#include "h2xbase/task/message_loop.h"

#include "h2xbase/task/default_message_pump.h"
#include "h2xbase/task/message_loop_proxy.h"

#include <assert.h>
#include "h2xbase/memory/lazy_instance.h"
#include "h2xbase/thread/thread_local.h"

namespace h2x {

LazyInstance<ThreadLocalPointer<MessageLoop> > g_lazy_ptr;

MessageLoop::MessageLoop() : type_(kDefaultMessageLoop), state_(NULL), nestable_tasks_allowed_(true),
next_delayed_task_sequence_num_(0) {
    // һ���߳��ڲ��ܴ�������������MessageLoop
    assert(g_lazy_ptr.pointer()->get() == NULL);
    // Ĭ����Ϣѭ��
    if (type_ == kDefaultMessageLoop) {
        pump_.reset(new DefaultMessagePump);
    }
    g_lazy_ptr.pointer()->set(this);

    message_loop_proxy_.reset(new MessageLoopProxy, &MessageLoopProxyTraits::destruct);
    message_loop_proxy_->target_message_loop_ = this;
}

MessageLoop::~MessageLoop() {
    bool has_work = false;

    // ����δ�����������ܵ��������µ�����
    // ����ͨ�����޴ε�ѭ������������Щ�����ɵ�����
    for (int i = 0; i < 100; i++)
    {
        deletePendingTasks();
        reloadWorkQueue();
        has_work = deletePendingTasks();
        if (!has_work)
            break;
    }

    assert(!has_work);

    preDestruct();

    message_loop_proxy_->willDestroyCurrentMessageLoop();
    message_loop_proxy_ = nullptr;

    g_lazy_ptr.pointer()->set(NULL);
}

MessageLoop* MessageLoop::current()
{
    return g_lazy_ptr.pointer()->get();
}

void MessageLoop::run() {
    assert(this == current());
    AutoRunState state(this);
    runInternal();
}

void MessageLoop::runAllPending() {
    assert(this == current());
    AutoRunState state(this);
    state_->quit_received = true;  // Means run until we would otherwise block.
    runInternal();
}

void MessageLoop::runInternal() {
    assert(this == current());

    pump_->run(this);
}

bool MessageLoop::deletePendingTasks() {
    bool has_work = false;
    while (!work_queue_.empty())
    {
        PendingTask task = work_queue_.front();
        work_queue_.pop();
        if (!task.delayed_run_time.is_null())
            addToDelayedWorkQueue(task);
    }

    while (!deferred_non_nestable_work_queue_.empty())
        deferred_non_nestable_work_queue_.pop();

    has_work = !delayed_work_queue_.empty();
    while (!delayed_work_queue_.empty())
        delayed_work_queue_.pop();

    return has_work;
}

void MessageLoop::quit() {
    if (state_) {
        state_->quit_received = true;
    }
}

void MessageLoop::quitNow() {
    if (pump_) {
        pump_->quit();
    }
}

void MessageLoop::postTask(const StdClosure &task) {
    PendingTask pending_task(task);
    addToIncomingQueue(pending_task);
}

void MessageLoop::postDelayedTask(const StdClosure &task, TimeDelta delay) {
    PendingTask pending_task(task,
        TimeTicks::Now() + delay,
        true);
    addToIncomingQueue(pending_task);
}

void MessageLoop::postNonNestableTask(const StdClosure &task) {
    PendingTask pending_task(task,
        TimeTicks(),
        false);
    addToIncomingQueue(pending_task);
}

void MessageLoop::postNonNestableDelayedTask(const StdClosure &task, TimeDelta delay) {
    PendingTask pending_task(task,
        TimeTicks::Now() + delay,
        false);
    addToIncomingQueue(pending_task);
}

TimeTicks MessageLoop::evalDelayedRuntime(int64_t delay_ms) {
    TimeTicks delayed_run_time;
    if (delay_ms > 0)
        delayed_run_time = TimeTicks::Now() + TimeDelta::FromMilliseconds(delay_ms);
    return delayed_run_time;
}

void MessageLoop::addToIncomingQueue(const PendingTask &task) {
    // ���������ܻ�����һ���߳��б�ִ�У����Ա����̰߳�ȫ
    std::shared_ptr<MessagePump> pump;
    {
        std::unique_lock<std::mutex> lock(incoming_queue_lock_);
        bool was_empty = incoming_queue_.empty();
        incoming_queue_.push(task);
        if (!was_empty) {
            return;
        }
        // ��Ϊ�⺯�������Ǽ�ӵ�����һ���߳��б����õģ�
        // ��ʱMessageLoop�п����������������У�
        // ��Щ�����п��ܰ�������MessageLoop������
        // Ϊ�˱�֤��MessageLoop�е�MessagePump������Ч��
        // ������Ҫ�õ�����ָ��
        pump = pump_;
    }
    pump->scheduleWork();
}

void MessageLoop::addToDelayedWorkQueue(const PendingTask &task) {
    PendingTask new_task(task);
    new_task.sequence_num = next_delayed_task_sequence_num_++;
    delayed_work_queue_.push(new_task);
}

void MessageLoop::reloadWorkQueue() {
    if (!work_queue_.empty()) {
        return;
    }

    {
        std::unique_lock<std::mutex> lock(incoming_queue_lock_);
        if (incoming_queue_.empty())
            return;
        // ����ʱ�佻���ڴ�
        work_queue_.swap(&incoming_queue_);
    }
}

bool MessageLoop::deferOrRunPendingTask(const PendingTask &task)
{
    // �����������ִ�е���������ôִ��֮
    if (task.nestable || state_->run_depth == 1)
    {
        runTask(task);
        return true;
    }
    // ����Ƕ��������Ҫ����ֱ֮�������MessageLoop��ִ��
    deferred_non_nestable_work_queue_.push(task);
    return false;
}

void MessageLoop::runTask(const PendingTask &task)
{
    assert(nestable_tasks_allowed_);

    // ���ǵ������£���������ǲ�������ģ�
    // ������ʱ����Ƕ������

    nestable_tasks_allowed_ = false;
    PendingTask pending_task = task;
    preProcessTask();
    pending_task.run();
    postPrecessTask();
    nestable_tasks_allowed_ = true;
}

bool MessageLoop::doWork() {
    // ����ǰ�Ƿ�����ִ��
    if (!nestable_tasks_allowed_)
        return false;

    for (;;)
    {
        // �ȴ�incoming����ȡ����
        reloadWorkQueue();
        if (work_queue_.empty())
            break;

        // һ���Դ���work�����е���������
        do
        {
            PendingTask task = work_queue_.front();
            work_queue_.pop();
            if (!task.delayed_run_time.is_null())
            {
                // ���뵽��ʱ�������
                addToDelayedWorkQueue(task);
                // ���������������ǽ�������ִ�еģ���ô��Ҫ���µ���
                if (delayed_work_queue_.top().sequence_num == task.sequence_num)
                    pump_->scheduleDelayedWork(task.delayed_run_time);
            }
            else
            {
                if (deferOrRunPendingTask(task))
                    return true;
            }
        } while (!work_queue_.empty());
    }

    return false;
}

bool MessageLoop::doDelayedWork(TimeTicks *next_delayed_message_time) {
    if (!next_delayed_message_time) {
        return false;
    }
    if (!nestable_tasks_allowed_ || delayed_work_queue_.empty())
    {
        *next_delayed_message_time = recent_tick_ = TimeTicks();
        return false;
    }

    // recent_tick_��¼���һ�ε���TimeTick::Nowʱ��ʱ�䣬
    // �����ܴ���TimeTick::Now������ֻ��һ����ȥ��Now�Ļ��棬
    // ��������޶ȼ��ٶ�TimeTick::Now�ĵ��á�
    // recent_tick_�������е�һ���жϣ�Ҫ���о�ȷ�ж���Ҫ������Ϊ������TimeTick::Now

    TimeTicks next_run_time = delayed_work_queue_.top().delayed_run_time;
    if (next_run_time > recent_tick_)
    {
        // ������recent_tick_�Ĳ���ȷ��������Ҫ����֮
        recent_tick_ = TimeTicks::Now();
        if (next_run_time > recent_tick_)
        {
            // �����һ����������Ҫ�����е�����������������
            *next_delayed_message_time = next_run_time;
            return false;
        }
    }

    // �����ʱ��������ʱ���ѵ�������֮
    PendingTask task = delayed_work_queue_.top();
    delayed_work_queue_.pop();

    if (!delayed_work_queue_.empty())
        *next_delayed_message_time = delayed_work_queue_.top().delayed_run_time;

    return deferOrRunPendingTask(task);
}


bool MessageLoop::processNextDelayedNonNestableTask() {
    // Ƕ������
    if (state_->run_depth != 1)
        return false;

    if (deferred_non_nestable_work_queue_.empty())
        return false;

    PendingTask task = deferred_non_nestable_work_queue_.front();
    deferred_non_nestable_work_queue_.pop();
    runTask(task);
    return true;
}

bool MessageLoop::doIdleWork() {
    // ����Idle״̬���ȳ���ִ�б������ŵķ�Ƕ������
    if (processNextDelayedNonNestableTask())
        return true;

    // ����˳����
    if (state_->quit_received)
        pump_->quit();

    return false;
}

void MessageLoop::setNestableTasksAllowed(bool allowed) {
    if (nestable_tasks_allowed_ != allowed)
    {
        nestable_tasks_allowed_ = allowed;
        if (!nestable_tasks_allowed_)
            return;
        pump_->scheduleWork();
    }
}

void MessageLoop::addDestructionObserver(DestructionObserver *observer) {
    assert(this == current());
    destruction_observers_.AddObserver(observer);
}

void MessageLoop::removeDestructionObserver(DestructionObserver *observer) {
    assert(this == current());
    destruction_observers_.RemoveObserver(observer);
}

void MessageLoop::addTaskObserver(TaskObserver *observer) {
    assert(this == current());
    task_observers_.AddObserver(observer);
}

void MessageLoop::removeTaskObserver(TaskObserver *observer) {
    assert(this == current());
    task_observers_.RemoveObserver(observer);
}

void MessageLoop::preDestruct() {
    size_t index = 0;
    DestructionObserver* observer;
    AutoLazyEraser lazy_eraser(&destruction_observers_);
    while (index < destruction_observers_.GetObserverCount())
    {
        observer = destruction_observers_.GetObserver(index++);
        if (observer == NULL)
            continue;
        observer->PreDestroyCurrentMessageLoop();
    }
}

void MessageLoop::preProcessTask() {
    size_t index = 0;
    TaskObserver* observer;
    AutoLazyEraser lazy_eraser(&task_observers_);
    while (index < task_observers_.GetObserverCount())
    {
        observer = task_observers_.GetObserver(index++);
        if (observer == NULL)
            continue;
        observer->preProcessTask();
    }
    // NOT compact the observer list, here
}

void MessageLoop::postPrecessTask() {
    size_t index = 0;
    TaskObserver* observer;
    AutoLazyEraser lazy_eraser(&task_observers_);
    while (index < task_observers_.GetObserverCount())
    {
        observer = task_observers_.GetObserver(index++);
        if (observer == NULL)
            continue;
        observer->postProcessTask();
    }
}


// the AutoRunState class
MessageLoop::AutoRunState::AutoRunState(MessageLoop* loop) : loop_(loop) {
    // Make the loop reference us.
    previous_state_ = loop_->state_;
    if (previous_state_) {
        run_depth = previous_state_->run_depth + 1;
    }
    else {
        run_depth = 1;
    }
    loop_->state_ = this;

    // Initialize the other fields:
    quit_received = false;
}

MessageLoop::AutoRunState::~AutoRunState() {
    loop_->state_ = previous_state_;
}

MessageLoop::PendingTask::PendingTask(const StdClosure &task)
    : std_task(task), nestable(true), sequence_num(0) {

}

MessageLoop::PendingTask::PendingTask(const StdClosure &task, TimeTicks delayed_run_time, bool nestable) :
    std_task(task), delayed_run_time(delayed_run_time),
    nestable(nestable), sequence_num(0) {

}

MessageLoop::PendingTask::~PendingTask() {

}

bool MessageLoop::PendingTask::operator<(const MessageLoop::PendingTask& other) const {
    if (delayed_run_time > other.delayed_run_time)
        return true;
    if (delayed_run_time < other.delayed_run_time)
        return false;
    return sequence_num > other.sequence_num;
}

} // end namespace h2x