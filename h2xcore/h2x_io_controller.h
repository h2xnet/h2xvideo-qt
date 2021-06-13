#ifndef H2XCORE_H2X_IO_CONTROLLER__H
#define H2XCORE_H2X_IO_CONTROLLER__H

#include "h2xcore/h2x_core_export.h"
#include "h2xcore/h2x_controller.h"

namespace h2x {

    /*
    * ClassName: IOController
    * Desc: IO�������࣬�����ṩ��IO�������ʹ���
    * ��CPU�������������ǣ�����IO������������ͬһ���߳��н������У��ʺϴ����IO����ʱ�ӵ�����
    * ����ͬ��CPU��������������ڲ�ͬ���߳������У�ÿ��CPU�����������ɵ������̸߳��������ʺϴ���ռCPUʱ�䳤��IO��Ƶ��������
    * Author: zfs
    * Date: 2021-05-27 21:50
    */
    class H2XCORE_EXPORT IOController : public Controller {
    public:
        IOController(Application* app, Context* ctx);
        virtual ~IOController();
    };

} // end namespace h2x

#endif // !H2XCORE_H2X_IO_CONTROLLER__H
