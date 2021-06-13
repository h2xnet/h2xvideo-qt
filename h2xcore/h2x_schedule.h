#ifndef H2XCORE_H2X_SCHEDULE__H
#define H2XCORE_H2X_SCHEDULE__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Application;
class Context;

/*
* ClassName: Schedule
* Desc: ��ʱ������
* Author: zfs
* Date: 2021-06-05 09:50
*/
class H2XCORE_EXPORT Schedule {
public:
    Schedule(Context* ctx);
    virtual ~Schedule();

private:
    // Ӧ�ö���
    Application* app_;

    // ����������
    Context* ctx_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_SCHEDULE__H
