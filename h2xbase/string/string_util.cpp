#include "h2xbase/string/string_util.h"

#include "h2xbase/time/time.h"
#include <stdarg.h>


namespace h2x {

StringUtil::StringUtil() {

}

StringUtil::~StringUtil() {

}


bool StringUtil::StringPrintf(StringResult<PathChar>& result, const char *format, ...) {
    va_list ap;
    va_start(ap, format);
    int count_write = _vscprintf(format, ap); //snprintf(NULL, 0, format, ap);
    va_end(ap);
    if (count_write <= 0) {
        return false;
    }

    count_write += sizeof(PathChar);

    std::unique_ptr<PathChar[]> dataPtr(new PathChar[count_write]{ '\0' });
    if (!dataPtr.get()) {
        return false;
    }

    va_start(ap, format);
    int ret = vsprintf_s(dataPtr.get(), count_write, format, ap);
    va_end(ap);

    result.SetData(dataPtr.get(), ret);

    dataPtr.release();
    return true;
}

bool StringUtil::StringPrintfW(StringResult<PathWChar>& result, const wchar_t *format, ...) {

    va_list ap;
    va_start(ap, format);
    int count_write = _vscwprintf(format, ap);
    va_end(ap);
    if (count_write <= 0) {
        return false;
    }

    count_write += sizeof(PathWChar);

    std::unique_ptr<PathWChar[]> dataPtr(new PathWChar[count_write]{ 0 });
    if (!dataPtr.get()) {
        return false;
    }

    va_start(ap, format);
    int ret = vswprintf_s(dataPtr.get(), count_write, format, ap);
    va_end(ap);

    result.SetData(dataPtr.get(), ret);

    dataPtr.release();

    return true;
}

bool StringUtil::GetNowDateString(StringResult<PathChar>& result) {
    h2x::Time ct = h2x::Time::Now();
    h2x::Time::TimeStruct tms = ct.ToTimeStruct(true);
    char szData[256] = {'\0'};
    int ret = sprintf(szData, "%04d-%02d-%02d", tms.year(), tms.month(), tms.day_of_month());
    result.SetData(szData, ret);
    return true;
}

bool StringUtil::GetNowDateStringW(StringResult<PathWChar>& result) {
    h2x::Time ct = h2x::Time::Now();
    h2x::Time::TimeStruct tms = ct.ToTimeStruct(true);
    wchar_t szData[256] = {'\0'};
    int ret = wsprintf(szData, L"%04d-%02d-%02d", tms.year(), tms.month(), tms.day_of_month());

    result.SetData(szData, ret);
    return true;
}

bool StringUtil::GetNowDatetimeString(StringResult<PathChar>& result) {
    h2x::Time ct = h2x::Time::Now();
    h2x::Time::TimeStruct tms = ct.ToTimeStruct(true);
    char szData[256] = {'\0'};
    int ret = sprintf(szData, "%04d-%02d-%02d %02d:%02d:%02d.%d", tms.year(), \
                      tms.month(), tms.day_of_month(), tms.hour(), tms.minute(), \
                      tms.second(), tms.millisecond());
    result.SetData(szData, ret);
    return true;
}

bool StringUtil::GetNowDatetimeStringW(StringResult<PathWChar>& result) {
    h2x::Time ct = h2x::Time::Now();
    h2x::Time::TimeStruct tms = ct.ToTimeStruct(true);
    wchar_t szData[256] = {'\0'};
    int ret = wsprintf(szData, L"%04d-%02d-%02d %02d:%02d:%02d.%d", tms.year(), \
                      tms.month(), tms.day_of_month(), tms.hour(), tms.minute(), \
                      tms.second(), tms.millisecond());
    result.SetData(szData, ret);
    return true;
}

bool StringUtil::GetDateLoggerFileNameW(const PathWString& prefix, StringResult<PathWChar>& result) {
    h2x::Time ct = h2x::Time::Now();
    h2x::Time::TimeStruct tms = ct.ToTimeStruct(true);
    wchar_t szData[520] = {0};
    int ret = 0;

    if (prefix.empty()) {
        // 没有前缀
        ret = wsprintf(szData, L"%04d_%02d_%02d.log", tms.year(), tms.month(), tms.day_of_month());
    }
    else {
        // 有前缀
        ret = wsprintf(szData, L"%s_%04d_%02d_%02d.log", prefix.c_str(), tms.year(), tms.month(), tms.day_of_month());
    }
    result.SetData(szData, ret);
    return true;
}


} // end namespace h2x
