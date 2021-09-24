#include "plugins/avcode/avcode.h"

#include "plugins/avcode/avcode_ffmpeg.h"
#include "h2xbase/h2x_error_code.h"
#include "plugins/avcode/avcode_option.h"

namespace h2x {

Avcode::Avcode() : last_code_(0)
{
}

Avcode::~Avcode() {
    if (avcode_.get()) {
        avcode_.release();
    }

    if (option_.get()) {
        option_.release();
    }
}

bool Avcode::open(const char* fileName, size_t fileNameSize) {
    last_code_ = ERROR_CODE_FAIL;
    if (!fileName) {
        last_code_ = ERROR_CODE_PARAM_ERROR;
        return false;
    }

    if (!fileNameSize) {
        fileNameSize = strlen(fileName);
    }

    if (!fileNameSize) {
        last_code_ = ERROR_CODE_PARAM_ERROR;
        return false;
    }

    // 编解码处理类对象
    avcode_.reset(new AvcodeFfmpeg());
    if (!avcode_.get()) {
        last_code_ = ERROR_CODE_ALLOC_FAIL;
        return ERROR_CODE_ALLOC_FAIL;
    }

    // 编解码选项类对象
    option_.reset(new AvcodeOption());

    bool bret = false;
    AVInputFormat* inputParam = NULL;
    // 初始化
    bret = avcode_->init(option_.get());
    if (!bret) {
        last_code_ = avcode_->getLastCode();
        return false;
    }

    // 打开
    bret = avcode_->open(fileName, fileNameSize, inputParam);
    if (!bret) {
        last_code_ = avcode_->getLastCode();
    }
    else {
        last_code_ = ERROR_CODE_SUCCESS;
    }

    return bret;
}

void Avcode::close() {
    if (avcode_.get()) {
        avcode_.reset(NULL);
    }
}

} // end namespace h2x
