#include "h2xvideo/app.h"

#include "h2xvideo/main_view_handler.h"

#include <QtQml>

App::App() : Application(0, NULL, NULL) {

}

App::App(int argc, char *argv[], const h2x::Config* cfg) : Application(argc, argv, cfg) {

}

void App::operator=(const App& other) {
    this->argc_ = other.argc_;
    this->argv_ = other.argv_;
    this->cfg_ = other.cfg_;
}

App::~App() {

}

MainViewHandler* App::getMainView() {
    static MainViewHandler* inst = NULL;

    if (!inst) {
        inst = MainViewHandler::qmlAttachedProperties(NULL);
    }

    return inst;
}

void App::registViews() {
    qmlRegisterType<MainViewHandler>("module.h2xvideo.mainviewhandler", 1, 0, "MainViewHandler");
}

void App::beforeStart() {
    // 初始化库
    int ret = init_library();

    // 注册页面控制类
    this->registViews();
}

void App::onStarted() {

}
