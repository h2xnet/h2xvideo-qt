#ifndef H2XBASE_LOGGER_H2X_LOGGER__H
#define H2XBASE_LOGGER_H2X_LOGGER__H

#include <memory>
#include <mutex>
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/file/file.h"
#include "h2xbase/string/string_result.h"

namespace h2x {

/*
* ClassName: Logger
* Desc: ��־��
* Author: zfs
* Date: 2021-05-16 17:25
*/
class H2XBASE_EXPORT Logger {
public:
    // ��־�ļ����ͣ���ͬ���Ͷ�Ӧ��ͬ��־�ļ���
    enum LoggerType {
        Default, // Ĭ�����ͣ���Ӧ��ǰ�����ļ�
        Frame // �����־
    };

    // ��־��������
    enum ContentType {
        OFF = 0, //�ر���־
        Debug, // ����
        Info, // ��Ϣ
        Warn, // �澯
        Error, // ����
        Fatal // ���ش���
    };
    
    Logger();
    virtual ~Logger();

    virtual int debug(const char* format, ...);
    virtual int debugw(const wchar_t* format, ...);

    virtual int info(const char* format, ...);
    virtual int infow(const wchar_t* format, ...);

    virtual int warn(const char* format, ...);
    virtual int warnw(const wchar_t* format, ...);

    virtual int error(const char* format, ...);
    virtual int errorw(const wchar_t* format, ...);
    
    virtual int fatal(const char* format, ...);
    virtual int fatalw(const wchar_t* format, ...);

    /*
     * FunctionName: PrintLog / PrintLogW
     * Desc: ��ʽ����ӡ��־
     * Author: zhaofushou
     * Date: 2021-05-29 16:39
     * ����ֵ������ʵ�ʴ�ӡ����־�ֽ��������������ض���׷�ӵ���Ϣ
     */
    int PrintLog(ContentType contentType, const char* format, ...);
    int PrintLogW(ContentType contentType, const wchar_t* format, ...);

    /*
     * FunctionName: GetPrefix
     * Desc: ��ȡ��־�ļ�ǰ׺��
     * Author: zhaofushou
     * Date: 2021-05-29 15:36
     */
    virtual bool GetPrefix(StringResult<PathWChar>& result);

    /*
     * FunctionName: SetLoggerType
     * Desc: ������־�ļ�����
     * Author: zhaofushou
     * Date: 2021-05-29 15:14
     */
    void SetLoggerType(LoggerType type) {
        log_type_ = type;
    }

    LoggerType GetLoggerType() const {
        return log_type_;
    }

    /*
     * FunctionName: GetContentType
     * Desc: ��ȡ��־��������
     * Author: zhaofushou
     * Date: 2021-05-29 16:02
     */
    ContentType GetContentType() const {
        return content_type_;
    }

protected:

    size_t GetModulePathSize() const {
        return module_path_size_;
    }

private://
    // OnOpenFile : ���ļ�
    //
    bool OnOpenFile();

    //
    // OnCloseFile : �ر��ļ�
    //
    void OnCloseFile();

    //
    // OnShouldSave : �ж��Ƿ���Ҫ����
    //
    bool OnShouldSave(const ContentType& contentType);

    // ��־�ļ�����
    LoggerType log_type_;

    // ��־��������
    ContentType content_type_;

    // ģ��·��
    PathWChar module_path_[2 * MAX_PATH];
    size_t module_path_size_;

    // �߳�ͬ����
    std::mutex mutex_;
    //std::unique_lock<std::mutex> lock_;

    // ��־�ļ�����
    h2x::File file_;
};

} // end namespace h2x

#endif // !H2XBASE_LOGGER_H2X_LOGGER__H
