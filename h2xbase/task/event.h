#ifndef H2XBASE_TASK_EVENT__H
#define H2XBASE_TASK_EVENT__H

#include <memory>
#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
 * ClassName: Event
 * Desc: 事件类
 * 事件由ID和JSON字符串参数组成，ID具有唯一性，代表一个特定事件，JSON参数用户可自定义，也可以扩展
 * 某些特定插件会包含特定固定参数，用户想扩展，只需要往里面加就可以
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
    // 事件ID
    int event_id;

    // 事件参数，使用JSON字符串，不同事件可能包含不同的固定键，和自定义扩展键
    std::unique_ptr<char[]> data_ptr;
    size_t data_size;
};

} // end namespace h2x

#endif // !H2XBASE_TASK_EVENT__H
