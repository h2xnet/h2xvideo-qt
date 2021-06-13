#ifndef H2XVIDEO_CACHE_ROUTER_CACHE__H
#define H2XVIDEO_CACHE_ROUTER_CACHE__H

#include <list>
#include <qstring.h>

/*
 * ClassName: RouterCache
 * Desc: ·�ɻ��棬���ڴ洢ҳ��·����ʷ��¼���߼�������س���
 * Author: zfs
 * Date: 2021-06-12 22:55
 */
class RouterCache {
public:
    typedef struct RouterNode_ {
        RouterNode_(QString name, QString param) {
            if (!name.isEmpty()) {
                pageName = QString::fromUtf8(name.toUtf8().data(), name.toUtf8().size());
            }
            if (!param.isEmpty()) {
                pageParam = QString::fromUtf8(param.toUtf8().data(), param.toUtf8().size());
            }
        }

        QString pageName; // ҳ������
        QString pageParam; // ҳ�����
    } RouterNode;

    typedef std::list<RouterNode> RouterListType;
    typedef std::list<RouterNode>::iterator RouterListIterator;

    RouterCache();
    virtual ~RouterCache();

    /*
     * FunctionName: pushBack
     * Desc: ĩβ׷��һ����¼
     * Author: zfs
     * Date: 2021-06-12 23:06
     */
    bool pushBack(QString pageName, QString pageParam = QString(""));

    /*
     * FunctionName: peekFront
     * Desc: ���ͷ���أ�����ɾ��
     * Author: zfs
     * Date: 2021-06-12 23:17
     */
    bool peekFront(RouterNode& node);

    /*
     * FunctionName: popFront
     * Desc: ���ͷԪ�أ�����ɾ��
     * Author: zfs
     * Date: 2021-06-12 23:18
     */
    bool popFront(RouterNode& node);

    bool isEmpty() {
        return list_.empty();
    }

    bool isFull() {
        return (list_.size() == max_count_);
    }

private:
    /*
     * FunctionName: OnReCal
     * Desc: ������ˣ������µ�����ɾ�����ּ�¼
     * Author: zfs
     * Date: 2021-06-12 23:11
     */
    void OnReCal();

    // ����¼����
    int max_count_;

    // �����б�
    RouterListType list_;
};

#endif // !H2XVIDEO_CACHE_ROUTER_CACHE__H
