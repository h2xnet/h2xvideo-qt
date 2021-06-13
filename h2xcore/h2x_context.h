#ifndef H2XCORE_H2X_CONTEXT__H
#define H2XCORE_H2X_CONTEXT__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Application;
class Helper;
class Model;
class Request;
class Response;
class Service;
class Session; // �Ự��

/*
* ClassName: Context
* Desc: ��������������࣬ÿ�����󣬿�ܶ���ʵ����һ��Context����
* Author: zfs
* Date: 2021-05-16 17:20
*/
class H2XCORE_EXPORT Context {
public:
    Context();
    virtual ~Context();

private:
    // Ӧ�ö���
    Application* app_;

    // �����������
    Service* services_;

    // ����ģ�Ͷ�������
    Model* models_;

    // �������
    Request* req_;

    // Ӧ�����
    Response* res_;

    // �������
    Helper* helper_;

    // �Ự
    Session* session_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_CONTEXT__H
