#ifndef H2XBASE_TASK_EVENT__H
#define H2XBASE_TASK_EVENT__H

#include <memory>
#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
 * ClassName: Event
 * Desc: �¼���
 * �¼���ID��JSON�ַ���������ɣ�ID����Ψһ�ԣ�����һ���ض��¼���JSON�����û����Զ��壬Ҳ������չ
 * ĳЩ�ض����������ض��̶��������û�����չ��ֻ��Ҫ������ӾͿ���
 * Author: zfs
 * Date: 2021-08-15 09:19
 */
class H2XBASE_EXPORT Event {
public:
    Event();
    Event(const Event& o);
    virtual ~Event();

    void setEventId(int id) {   event_id = id;  }
    int getEventId() const  {   return event_id;    }

    void setData(const char* data, size_t size);
    const char* getData() const {   return data_ptr.get();  }
    size_t getDataSize() const  {   return data_size;   }

public:
    // �¼�ID
    int event_id;

    // �¼�������ʹ��JSON�ַ�������ͬ�¼����ܰ�����ͬ�Ĺ̶��������Զ�����չ��
    std::unique_ptr<char[]> data_ptr;
    size_t data_size;
};

} // end namespace h2x

#endif // !H2XBASE_TASK_EVENT__H
