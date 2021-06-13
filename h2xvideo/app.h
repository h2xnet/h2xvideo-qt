#ifndef H2XVIDEO_APP__H
#define H2XVIDEO_APP__H

#include "h2xbase/logger/h2x_logger.h"
#include "h2xcore/h2x_application.h"

namespace h2x {
    
class Logger;
class Config;
class View;

}

/*
 * ClassName : App
 * Desc: Ӧ���࣬һ��Ӧ��ֻ�������һ��Ӧ�ö���
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
     * Desc: ע��QML��ͼ������,ע�����ͼ���еĺ������Ա�QML����
     */
    void registViews();

    /*
     * FunctionName: beforeStart
     * Desc: ��Ӧ�÷�������ǰ������ô˺����ص�֪ͨ��һ��Ӧ��ֻ��֪ͨһ��
     * Author: zfs
     * Date: 2021-06-12 15:40
     */
    virtual void beforeStart() override;

    /*
     * FunctionName: onStarted
     * Desc: ��Ӧ�÷���������ɺ󣬻���ô˺����ص�֪ͨ��һ��Ӧ��ֻ��֪ͨһ��
     * Author: zfs
     * Date: 2021-06-12 15:41
     */
    virtual void onStarted() override;

    h2x::Logger& getLogger() {
        return logger_;
    }

private:
    h2x::Logger logger_;
};

extern App& getApp();

#endif // !H2XVIDEO_APP__H
