#ifndef H2XBASE_H2X_ERROR_CODE__H
#define H2XBASE_H2X_ERROR_CODE__H

#include <memory>
#include <stdint.h>

namespace h2x {

//
// ErrorCode : ������Ϣ code ����
//
enum ErrorCode {
    ERROR_CODE_SUCCESS = 0, // �ɹ�
    ERROR_CODE_FAIL = 1, // ʧ��
    ERROR_CODE_PARAM_ERROR = 3, // ��������
    ERROR_CODE_ALLOC_FAIL = 4, // ���ڷ���ʧ��
    ERROR_CODE_NOT_VALID = 5, // ֵ��Ч
    ERROR_CODE_NOT_OPEN = 6, // û�д�
    ERROR_CODE_OPEN_FAIL = 7, // ��ʧ��
};

//
// ������Ϣ status ����
//
#define ERROR_STATUS_SUCCESS    0   // �ɹ�
#define ERROR_STATUS_FAIL       -1  // ʧ��

} // end namespace h2x

#endif // ! H2XBASE_H2X_ERROR_CODE__H
