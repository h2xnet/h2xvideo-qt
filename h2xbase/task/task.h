#ifndef H2XBASE_TASK_TASK__H
#define H2XBASE_TASK_TASK__H

#include "h2xbase/task/callback.h"
#include "h2xbase/time/time.h"
#include "h2xbase/h2x_base_export.h"
#include <assert.h>

namespace h2x {

/*struct H2XBASE_EXPORT PendingTask {
    PendingTask(const StdClosure& task) : std_task(task), sequence_num(0){}

    PendingTask(const StdClosure &task,
        h2x::TimeTicks delayed_run_time) : std_task(task), delayed_run_time(delayed_run_time),
        sequence_num(0) {}

    ~PendingTask() {}

    // �������ȶ��е�����std::heapĬ��Ϊ�󶥶ѣ�
    // ������Ҫ����С���ѣ������������������ʵ�ʵ÷��ش��ڵıȽϽ��
    bool operator<(const PendingTask& other) const {
        if (delayed_run_time > other.delayed_run_time)
            return true;
        if (delayed_run_time < other.delayed_run_time)
            return false;
        return sequence_num > other.sequence_num;
    }

    // �������е�ʱ�̣����Ҳ���ڼ���ʱ������Ƕ�ʱ����
    h2x::TimeTicks delayed_run_time;
    // ��ʱ������ţ�����Ϊ��ʱ����ĵڶ���������Ƕ�ʱ���������Ч
    int sequence_num;

    void Run() {
        if (std_task) {
            std_task();
        }
        else {
            assert(false);
        }
    }

private:
    StdClosure std_task;
};*/

} // end namespace h2x

#endif // !H2XBASE_TASK_TASK__H
