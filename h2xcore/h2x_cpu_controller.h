#ifndef H2XCORE_H2X_CPU_CONTROLLER__H
#define H2XCORE_H2X_CPU_CONTROLLER__H

#include "h2xcore/h2x_core_export.h"
#include "h2xcore/h2x_controller.h"

namespace h2x {

    /*
    * ClassName: CPUController
    * Desc: CPU�������࣬�����ṩ��CPU�������ʹ���
    * Author: zfs
    * Date: 2021-05-27 21:44
    */
    class H2XCORE_EXPORT CPUController : public Controller {
    public:
        CPUController(Application* app, Context* ctx);
        virtual ~CPUController();
    };

} // end namespace h2x

#endif // !H2XCORE_H2X_CPU_CONTROLLER__H
