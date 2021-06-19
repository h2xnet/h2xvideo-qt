#ifndef H2XVIDEO_MAIN_VIEW_HANDLER__H
#define H2XVIDEO_MAIN_VIEW_HANDLER__H

#include "h2xcore/h2x_view.h"
#include <QObject>
#include <qstring.h>
#include <QtQml>

class MainViewHandler : public QObject, public h2x::View {
    Q_OBJECT
public:
    // �Ե����ķ�ʽ�ṩ��QMLʹ��
    static MainViewHandler* qmlAttachedProperties(QObject *object);

    explicit MainViewHandler(QObject* parent = nullptr);
    virtual ~MainViewHandler();

    /*
     * FunctionName: routerPageSet
     * Desc: ����·��ҳ��
     */
    Q_INVOKABLE void routerPageSet(QString sender, QString pageId, QString pageParam = QString(""));

    /*
     * FunctionName: closeApp
     * Desc: �ر�APP
     * Author: zfs
     * Date: 2021-06-17 22:09
     * @sender: ������
     * @exitCode: �رմ���
     */
    Q_INVOKABLE void closeApp(QString sender, int exitCode);


public:

    // �ź�
Q_SIGNALS:
//signals:
    // �ź��б�
    /*
     * FunctionName: routerPageChangeEvent
     * Desc: ·��ҳ��ı��¼�
     * Author: zfs
     * Date: 2021-06-12 22:35
     * @sender: ������
     * @pageId: ҳ��ID
     * @pageParam: ҳ�����������Ϊ�գ�
     */
    void routerPageChangeEvent(QString sender, QString pageId, QString pageParam = QString(""));



public slots:

private:
};

#endif // !H2XVIDEO_MAIN_VIEW_HANDLER__H
