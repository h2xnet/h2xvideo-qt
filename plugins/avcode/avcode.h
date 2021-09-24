#ifndef AVCODE_H
#define AVCODE_H

#include <memory>
#include "h2xcore/h2x_plugin.h"
#include "plugins/avcode/avcode_export.h"

namespace h2x {

// 解码器状态
enum AvcodeState {
    eStop = 0, // 停止
    eRunning, // 运行
    ePause // 暂停
};

class AvcodeInterface;
class AvcodeOption;

class AVCODE_EXPORT Avcode
{
public:
    Avcode();
    virtual ~Avcode();

    /*
     * Function: open
     * Desc: 打开
     * Author: zfs
     * Date: 2021-0-13 22:35
     */
    bool open(const char* fileName, size_t fileNameSize);

    /*
     * Function: close
     * Desc: 关闭
     * Author: zfs
     * Date: 2021-0-13 22:35
     */
    void close();

    int getLastCode() const {
        return last_code_;
    }

    AvcodeState getAvocdeState() const {
        return avcode_state_;
    }

    void setAvcodeState(AvcodeState state) {
        avcode_state_ = state;
    }


private:
    // 最后错误码
    int last_code_;

    // 当前解码状态
    AvcodeState avcode_state_;

    // 解码指针
    std::unique_ptr<AvcodeInterface> avcode_;

    // 初始化选项
    std::unique_ptr<AvcodeOption> option_;

};


} // end namespace h2x

#endif // AVCODE_H
