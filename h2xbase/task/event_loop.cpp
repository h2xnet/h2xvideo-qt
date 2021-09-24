#include "h2xbase/task/event_loop.h"

#include <assert.h>

namespace h2x {


EventLoop::EventLoop() : delegate_(NULL)
{

}

EventLoop::~EventLoop() {
    if (delegate_) {
        delegate_ = NULL;
    }
}


bool EventLoop::PostEvent(const Event& task) {
    Event pending(task);
    return this->OnAddToIncomingQueue(pending);
}

bool EventLoop::OnAddToIncomingQueue(const Event& task) {
    {
        std::unique_lock<std::mutex> lock(incoming_queue_mutex_);
        bool was_empty = incoming_queue_.empty();
        incoming_queue_.push(task);
        if (!was_empty) {
            return true;
        }
        // 通知处理即时任务
        this->ScheduleWork();
        return true;
    }
}

void EventLoop::ScheduleWork() {
    this->NoticeOne();
}

void EventLoop::NoticeOne() {
    wait_cv_.notify_one();
}

void EventLoop::NoticeAll() {
    wait_cv_.notify_all();
}


void EventLoop::working(Delegate* delegate) {

    assert(delegate);

    delegate_ = delegate;

    while(true) {

        // 加载任务
        this->OnReloadWorkQueue();

        if (!work_queue_.empty()) {
            // 一次性处理work队列中的所有任务
            this->OnDoWork();

            // 执行完上一批任务，接着执行下一批任务
            continue;
        }

        // 判断是否退出
        if (!delegate_->IsRunning()) {
            break;
        }

        // 等待通知
        this->OnWait();
    }

}


void EventLoop::OnReloadWorkQueue() {
    if (!work_queue_.empty()) {
        return;
    }

    {
        std::unique_lock<std::mutex> lock(incoming_queue_mutex_);
        if (incoming_queue_.empty()) {
            return;
        }
        // 常数时间交换内存
        work_queue_.swap(&incoming_queue_);
    }
}

bool EventLoop::OnDoWork() {
    if (!delegate_) {
        return false;
    }
    do {
        Event task = work_queue_.front();
        work_queue_.pop();

        // 运行消息
        delegate_->RunPendingTask(task);

    } while(!work_queue_.empty());

    return true;
}

void EventLoop::OnWait() {
    std::unique_lock<std::mutex> lock(wait_mutex_);
    wait_cv_.wait(lock);
}

bool EventLoop::OnWaitTimes(int milSecs) {
    std::unique_lock<std::mutex> lock(wait_mutex_);
    //std::chrono::seconds   secs(iSec);
    std::chrono::milliseconds  ms(milSecs);
    auto ret =wait_cv_.wait_for(lock,  ms);
    return (ret != std::cv_status::timeout);
}

} // end namespace h2x
