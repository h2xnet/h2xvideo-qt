#ifndef H2XCORE_H2X_ROUTER__H
#define H2XCORE_H2X_ROUTER__H

#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Application;

/*
* ClassName: Router
* Desc: ·����
* Author: zfs
* Date: 2021-05-16 17:35
*/
class H2XCORE_EXPORT Router {
public:
    Router(Application* app);
    virtual ~Router();

private:
    // Ӧ�ö���
    Application* app_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_ROUTER__H
