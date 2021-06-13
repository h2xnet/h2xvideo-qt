#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include "h2xvideo/app.h"
#include "h2xvideo/app_config.h"
#include "h2xbase/crash/crash_win.h"

#include "h2xvideo/main_view_handler.h"

namespace {
    static AppConfig g_app_cfg_;
    static App g_app_;
}

App& getApp() {
    return g_app_;
}

class CrashWinHandle : public h2x::CrashHandler {
public:
};

int main(int argc, char *argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app(argc, argv);

    // 初始化应用,必须放在engine之前，因为里面包含注册类型
    g_app_ = App(argc, argv, &g_app_cfg_);

    // 执行应用初始化
    if (!g_app_.exec()) {

    }

    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
