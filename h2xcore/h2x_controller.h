#ifndef H2XCORE_H2X_CONTROLLER__H
#define H2XCORE_H2X_CONTROLLER__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Application;
class Context;
class Logger;

/*
* ClassName: Controller
* Desc: ��������
* Author: zfs
* Date: 2021-05-16 17:20
*/
class H2XCORE_EXPORT Controller {
public:
    Controller(Application* app, Context* ctx);
    virtual ~Controller();

private:
    // Ӧ�ö���
    Application* app_;

    // �����Ķ���
    Context* ctx_;

    // Ϊ��ǰ��������װ����־����
    Logger* log_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_CONTROLLER__H
