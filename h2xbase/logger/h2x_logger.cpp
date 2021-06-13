#include "h2xbase/logger/h2x_logger.h"

#include "h2xbase/string/string_util.h"
#include "h2xbase/h2x_error_code.h"

namespace h2x {

Logger::Logger() : module_path_size_(0), log_type_(Default), content_type_(Info) {

}

Logger::~Logger() {

}

inline bool Logger::OnShouldSave(const ContentType& contentType) {
    if (OFF == contentType || this->GetContentType() > contentType) {
        return false;
    }
    return true;
}

bool Logger::GetPrefix(StringResult<PathWChar>& result) {
    switch (log_type_) {
    case Frame: {
        // �����־
        const PathWChar* prefix = L"frame";
        result.SetData(prefix, wcslen(prefix));
    }break;

    default: {
        result.SetData(NULL, 0);
    }break;

    }
    return true;
}

int Logger::debug(const char* format, ...) {
    return 0;
}

int Logger::debugw(const wchar_t* format, ...) {
    return 0;
}

int Logger::info(const char* format, ...) {
    return 0;
}

int Logger::infow(const wchar_t* format, ...) {
    return 0;
}

int Logger::warn(const char* format, ...) {
    return 0;
}

int Logger::warnw(const wchar_t* format, ...) {
    return 0;
}

int Logger::error(const char* format, ...) {
    return 0;
}

int Logger::errorw(const wchar_t* format, ...) {
    return 0;
}

int Logger::fatal(const char* format, ...) {
    return 0;
}

int Logger::fatalw(const wchar_t* format, ...) {
    return 0;
}

int Logger::PrintLog(ContentType contentType, const char* format, ...) {
    // �жϵ�ǰ��ӡ���������ͣ�ȷ���Ƿ���Ҫ����
    if (!this->OnShouldSave(contentType)) {
        return ERROR_CODE_SUCCESS;
    }

    std::unique_lock<std::mutex> lock(mutex_);
    // ���ļ�
    if (!this->OnOpenFile()) {
        return ERROR_CODE_FAIL;
    }

    // ��ӡǰ׺
    StringResult<PathChar> dt;
    StringUtil::GetNowDatetimeString(dt);
    std::string strDt(dt.GetData(), dt.GetDataSize());

    file_.Print("%s ", strDt.c_str());
    // ��ӡ����
    va_list ap;
    va_start(ap, format);
    int status = file_.Print(format, ap);
    va_end(ap);
    // �ر��ļ�
    this->OnCloseFile();
    return status;
}

int Logger::PrintLogW(ContentType contentType, const wchar_t* format, ...) {
    if (!this->OnShouldSave(contentType)) {
        return ERROR_CODE_SUCCESS;
    }

    std::unique_lock<std::mutex> lock(mutex_);
    // ���ļ�
    if (!this->OnOpenFile()) {
        return ERROR_CODE_FAIL;
    }
    // ��ӡǰ׺
    StringResult<PathChar> dt;
    StringUtil::GetNowDatetimeString(dt);
    std::string strDt(dt.GetData(), dt.GetDataSize());

    // ��ӡ����
    va_list ap;
    va_start(ap, format);
    int status = file_.PrintW(format, ap);
    va_end(ap);
    // �ر��ļ�
    this->OnCloseFile();
    return status;
}

bool Logger::OnOpenFile() {
    if (!this->GetModulePathSize()) {
        // ��ʼ��ģ��
        PathWChar path[2 * MAX_PATH] = { 0 };
        int pathSize = 0;
        if (!FilePath::GetModulePathW(path, 2 * MAX_PATH, pathSize)) {
            return false;
        }
        // ����ģ����
        wcsncpy_s(module_path_, 2 * MAX_PATH, path, pathSize);
        module_path_size_ = pathSize;
    }

    // ������ȫ·���ļ���
    // ��ȡǰ׺
    StringResult<PathWChar> prefix;
    if (!this->GetPrefix(prefix)) {
        return false;
    }

    // ��־�ļ���
    StringResult<PathWChar> fileName;
    if (!StringUtil::GetDateLoggerFileNameW(std::wstring(prefix.GetData(), prefix.GetDataSize()), fileName)) {
        return false;
    }

    // ��ȫ·���ļ���
    PathWString fullFileName = PathWString(module_path_, module_path_size_) + PathWString(L"\\") + PathWString(fileName.GetData(), fileName.GetDataSize());

    // ׷��ģʽ����־�ļ�
    return file_.Open(fullFileName.c_str(), L"a+");
}

void Logger::OnCloseFile() {
    file_.Close();
}


} // end namespace h2x