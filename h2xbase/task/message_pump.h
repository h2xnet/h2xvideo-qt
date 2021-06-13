#ifndef H2XBASE_TASK_MESSAGE_PUMP__H
#define H2XBASE_TASK_MESSAGE_PUMP__H

#include "build/build_config.h"
#include "h2xbase/h2x_base_export.h"

namespace h2x {

class TimeTicks;

/*
* ClassName: MessagePump
* Desc: ��Ϣ����
* Author: zfs
* Date: 2021-06-08 21:27
*/
class H2XBASE_EXPORT MessagePump {
public:
    // Delegate��һ���ص��࣬��MessagePump������������������������
    //   DoWork��������ʱ��������������Ҫ�����ܿ�ر���ʼ����
    //   DoDelayedWork��������ʱ���������������ض�ʱ�̱�����next_delayed_message_timeΪ�¸�����ִ�е�ʱ��
    //   DoIdleWork����������ʱ��������������MessagePump���ڿ���״̬ʱ������
    // ���߷���ֵ�������ƣ�����true��ʾ�����˸������񣬷���false��ʾû�и���������Ҫ����
    class H2XBASE_EXPORT Delegate {
    public:
        virtual ~Delegate() {}

        virtual bool doWork() = 0;
        virtual bool doDelayedWork(TimeTicks *next_delayed_message_time) = 0;
        virtual bool doIdleWork() = 0;
    };

    MessagePump();
    virtual ~MessagePump();

    // ������Ϣѭ��
    virtual void run(Delegate* delegate) = 0;

    // ֪ͨ�˳���Ϣѭ��
    virtual void quit() = 0;

    // ֪ͨMessagePump����ʱ����
    // ���Կ��̵߳�������ӿ�
    virtual void scheduleWork() = 0;

    // ֪ͨMessagePump����ʱ����
    // �˽ӿڲ�������̵߳���
    virtual void scheduleDelayedWork(const TimeTicks& delay_message_time) = 0;

};

} // end namespace h2x

#endif // !H2XBASE_TASK_MESSAGE_PUMP__H
