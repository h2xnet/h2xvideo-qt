#include "h2xvideo/main_view_handler.h"

#include "h2xvideo/app.h"

namespace {

static MainViewHandler* g_instance_ = NULL;

}

MainViewHandler* MainViewHandler::qmlAttachedProperties(QObject *object) {
    if (!g_instance_) {
        g_instance_ = new MainViewHandler(object);
    }
    return g_instance_;
}

MainViewHandler::MainViewHandler(QObject* parent) : QObject(parent) {
    // 绑定信号和槽函数

}

MainViewHandler::~MainViewHandler() {

}

void MainViewHandler::routerPageSet(QString sender, QString pageId, QString pageParam) {

    getApp().getLogger().PrintLogW(h2x::Logger::ContentType::Info, L"MainViewHandler::routerPageSet sender:%s pageId:%s, pageParam:%s\n",
        reinterpret_cast<const wchar_t*>(sender.utf16()),
        reinterpret_cast<const wchar_t*>(pageId.utf16()),
        reinterpret_cast<const wchar_t*>(pageParam.utf16()));

    // 通知页面改变
    emit routerPageChangeEvent(sender, pageId, pageParam);
}

void MainViewHandler::closeApp(QString sender, int exitCode) {
    // 关闭APP
    getApp().getLogger().PrintLogW(h2x::Logger::ContentType::Info,
                                   L" MainViewHandler::closeApp sender:%s exitCode:%d\n",
                                   reinterpret_cast<const wchar_t*>(sender.utf16()), exitCode);

    exit(exitCode);
}
