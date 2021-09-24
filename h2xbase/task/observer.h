#ifndef H2XBASE_TASK_OBSERVER_H
#define H2XBASE_TASK_OBSERVER_H

#include "h2xbase/error.h"
#include "h2xbase/task/event.h"

namespace h2x {

class Observer
{
public:
    Observer();

    virtual ~Observer();

    virtual void notice(const Error& er, const char* data, const size_t size, const Event& reqEvent) {}

};

} // end namespace h2x

#endif // H2XBASE_TASK_OBSERVER_H
