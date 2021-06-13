#ifndef H2XCORE_H2X_LISTEN_TABLE__H
#define H2XCORE_H2X_LISTEN_TABLE__H

#include "h2xbase/h2x_map_table.h"
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Listen;

/*
* ClassName: ListenTable
* Desc: ������ע���
* Author: zfs
* Date: 2021-06-06 09:43
*/
class H2XCORE_EXPORT ListenTable {
public:
    ListenTable();
    virtual ~ListenTable();

    /*
     * FunctionName: regist
     * Desc: ע��һ��������
     * Author: zfs
     * Date: 2021-06-06 09:50
     * @name: ����������
     * @value: ������ָ��
     * @replace: ����Ѿ����ڣ����Ƿ��滻��־��true��ʾ�滻��false��ʾ���滻
     * @isDelete: ���replaceΪtrueʱ���Ƿ�ɾ����־
     * ����ֵ���ɹ�����true��ʧ�ܷ���false
     */
    bool regist(const std::string& name, const Listen* value, bool replace = true, bool isDelete = true);

    /*
     * FunctionName: unregist
     * Desc: ע��һ��������
     * Author: zfs
     * Date: 2021-06-06 10:35
     * @name: ����������
     * @isDelete: �Ƿ�ɾ����־
     */
    void unregist(const std::string& name, bool isDelete = true);

    /*
     * FunctionName: get
     * Desc: ��ѯָ��������
     * Author: zfs
     * Date: 2021-06-06 10:37
     * @name: ����������
     */
    Listen* get(const std::string& name);

private:
    typedef PtrMapTable<std::string> ListenTableType;

    ListenTableType list_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_LISTEN_TABLE__H
