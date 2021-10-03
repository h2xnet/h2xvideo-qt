#include "plugins/avcode/avcode_ffmpeg.h"

#include "h2xbase/h2x_error_code.h"
#include "plugins/avcode/avcode_option.h"

namespace h2x {


AvcodeFfmpeg::AvcodeFfmpeg() : inputAvFmtCtx_(NULL), last_code_(0), options_(NULL), is_open_(false)
{
    av_log_set_level(AV_LOG_INFO);
}

AvcodeFfmpeg::~AvcodeFfmpeg() {
    this->close();

    // 销毁字典
    if (options_) {
        av_dict_free(&options_);
        options_ = NULL;
    }
}

std::string AvcodeFfmpeg::getName() {
    return "avcode_ffmpeg";
}

bool AvcodeFfmpeg::init(const AvcodeOption* opt) {
    if (options_) {
        return true;
    }

    av_dict_set(&options_, "probesize", "4096", 0);
    av_dict_set(&options_, "video_size", "640x480", 0);
    av_dict_set(&options_, "pixel_format", "rgb24", 0);
    av_dict_set(&options_, "max_delay", "100", 0);  //指定最大延时100毫秒

    return true;
}

bool AvcodeFfmpeg::open(const char* fileName, size_t fileNameSize, void* param) {
    if (!fileName || !fileNameSize) {
        last_code_ = ERROR_CODE_PARAM_ERROR;
        return false;
    }

    this->close();

    // 分配内在
    inputAvFmtCtx_ = avformat_alloc_context();
    if (!inputAvFmtCtx_) {
        last_code_ = ERROR_CODE_ALLOC_FAIL;
        return false;
    }

    // 第四个参数用来填充AVFormatContext一些字段以及Demuxer的private选项
    last_code_ = avformat_open_input(&inputAvFmtCtx_, fileName, (AVInputFormat*)param, &options_);
    if (last_code_ != 0) {
        last_code_ = ERROR_CODE_FAIL;
        return false;
    }

    // 判断输入流是否有效
    if (!this->OnInputStreamValid()) {
        last_code_ = ERROR_CODE_NOT_VALID;
        return false;
    }

    // 打印输入流信息
    av_dump_format(inputAvFmtCtx_, 0, fileName, 0);

    is_open_ = true;

    last_code_ = ERROR_CODE_SUCCESS;
    return true;
}

void AvcodeFfmpeg::close() {
    if (inputAvFmtCtx_) {
        avformat_close_input(&inputAvFmtCtx_);
        inputAvFmtCtx_ = NULL;

        is_open_ = false;
    }
}

inline int AvcodeFfmpeg::getLastCode() const {
    return last_code_;
}

const char* AvcodeFfmpeg::getLastMsg() {
    return NULL;
}

bool AvcodeFfmpeg::isOpen() {
    return  is_open_;
}

bool AvcodeFfmpeg::OnInputStreamValid() {
    if (!inputAvFmtCtx_) {
        return false;
    }

    // 查找流信息（获取更多流信息）
    // avformat_find_stream_info主要用来获取必要的CODEC参数，设置到inputAvFmtCtx_->streams[i]->codec
    int status = avformat_find_stream_info(inputAvFmtCtx_, NULL);

    return status == 0 ? true : false;
}


bool AvcodeFfmpeg::OnGetVideoInfo(VideoInfo& info) {
    if (!inputAvFmtCtx_) {
        return false;
    }

    // 查找视频流信息
    int status = avformat_find_stream_info(inputAvFmtCtx_, NULL);
    if (status != 0) {
        return false;
    }

    // 视频流个数
    int streamNum = this->getInputAvFormatContext()->nb_streams;

    // 视频总秒数
    int secs = this->getInputAvFormatContext()->duration / 1000000;

    //  比特率
    int bitRates = this->getInputAvFormatContext()->bit_rate / 1000;

    // 流信息
    AVInputFormat* infoFmt = this->getInputAvFormatContext()->iformat;

    // 输入流名称
    const char* fmtName = infoFmt->name;

    info.streamNum = streamNum;
    info.secs = secs;
    info.bitRates = bitRates;

    for(int i = 0; i < streamNum; i++) {
        AVStream* inputStream = this->getInputAvFormatContext()->streams[i];

        if (inputStream->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            // 判断为视频
        }
        else if (inputStream->codecpar->codec_type == AVMEDIA_TYPE_AUDIO) {
            // 判断为音频
        }
    }

    return true;
}

int AvcodeFfmpeg::toFile(const char* fileName, size_t fileNameSize) {
    if (!fileName || !fileNameSize) {
        return ERROR_CODE_PARAM_ERROR;
    }

    // 判断输入流是否有效
    if (!inputAvFmtCtx_) {
        return ERROR_CODE_NOT_OPEN;
    }

    AVOutputFormat* outAvFmt = NULL;
    AVFormatContext* outAvFmtCtx = NULL;
    AVPacket pkt;
    int status = 0;

    // 创建输出上下文
    status = avformat_alloc_output_context2(&outAvFmtCtx, outAvFmt, NULL, fileName);
    if (status != 0 || !outAvFmtCtx) {
        return ERROR_CODE_ALLOC_FAIL;
    }

    int streamIndex = 0;
    int* streamMapping = NULL;
    int streamMappingSize = 0;

    streamMappingSize = inputAvFmtCtx_->nb_streams;
    streamMapping = (int*)av_mallocz_array(streamMappingSize, sizeof(*streamMapping));

    if (!streamMapping) {
        return ERROR_CODE_ALLOC_FAIL;
    }

    outAvFmt = outAvFmtCtx->oformat;

    // 创建并初始化输出流信息
    for (int i = 0; i < inputAvFmtCtx_->nb_streams; i++) {
        // copy输入音频流
        AVStream *outStream = NULL;
        AVStream *inStream = inputAvFmtCtx_->streams[i];
        AVCodecParameters *inAvCodecpar = inputAvFmtCtx_->streams[i]->codecpar;

        if (inAvCodecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
            inAvCodecpar->codec_type != AVMEDIA_TYPE_VIDEO &&
            inAvCodecpar->codec_type != AVMEDIA_TYPE_SUBTITLE) {
            streamMapping[i] = -1;
            continue;
        }

        streamMapping[i] = streamIndex++;
        // 创建输出流
        outStream = avformat_new_stream(outAvFmtCtx, NULL);

        if (!outStream) {
            return ERROR_CODE_ALLOC_FAIL;
        }

        // 拷贝编解码参数
        status = avcodec_parameters_copy(outStream->codecpar, inAvCodecpar);
        if (status < 0) {
            return ERROR_CODE_FAIL;
        }

        outStream->codecpar->codec_tag = 0;
    }

    // 打印输出流信息
    av_dump_format(outAvFmtCtx, 0, fileName, 1);

    if (!(outAvFmt->flags & AVFMT_NOFILE)) {
        // 如果没有，则创建输出文件
        status = avio_open(&outAvFmtCtx->pb, fileName, AVIO_FLAG_WRITE);
        if (status < 0) {
            return ERROR_CODE_FAIL;
        }
    }

    // 写入输出文件haeder
    status = avformat_write_header(outAvFmtCtx, NULL);
    if (status < 0) {
        return ERROR_CODE_FAIL;
    }

    status = 0;
    while (1) {
        AVStream *inStream = NULL, *outStream = NULL;
        // 读取一帧
        status = av_read_frame(inputAvFmtCtx_, &pkt);
        if (status < 0) {
            break;
        }

        inStream = inputAvFmtCtx_->streams[pkt.stream_index];

        if (pkt.stream_index >= streamMappingSize || streamMapping[pkt.stream_index] < 0) {
            av_packet_unref(&pkt);
            continue;
        }

        pkt.stream_index = streamMapping[pkt.stream_index];
        outStream = outAvFmtCtx->streams[pkt.stream_index];

        // 打印帧信息
        OnLogPacket(inputAvFmtCtx_, &pkt, "in");

        // 刻度转化 转化时间基
        pkt.pts = av_rescale_q_rnd(pkt.pts, inStream->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        pkt.dts = av_rescale_q_rnd(pkt.dts, inStream->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        pkt.duration = av_rescale_q(pkt.duration, inStream->time_base, outStream->time_base);
        pkt.pos = -1;

        // 打印日志
        OnLogPacket(outAvFmtCtx, &pkt, "out");

        status = av_interleaved_write_frame(outAvFmtCtx, &pkt);
        if (status < 0) {
            break;
        }
        av_packet_unref(&pkt);

        // 如果为停止状态，则退出
        if (this->getStop()) {
            break;
        }
    }

    // 写结束符号
    last_code_ = av_write_trailer(outAvFmtCtx);

    if (outAvFmtCtx && !(outAvFmt->flags & AVFMT_NOFILE)) {
        avio_closep(&outAvFmtCtx->pb);
    }

    if (outAvFmtCtx) {
        avformat_free_context(outAvFmtCtx);
        outAvFmtCtx = NULL;
    }

    if (streamMapping) {
        av_freep(&streamMapping);
        streamMapping = NULL;
    }

    if (status < 0 && status != AVERROR_EOF) {
        //av_log(NULL, AV_LOG_ERROR, "文件解析出现异常:%s\n", av_err2str(ret));
        return ERROR_CODE_FAIL;
    }
    return ERROR_CODE_SUCCESS;
}

int AvcodeFfmpeg::toPushFlow(const char*url, const char* formatName) {
    // rtmp 推流必须推送 flv 封装格式，udp 推流必须推送 mpegts 封装格式，其他情况就当作是输出普通文件
    if (!url || strlen(url) < 5 || !formatName) {
        return ERROR_CODE_PARAM_ERROR;
    }

    if (!inputAvFmtCtx_) {
        return ERROR_CODE_NOT_OPEN;
    }

    int status = -1;

    // 创建输出流
    AVFormatContext* outAvFmtCtx = NULL;
    AVOutputFormat* outAvFmt = NULL;

    status = avformat_alloc_output_context2(&outAvFmtCtx, outAvFmt, formatName, url);
    if (status != 0 || !outAvFmtCtx) {
        return ERROR_CODE_ALLOC_FAIL;
    }

    int streamIndex = 0;
    int* streamMapping = NULL;
    int streamMappingSize = 0;

    streamMappingSize = inputAvFmtCtx_->nb_streams;
    streamMapping = (int*)av_mallocz_array(streamMappingSize, sizeof(*streamMapping));

    if (!streamMapping) {
        return ERROR_CODE_ALLOC_FAIL;
    }

    outAvFmt = outAvFmtCtx->oformat;

    // 创建并初始化输出流信息
    for (int i = 0; i < inputAvFmtCtx_->nb_streams; i++) {
        // copy输入音频流
        AVStream *outStream = NULL;
        AVStream *inStream = inputAvFmtCtx_->streams[i];
        AVCodecParameters *inAvCodecpar = inputAvFmtCtx_->streams[i]->codecpar;

        if (inAvCodecpar->codec_type != AVMEDIA_TYPE_AUDIO &&
            inAvCodecpar->codec_type != AVMEDIA_TYPE_VIDEO &&
            inAvCodecpar->codec_type != AVMEDIA_TYPE_SUBTITLE) {
            streamMapping[i] = -1;
            continue;
        }

        streamMapping[i] = streamIndex++;

        // 创建输出流
        outStream = avformat_new_stream(outAvFmtCtx, NULL);

        if (!outStream) {
            return ERROR_CODE_ALLOC_FAIL;
        }

        // 拷贝编解码参数
        status = avcodec_parameters_copy(outStream->codecpar, inAvCodecpar);
        if (status < 0) {
            return ERROR_CODE_FAIL;
        }

        outStream->codecpar->codec_tag = 0;
    }

    // 打印输出流信息
    av_dump_format(outAvFmtCtx, 0, url, 1);

    //rtmp推流
    status = avio_open(&outAvFmtCtx->pb, url, AVIO_FLAG_WRITE);
    if (status < 0 || !outAvFmtCtx->pb) {
        return ERROR_CODE_OPEN_FAIL;
    }

    // 写入头信息
    status = avformat_write_header(outAvFmtCtx, NULL);
    if (status < 0) {
        return ERROR_CODE_FAIL;
    }

    AVPacket pkt;
    long long startTime = av_gettime();

    while (1) {
        AVStream *inStream = NULL, *outStream = NULL;

        // 读取一帧
        status = av_read_frame(inputAvFmtCtx_, &pkt);
        if (status < 0) {
            break;
        }

        inStream = inputAvFmtCtx_->streams[pkt.stream_index];

        if (pkt.stream_index >= streamMappingSize || streamMapping[pkt.stream_index] < 0) {
            av_packet_unref(&pkt);
            continue;
        }

        pkt.stream_index = streamMapping[pkt.stream_index];
        outStream = outAvFmtCtx->streams[pkt.stream_index];

        // 打印帧信息
        OnLogPacket(inputAvFmtCtx_, &pkt, "in");

        // 刻度转化 转化时间基
        pkt.pts = av_rescale_q_rnd(pkt.pts, inStream->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        pkt.dts = av_rescale_q_rnd(pkt.dts, inStream->time_base, outStream->time_base, (AVRounding)(AV_ROUND_NEAR_INF | AV_ROUND_PASS_MINMAX));
        pkt.duration = av_rescale_q(pkt.duration, inStream->time_base, outStream->time_base);
        pkt.pos = -1;

        // 视频帧推送速度，即增加延迟，以播放速度推，否则服务器受不了
        if (inputAvFmtCtx_->streams[pkt.stream_index]->codecpar->codec_type == AVMEDIA_TYPE_VIDEO) {
            AVRational tb = inputAvFmtCtx_->streams[pkt.stream_index]->time_base;
            // 已经过去的时间
            long long now = av_gettime() - startTime;
            long long dts = 0;
            dts = pkt.dts * (1000 * 1000 * this->OnR2d(tb));

            if (dts > now) {
                av_usleep(dts - now);
            }
        }

        // 打印日志
        OnLogPacket(outAvFmtCtx, &pkt, "out");

        status = av_interleaved_write_frame(outAvFmtCtx, &pkt);
        if (status < 0) {
            break;
        }
        av_packet_unref(&pkt);

        // 如果为停止状态，则退出
        if (this->getStop()) {
            break;
        }
    }

    // 写结束符号
    last_code_ = av_write_trailer(outAvFmtCtx);

    // 关闭输出
    if (outAvFmtCtx && !(outAvFmt->flags & AVFMT_NOFILE)) {
        avio_closep(&outAvFmtCtx->pb);
    }

    if (outAvFmtCtx) {
        avformat_free_context(outAvFmtCtx);
        outAvFmtCtx = NULL;
    }

    if (streamMapping) {
        av_freep(&streamMapping);
        streamMapping = NULL;
    }

    if (status < 0 && status != AVERROR_EOF) {
        //av_log(NULL, AV_LOG_ERROR, "文件解析出现异常:%s\n", av_err2str(ret));
        return ERROR_CODE_FAIL;
    }
    return ERROR_CODE_SUCCESS;
}

inline char* AvcodeFfmpeg::OnAvTsMakeTimeString(char *buf, int64_t ts, AVRational *tb)
{
    if (!buf) {
        return NULL;
    }
    if (ts == AV_NOPTS_VALUE)
        snprintf(buf, AV_TS_MAX_STRING_SIZE, "NOPTS");
    else
        snprintf(buf, AV_TS_MAX_STRING_SIZE, "%.6g", av_q2d(*tb) * ts);
    return buf;
}

inline char* AvcodeFfmpeg::OnAvTsMakeString(char *buf, int64_t ts)
{
    if (!buf) {
        return NULL;
    }
    if (ts == AV_NOPTS_VALUE)
        snprintf(buf, AV_TS_MAX_STRING_SIZE, "NOPTS");
    else
        snprintf(buf, AV_TS_MAX_STRING_SIZE, "%" PRId64, ts);
    return buf;
}


double AvcodeFfmpeg::OnR2d(AVRational r) {
    return r.num == 0 || r.den == 0 ? 0. : (double)r.num / (double)r.den;
}

void AvcodeFfmpeg::OnLogPacket(const AVFormatContext *avFmtCtx, const AVPacket *pkt, const char *tag) {
    AVRational *time_base = &avFmtCtx->streams[pkt->stream_index]->time_base;

    char av_error[AV_TS_MAX_STRING_SIZE] = { 0 };
    char * pp = this->OnAvTsMakeTimeString(av_error, pkt->pts, time_base);

    printf("%s: pts:%s pts_time:%s dts:%s dts_time:%s duration:%s duration_time:%s stream_index:%d\n",
        tag,
        this->OnAvTsMakeString(av_error, pkt->pts),
        this->OnAvTsMakeTimeString(av_error,pkt->pts, time_base),
        this->OnAvTsMakeString(av_error, pkt->dts),
        this->OnAvTsMakeTimeString(av_error, pkt->dts, time_base),
        this->OnAvTsMakeString(av_error, pkt->duration),
        this->OnAvTsMakeTimeString(av_error, pkt->duration, time_base),
        pkt->stream_index);
}

} // end namespace h2x
