#ifndef H2XBASE_ERROR_H
#define H2XBASE_ERROR_H

#include <memory>

#include "h2xbase/h2x_base_export.h"

namespace h2x {

enum ErrorFlag {
    requestFlag = 0,    // 请求
    responseFlag        // 应答
};

class H2XBASE_EXPORT Error
{
public:
    Error();
    ~Error();

    void setFlag(int f)  {   flag = f;  }
    int getFlag() const {   return flag;    }

    void setErrorId(int id) {   error_id = id;  }
    int getErrorId() const  {   return error_id;    }

    void setData(const char* data, const size_t size);
    const char* getData() const {   return data_ptr.get();  }
    size_t getDataSize() const  {   return data_size;    }

public:
    // 错误类型标记
    int flag;

    // 错误ID
    int error_id;

    // 错误消息
    std::unique_ptr<char[]> data_ptr;
    size_t data_size;
};

} // end namespace h2x

#endif // ERROR_H
