#ifndef H2XCORE_H2X_HELPER__H
#define H2XCORE_H2X_HELPER__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Context;

/*
    * ClassName: Helper
    * Desc: ���������࣬���ڷ�װһЩ�����㷨��ÿ�δ��������Ķ���ʱ��ͬʱ����һ���������������
    * Author: zfs
    * Date: 2021-06-05 11:42
    */
class H2XCORE_EXPORT Helper {
public:
    Helper();
    virtual ~Helper();

private:
    // ���������Ķ���
    Context* ctx_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_HELPER__H
