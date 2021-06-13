#ifndef H2XBASE_TASK_MESSAGE_LOOP__H
#define H2XBASE_TASK_MESSAGE_LOOP__H

#include "build/build_config.h"
#include <memory>
#include <mutex>
#include <queue>
#include "h2xbase/task/callback.h"
#include "h2xbase/task/message_pump.h"
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/h2x_observer_list.h"
#include "h2xbase/time/time.h"

namespace h2x {

    // һ���߳����ֻ��ʹ��һ��MessageLoop��
    // MessageLoop���ڴ���Task��ͬʱ���������͵Ĳ�ͬ��MessageLoop�����ܴ���Windows��Ϣ����ʱ����IO�¼���
    // �����ر�˵����MessageLoop�����еĳ�Ա������ֻ������ִ��MessageLoop���߳��ϵ���
    //
    // MessageLoop��Task���뱣����Ҳ����˵��һ��Taskִ�й����������˵ڶ���Task��
    // ��ô�ڶ���Task���ڵ�һ��Taskִ�����֮��Żᱻִ�У���Ϊ�ڶ���Task��Ҳ������һ��MessagePump��
    // Ҫ���������Ϊ����Ҫʹ��SetNestableTasksAllowed������������������˵��

    class UIMessageLoop;
    class IOMessageLoop;
    class MessageLoopProxy;

/*
 * ClassName: MessageLoop
 * Desc: ��Ϣѭ��������
 * Author: zfs
 * Date: 2021-06-08 21:26
 */
class H2XBASE_EXPORT MessageLoop : public MessagePump::Delegate {
public:
    enum Type
    {
        kDefaultMessageLoop,
        kUIMessageLoop, // ��Ҫ���ڽ�����Ⱦ��ͨ����ҵ����ֻ�ṩ����չʾ��
        kIOMessageLoop, // ��Ҫ������������������ļ���д����������Ӧ��
        kCustomMessageLoop // �Զ�����Ϣѭ��
    };

    explicit MessageLoop();
    virtual ~MessageLoop();

    static MessageLoop* current();

#if defined(OS_WIN)
    // ת���ɶ�Ӧ�������͵�MessageLoopָ��
    // ���ԭָ��Ƕ�Ӧ���͵�ָ�룬������NULL
    UIMessageLoop* ToUIMessageLoop();
    IOMessageLoop* ToIOMessageLoop();
#elif defined(OS_POSIX)
    IOMessageLoop* ToIOMessageLoop();
#endif

    MessagePump * pump() { return pump_.get(); }

    Type type() const { return type_; }

    // ����MessageLoop
    void run();

    // �������д������Task��Windows��Ϣ��IO�¼��ȵȣ����ǽ���Wait/Sleep��
    // �����д������Task��������ɺ������Ӷ���������ĵ��÷���
    void runAllPending();

    // ֪ͨMessageLoop�ڴ������д���������֮���Run�����з��ء�
    // �������ֻ���ڵ���Run�������Ǹ��߳��б�����
    // Ҫ�˳������̵߳�MessageLoop����Ҫʹ��PostTask�庯��Ͷ��һ��QuitTask�������棩
    void quit();

    // Quit�����ı��壬����������Run���ض��������κδ������Task
    void quitNow();

    // PostTask�庯�������ڸ�MessageLoop����첽ִ�е�����
    //
    // - PostTask���������ͨ��Ƕ������
    // - PostDelayedTask������Ӷ�ʱ�����ʺ�һЩ��Ҫ���Ӻ�ָ��ʱ��ִ�е�Ƕ������
    // - PostNonNestableTask������ӷ�Ƕ��ִ�е�������������ֻ������MessageLoop��Run�����б�ִ�е�����
    //   ��Ƕ�׵�MessageLoop��PostNonNestableTask����ô��Щ��Post��Task�����ݴ档
    // - PostNonNestableDelayedTask������ӷ�Ƕ�׵Ķ�ʱ������������ֻ���ض�ʱ��������MessageLoop��Run����
    //   �б�ִ�е�������������Ƕ�׵�MessageLoop�У��ʺ���Ҫ���Ӻ�ָ��ʱ��ִ�еķ�Ƕ������
    //
    // PostTask�庯�����̰߳�ȫ��һ���߳̿���ʹ����Щ�����������̷߳�������
    //
    // ע�⣺һ������Post��MessageLoop֮�����������ڽ������MessageLoop���ڵ��߳̿���
    void postTask(const StdClosure &task);
    void postDelayedTask(const StdClosure &task, TimeDelta delay);
    void postNonNestableTask(const StdClosure &task);
    void postNonNestableDelayedTask(const StdClosure &task, TimeDelta delay);

