#ifndef H2XCORE_H2X_LISTEN__H
#define H2XCORE_H2X_LISTEN__H

#include "h2xcore/h2x_plugin.h"
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Option;

/*
* ClassName: Listen
* Desc:������
* Author: zhaofushou
* Date: 2021-06-03 22:51
*/
class H2XCORE_EXPORT Listen : public Plugin {
public:
    Listen();
    virtual ~Listen();

    virtual int send(const char* data, size_t size) = 0;

    virtual int recv(unsigned char* buffer, size_t bufferSize) = 0;

    /*
     * FunctionName: isRunning
     * Desc: ���ؼ���������״̬��true������������,false�����Ѿ�ֹͣ����
     */
    virtual bool isRunning() = 0;

    /*
     * FunctionName: working
     * Desc: �̹߳��̺���
     * Author: zfs
     * Date: 2021-06-06 18:06
     */
    virtual void working() = 0;

};

} // end namespace h2x

#endif // !H2XCORE_H2X_LISTEN__H
