#ifndef H2XCORE_H2X_PLUGIN__H
#define H2XCORE_H2X_PLUGIN__H

#include <string>
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Option;

/*
* ClassName: Plugin
* Desc: ����࣬ÿһ������ᵥ��������һ���߳���
* Author: zfs
* Date: 2021-05-16 17:31
*/
class H2XCORE_EXPORT Plugin {
public:
    Plugin();
    virtual ~Plugin();

    /*
     * FunctionName: getName
     * Desc: ��������
     * Author: zfs
     * Date: 2021-06-06 08:24
     */
    virtual std::string getName() = 0;

    virtual bool init(const Option* opt) = 0;

    virtual bool open() = 0;

    virtual void close() = 0;

    virtual void error(int errorno, const std::string& errormsg) = 0;

    virtual bool isOpen() = 0;

};

} // end namespace h2x

#endif // !H2XCORE_H2X_PLUGIN__H