    // SetNestableTasksAllowed�������û��߽���Ƕ��������
    // �������Ƕ��������ôTask��������ִ�У������ȱ��ݴ���һ��������ֱ���ϲ�����ִ�������ִ��
    // ���͵ĳ�����
    // - �߳�������һ��MessageLoop
    // - �߳��յ���һ��Task��Task #1
    // - Task #1ִ�й����е�����һ��MessageBox�Ӷ���ʽ�ؽ�����һ��MessageLoop����MessageBox��Ϣѭ����
    // - ��MessageBox��MessageLoop��δ����ǰ���߳����յ�����һ��Task��Task #2
    // - �����ʱǶ�����������ã���ôTask #2��������ִ�У�����Task #1�Ƿ��Ѿ���������
    //   ����Task #2����Task #1��ִ����ɺ������̵߳�MessageLoop��ִ�С�
    void setNestableTasksAllowed(bool allowed);
    bool isNestableTasksAllowed() const { return nestable_tasks_allowed_; }
    //bool IsNested() const { if (state_) return state_->run_depth > 1; return false; }

    // MessageLoopProxy�ṩ���̰߳�ȫ����MessageLoop�Ļ��ƣ�
    // ���з��߳��ڵ�PostTask�庯������ͨ��MessageLoopProxy����
    std::shared_ptr<MessageLoopProxy> message_loop_proxy() {
        return message_loop_proxy_;
    }

    // MessageLoop���ٹ۲��ߣ�MessageLoop����ǰ����֪ͨ��Щ�۲���
    class H2XBASE_EXPORT DestructionObserver {
    public:
        virtual void PreDestroyCurrentMessageLoop() = 0;
        virtual ~DestructionObserver() {}
    };

    void addDestructionObserver(DestructionObserver *observer);
    void removeDestructionObserver(DestructionObserver *observer);

    // ����۲��ߣ�ÿ�����񱻴���ǰ�ʹ�������֪ͨ��Щ�۲���
    class H2XBASE_EXPORT TaskObserver
    {
    public:
        virtual void preProcessTask() {}
        virtual void postProcessTask() {}

    protected:
        virtual ~TaskObserver() {}
    };

    void addTaskObserver(TaskObserver* observer);
    void removeTaskObserver(TaskObserver* observer);

    struct RunState {
        int run_depth;
        bool quit_received;
    };

    class H2XBASE_EXPORT AutoRunState : RunState {
    public:
        explicit AutoRunState(MessageLoop* loop);
        ~AutoRunState();
    private:
        MessageLoop* loop_;
        RunState* previous_state_;
    };

    class ScopedNestableTaskAllower {
    public:
        explicit ScopedNestableTaskAllower(MessageLoop* loop)
            : loop_(loop),
            old_state_(loop_->isNestableTasksAllowed()) {
            loop_->setNestableTasksAllowed(true);
        }
        ~ScopedNestableTaskAllower() {
            loop_->setNestableTasksAllowed(old_state_);
        }

    private:
        MessageLoop* loop_;
        bool old_state_;
    };

    struct PendingTask {
        PendingTask(const StdClosure &task);
        PendingTask(const StdClosure &task,
            TimeTicks delayed_run_time,
            bool nestable);

        ~PendingTask();

