#include "h2xvideo/api/h2xvideo_api.h"

extern "C" {

#include "libavformat/avformat.h"

}

//
// init_library : 初如化库
//
int init_library() {
    int ret = -1;

    // 初始化网络环境，推流时需要（ffmpeg）
    ret = avformat_network_init();

    // 注册所有
    //av_register_all();

    return ret;
}

//
// uninit_library : 反初如化库
//
int uninit_library() {
    int ret = -1;

    ret = avformat_network_deinit();

    return ret;
}
