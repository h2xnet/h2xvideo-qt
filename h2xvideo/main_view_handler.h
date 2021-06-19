#ifndef H2XVIDEO_MAIN_VIEW_HANDLER__H
#define H2XVIDEO_MAIN_VIEW_HANDLER__H

#include "h2xcore/h2x_view.h"
#include <QObject>
#include <qstring.h>
#include <QtQml>

class MainViewHandler : public QObject, public h2x::View {
    Q_OBJECT
public:
    // 以单例的方式提供给QML使用
    static MainViewHandler* qmlAttachedProperties(QObject *object);

    explicit MainViewHandler(QObject* parent = nullptr);
    virtual ~MainViewHandler();

    /*
     * FunctionName: routerPageSet
     * Desc: 设置路由页面
     */
    Q_INVOKABLE void routerPageSet(QString sender, QString pageId, QString pageParam = QString(""));

    /*
     * FunctionName: closeApp
     * Desc: 关闭APP
     * Author: zfs
     * Date: 2021-06-17 22:09
     * @sender: 发送者
     * @exitCode: 关闭代码
     */
    Q_INVOKABLE void closeApp(QString sender, int exitCode);


public:

    // 信号
Q_SIGNALS:
//signals:
    // 信号列表
    /*
     * FunctionName: routerPageChangeEvent
     * Desc: 路由页面改变事件
     * Author: zfs
     * Date: 2021-06-12 22:35
     * @sender: 发送者
     * @pageId: 页面ID
     * @pageParam: 页面参数，可以为空，
     */
    void routerPageChangeEvent(QString sender, QString pageId, QString pageParam = QString(""));



public slots:

private:
};

#endif // !H2XVIDEO_MAIN_VIEW_HANDLER__H