        // �������ȶ��е�����std::heapĬ��Ϊ�󶥶ѣ�
        // ������Ҫ����С���ѣ������������������ʵ�ʵ÷��ش��ڵıȽϽ��
        bool operator<(const PendingTask& other) const;
        // �������е�ʱ�̣����Ҳ���ڼ���ʱ������Ƕ�ʱ����
        TimeTicks delayed_run_time;
        // ��ʱ������ţ�����Ϊ��ʱ����ĵڶ���������Ƕ�ʱ���������Ч
        int sequence_num;
        // �Ƿ�������Ƕ�׵�MessageLoop�б�ִ��
        bool nestable;

        void run() {
            if (std_task) {
                std_task();
            }
            else {
                assert(false);
            }
        }

    private:
        StdClosure std_task;
    };

    class TaskQueue : public std::queue<PendingTask> {
    public:
        void swap(TaskQueue* queue) {
            c.swap(queue->c);  // ����ʱ�临�Ӷȵ��ڴ潻��
        }
    };

    typedef std::priority_queue<PendingTask> DelayedTaskQueue;

    // MessagePump::Delegate
    virtual bool doWork() override;
    virtual bool doDelayedWork(TimeTicks *next_delayed_message_time) override;
    virtual bool doIdleWork() override;

    void runInternal();

    // AddToIncomingQueue�����̰߳�ȫ�������Ϊ���̰߳�ȫ
    virtual void addToIncomingQueue(const PendingTask &task);
    void addToDelayedWorkQueue(const PendingTask &task);
    void reloadWorkQueue();
    bool deferOrRunPendingTask(const PendingTask &task);
    void runTask(const PendingTask &task);
    bool processNextDelayedNonNestableTask();
    bool deletePendingTasks();

    void preDestruct();
    void preProcessTask();
    void postPrecessTask();

    static TimeTicks evalDelayedRuntime(int64_t delay_ms);

protected:
    // MessageLoop����
    Type type_;
    // ����״̬
    RunState *state_;
    // ��Ϣ��
    std::shared_ptr<MessagePump> pump_;

    // �Ƿ�����Ƕ������
    bool nestable_tasks_allowed_;

    // ����������У��κξ���Post�庯��������������Ƚ���ö��У�֮��������Run���̷߳��䵽����רְ����
    TaskQueue incoming_queue_;
    // ���������
    std::mutex incoming_queue_lock_;

    // ����������е������Ϊ������޶ȼ��ٶ�������еļ���������
    // ���ֹ�ϵ������˫������ƣ���������ݴ汾�̺߳������߳�Ͷ�ݹ���������
    // �������������������Run�������̲߳�����ֻ���̼߳�鵽��������Ϊ�ղŻ�ȥ�������������ŵ���������Ȼ��������С�
    // ��������˽����ڴ�ķ���������������Ч�ʣ�Ҳ����˵������Ĳ�����ʵ����һ��һ��������������ƶ���������ɵģ�
    // ����ֱ�ӽ���˫�����ڴ棬�����������������˲ʱ��գ������������ӵ����֮ǰ����������е����ݡ�
    TaskQueue work_queue_;
    // MessageLoop����Ƕ����ʱ����Ƕ�����񽫱���ʱ������������У���MessageLoop�ص������ʱ����ͨ��DoIdleWork���ִ��֮
    TaskQueue deferred_non_nestable_work_queue_;
    // ��ʱ������У�Ƕ�׺ͷ�Ƕ�ף�
    DelayedTaskQueue delayed_work_queue_;
    // ��һ����ʱ��������к�
    int next_delayed_task_sequence_num_;
    // ���һ�ε���TimeTicks::Now������ʱ��
    TimeTicks recent_tick_;
    // ����۲����б�
    ObserverList<TaskObserver> task_observers_;
    // MessageLoop���ٹ۲����б�
    ObserverList<DestructionObserver> destruction_observers_;

    // The message loop proxy associated with this message loop, if one exists.
    std::shared_ptr<MessageLoopProxy> message_loop_proxy_;
};

} // end namespace h2x

#endif // !H2XBASE_TASK_MESSAGE_LOOP__H
