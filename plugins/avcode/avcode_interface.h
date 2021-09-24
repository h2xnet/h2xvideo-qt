#ifndef AVCODE_AVCODE_INTERFACE_H
#define AVCODE_AVCODE_INTERFACE_H

#include <string>
#include "plugins/avcode/avcode_export.h"

namespace h2x {

class AvcodeOption;

/*
 * ClassName: AvcodeInterface
 * Desc: 接口类
 * Author: zfs
 * Date: 2021-09-23 22:41
 */
class AVCODE_EXPORT AvcodeInterface
{
public:
    AvcodeInterface();
    virtual ~AvcodeInterface();

    virtual std::string getName() = 0;

    // 初始化
    virtual bool init(const AvcodeOption* opt) = 0;
    virtual bool open(const char* fileName, size_t fileNameSize, void* param = 0) = 0;
    virtual void close() = 0;

    virtual int getLastCode() const = 0;
    virtual const char* getLastMsg() = 0;

    virtual bool isOpen() = 0;

    // 播放控制

};

} // end namespace h2x

#endif // AVCODEINTERFACE_H
