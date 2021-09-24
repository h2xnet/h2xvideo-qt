#include "h2xbase/task/event.h"

namespace h2x {

Event::Event() : event_id(0), data_size(0) {

}

Event::Event(const Event& o) {
    event_id = o.event_id;
    data_size = o.data_size;
    if (o.data_ptr.get() && o.data_size > 0) {
        data_ptr.reset(new char[data_size + 1]{'\0'});
        memcpy(data_ptr.get(), o.data_ptr.get(), o.data_size);
        data_size = o.data_size;
    }
}

Event::~Event() {
    if (data_ptr.get()) {
        data_ptr.release();
    }
}

void Event::setData(const char* data, size_t size) {
    data_ptr.reset(NULL);
    data_size = 0;

    if (data && size > 0) {
        data_ptr.reset(new char[size + 1]{'\0'});
        if (data_ptr.get()) {
            memcpy(data_ptr.get(), data, size);
            data_size = size;
        }
    }
}

} // end namespace h2x
