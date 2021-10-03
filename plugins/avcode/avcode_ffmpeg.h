#ifndef AVCODE_AVCODE_FFMPEG_H
#define AVCODE_AVCODE_FFMPEG_H

extern "C" {

#include "libavcodec/avcodec.h"
#include "libavformat/avformat.h"
#include "libavutil/timestamp.h"
#include "libavutil/time.h"

}

//#include <string>
//#include "plugins/avcode/avcode_export.h"
#include "plugins/avcode/avcode_interface.h"

namespace h2x {

class AvcodeOption;

/*
 * ClassName: AvcodeFfmpeg
 * Desc: ffmpeg音视频编解码
 * Author: zfs
 * Date: 2021-09-12 11:10
 */
class AVCODE_EXPORT AvcodeFfmpeg : public AvcodeInterface
{
public:

    // video_info_ : 视频流信息
    typedef struct video_info_ {
        video_info_() {
            streamNum = 0;
            secs = 0;
            bitRates = 0;
        }

        int streamNum;  //流个数
        int secs;   // 总秒数
        int bitRates;    // 比特率
    } VideoInfo;

    explicit AvcodeFfmpeg();
    virtual ~AvcodeFfmpeg();

    virtual std::string getName() override;

    /*
     * Function: init
     * Desc: 初始化
     * Author: zfs
     * Date: 2021-09-23 22:23
     * @opt: 初始化参数类
     * 返回值：成功返回true，失败返回false
     */
    virtual bool init(const AvcodeOption* opt) override;

    /*
     * Function: open
     * Desc: 打开指定文件
     * Author: zfs
     * Date: 2021-09-23 22:24
     * @fileName: 要打开的文件名称（可以是本地文件，也可以是网络文件）
     * @fileNameSize: 文件名大小
     * @param: 输入文件格式，可以为空，如果为空，则自动检测输入文件格式
     * 返回值：成功返回true，失败返回false
     */
    virtual bool open(const char* fileName, size_t fileNameSize, void* param = nullptr) override;

    /*
     * Function: close
     * Desc: 关闭已经打开的文件
     * Author: zfs
     * Date: 2021-09-23 22:25
     */
    virtual void close() override;

    virtual int getLastCode() const override;

    virtual const char* getLastMsg() override;

    virtual bool isOpen() override;

    void setStop(bool val) {
        stop_ = val;
    }

    bool getStop() const {
        return stop_;
    }

    /*
     * FunctionName: toFile
     * Description: 保存到文件
     * Author: fushou
     * Date: 2021-04-03 22:24
     * @fileName: 保存的文件名
     * @fileNameSize: 文件名长度
     * 返回值，成功返回0，失败返回错误码
     */
    int toFile(const char* fileName, size_t fileNameSize);

    /*
     * FunctionName: toPushFlow
     * Description: 进行推流
     * Author: fushou
     * Date: 2021-04-04 16:42
     * @fileName: 保存的文件名
     * @fileNameSize: 文件名长度
     * 返回值，成功返回0，失败返回错误码
     */
    int toPushFlow(const char*url, const char* formatName = "flv");

    AVFormatContext* getInputAvFormatContext() const {
        return inputAvFmtCtx_;
    }

    /*
     * FunctionName: OnGetVideoInfo
     * Desc: 获取视频信息
     * Author: fushou
     * Date: 2021-03-28 17:33
     */
    bool OnGetVideoInfo(VideoInfo& info);

    /*
     * FunctionName: OnAvTsMakeTimeString
     * Description: av_ts2timestr库函数的自实现
     * Author: fushou
     * Date: 2021-04-04 10:40
     */
    char* OnAvTsMakeTimeString(char *buf, int64_t ts, AVRational *tb);

    /*
     * FunctionName: OnAvTsMakeTimeString
     * Description: av_ts2str库函数的自实现
     * Author: fushou
     * Date: 2021-04-04 10:40
     */
    char* OnAvTsMakeString(char *buf, int64_t ts);

    double OnR2d(AVRational r);

private:
    friend class Avcode;

    /*
     * FunctionName: OnInputStreamValid
     * Description: 判断输入流是否有效
     * Author: fushou
     * Date: 2021-09-12 16：28
     * 返回值：有效返回true，否则返回false
     */
    bool OnInputStreamValid();

    /*
     * FunctionName: OnLogPacket
     * Description: 打印包日志
     */
    void OnLogPacket(const AVFormatContext *avFmtCtx, const AVPacket *pkt, const char *tag);

    // 打开成功标志
    bool is_open_;

    // 停止标志，通常用在保存网络流或推流过程中
    bool stop_;

    // 最后返回码
    int last_code_;

    // 输入格式指针
    AVFormatContext* inputAvFmtCtx_;

    // 输入选项,可用于配置参数
    AVDictionary* options_;

};

}

#endif // AVCODE_AVCODE_FFMPEG_H
