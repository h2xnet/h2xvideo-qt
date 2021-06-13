#ifndef H2XCORE_H2X_ERROR__H
#define H2XCORE_H2X_ERROR__H

#include <memory>
#include "h2xbase/string/string_result.h"
#include "h2xbase/h2x_error_code.h"
#include "h2xcore/h2x_core_export.h"

namespace h2x {

/*
* ClassName: Error
* Desc: ������Ϣ��
* Author: zfs
* Date: 2021-06-05 10:18
*/
class H2XCORE_EXPORT Error {
public:
    Error();
    virtual ~Error();

public:
    // ����״̬��0Ϊ�ɹ�������Ϊ�������
    int status_;

    // ���ݴ�����룬0Ϊ��ȷ������Ϊ�������
    int code_;

    // ������Ϣ
    StringResult<char> msg_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_ERROR__H
