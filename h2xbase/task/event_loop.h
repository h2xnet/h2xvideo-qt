#ifndef H2XBASE_TASK_EVENT_LOOP_H
#define H2XBASE_TASK_EVENT_LOOP_H

#include <queue>
#include <mutex>

#include "h2xbase/task/event.h"
#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
 * ClassName: EventLoop
 * Desc: 事件循环,主要用于通知
 * Author: zfs
 * Date: 2021-08-15 09:42
 */
class H2XBASE_EXPORT EventLoop
{
public:
    explicit EventLoop();
    virtual ~EventLoop();

    // Delegate class
    class Delegate {
    public:
        virtual bool IsRunning() = 0;
        virtual bool RunPendingTask(const Event& task) = 0;
    };

    // Event queue
    class EventQueue : public std::queue<Event> {
    public:
        void swap(EventQueue* que) {
            // 常数时间复杂度的内存交换
            c.swap(que->c);
        }
    };

    /*
     * FunctionName: PostEvent
     * Desc: 投递消息任务
     * Author: zfs
     * Date: 2021-08-15 09:46
     * @delegate: 任务代理指针
     */
    virtual bool PostEvent(const Event& task);

    /*
     * FunctionName: ScheduleWork
     * Desc: 通知处理即时任务
     * Author: zfs
     * Date: 2021-08-15 09:46
     */
    virtual void ScheduleWork();

    void NoticeOne();
    void NoticeAll();

    /*
     * FunctionName: working
     * Desc: 开始消息循环
     * Author: zfs
     * Date: 2021-08-15 09:46
     * @delegate: 任务代理指针
     */
    virtual void working(Delegate* delegate);


private:

    /*
     * FunctionName: OnAddToIncomingQueue
     * Desc: add task to queue
     * Authro: zfs
     * Date: 2021-08-15 09:47
     */
    bool OnAddToIncomingQueue(const Event& task);

    /*
     * FunctionName: OnReloadWorkQueue
     * Desc: 加载工作任务
     * Author: zfs
     * Date: 2021-08-15 09:47
     */
    void OnReloadWorkQueue();

    /*
     * FunctionName: OnDoWork
     * Desc: 执行一次工作任务（处理一批消息）
     * Author: zfs
     * Date: 2021-08-15 09:47
     */
    bool OnDoWork();

    //
    // 等待事件，通知等待
    //
    void OnWait();
    bool OnWaitTimes(int milSecs);
    void OnNotifyOne();
    void OnNotifyAll();

    // input event queue
    EventQueue incoming_queue_;
    std::mutex incoming_queue_mutex_;

    // work event queue
    EventQueue work_queue_;

    // wait event
    std::mutex wait_mutex_;
    std::condition_variable wait_cv_;

    // agent
    Delegate* delegate_;

};

} // namespace h2x

#endif // H2XBASE_TASK_EVENT_LOOP_H
