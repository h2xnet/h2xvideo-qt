#include "h2xbase/error.h"

namespace h2x {


Error::Error() : flag(0), data_size(0)
{

}

Error::~Error() {
    if (data_ptr.get()) {
        data_ptr.release();
    }
}

void Error::setData(const char* data, const size_t size) {
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
