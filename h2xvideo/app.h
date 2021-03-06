#ifndef H2XVIDEO_APP__H
#define H2XVIDEO_APP__H

#include "h2xbase/logger/h2x_logger.h"
#include "h2xcore/h2x_application.h"

#include "api/h2xvideo_api.h"

namespace h2x {
    
class Logger;
class Config;
class View;

}

class MainViewHandler;

/*
 * ClassName : App
 * Desc: 应用类，一个应用只允许包含一个应用对象
 * Author: zhaofushou
 * Date: 2021-06-12 15:36
 */
class App : public h2x::Application {
public:
    App();
    App(int argc, char *argv[], const h2x::Config* cfg);

    virtual ~App();

    void operator=(const App& other);

    /*
     * FunctionName: registViews
     * Desc: 注册QML视图控制器,注册的视图类中的函数可以被QML调用
     */
    void registViews();

    /*
     * FunctionName: beforeStart
     * Desc: 当应用服务启动前，会调用此函数回调通知，一个应用只会通知一次
     * Author: zfs
     * Date: 2021-06-12 15:40
     */
    virtual void beforeStart() override;

    /*
     * FunctionName: onStarted
     * Desc: 当应用服务启动完成后，会调用此函数回调通知，一个应用只会通知一次
     * Author: zfs
     * Date: 2021-06-12 15:41
     */
    virtual void onStarted() override;

    h2x::Logger& getLogger() {
        return logger_;
    }

    MainViewHandler* getMainView();

private:
    h2x::Logger logger_;
};

extern App& getApp();

#endif // !H2XVIDEO_APP__H
