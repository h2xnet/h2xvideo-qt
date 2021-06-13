#ifndef H2XCORE_H2X_CONFIG__H
#define H2XCORE_H2X_CONFIG__H

#include <string>
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Middleware;

/*
    * ClassName: Config
    * Desc: �����࣬�����������ɵ���һ��JSON�ַ���������������ļ����кϲ�����
    * �����app_config.json����agent_config.json�ļ���
    * Author: zfs
    * Date: 2021-05-16 17:17
    */
class H2XCORE_EXPORT Config {
public:
    Config();
    virtual ~Config();

public:
    // �������л�������������Ϊprod����Ԫ���Ի���Ϊunittest�����ؿ�������Ϊlocal���
    // ��ͬ�Ļ������ӦconfigĿ¼�²�ͬ�������ļ�
    std::string env_;

    // �˴����õ���ȫ���м�����ֲ��м��ֱ����·��������
    // ��ܲ��м��
    Middleware* core_middleware_;

    // Ӧ�ò��м��
    Middleware* app_middleware_;

};

} // end namespace h2x

#endif // !H2XCORE_H2X_CONFIG__H
