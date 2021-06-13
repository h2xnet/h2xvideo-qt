#ifndef H2XBASE_CRASH_CRASH_WIN__H
#define H2XBASE_CRASH_CRASH_WIN__H

#include "build/build_config.h"
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/crash/crash_handler.h"

#ifdef  OS_WIN
#include <Windows.h>
#endif //  OS_WIN

namespace h2x {

/*
 * ClassName: CrashWin
 * Description: Windows����������
 * Author: zfs
 * Date: 2021-05-16 09:02
 */
class H2XBASE_EXPORT CrashWin {
public:
    /*
     * ExceptionLevel: �쳣������
     * info: ֻ������Ϣ
     * normal: ��������Ϣ��ֻ��¼DUMP�ļ�
     * error: ��������Ϣ���ּ�¼DUMP�ļ�
     */
    enum ExceptionLevel {
        info, // ��Ϣ
        normal, // ����
        error, // ����
    };

#ifdef OS_WIN
    // �쳣ע�ᴦ����
    static LONG CALLBACK ExceptionHandler(PEXCEPTION_POINTERS exception);
    static BOOL PreventSetUnhandledExceptionFilter();
    static LPTOP_LEVEL_EXCEPTION_FILTER WINAPI ExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter);
#endif // OS_WIN


    explicit CrashWin(const CrashHandler* handler);
    virtual ~CrashWin();

    /*
     * FunctionName: Regist
     * Description: ע�����������
     * Author: zfs
     * Date: 2021-05-16 09:18
     */
    bool Regist(const ExceptionLevel& el);

    CrashHandler* getHandler() const {
        return handler_;
    }

    bool getInited() const {
        return inited_;
    }

protected:
    // ֪ͨ�ص����
    CrashHandler* handler_;

    // �쳣������
    ExceptionLevel exception_level_;

    // �ص������Ѿ�ע���־
    bool inited_;
};

} // end namespace h2x

#endif // !H2XBASE_CRASH_CRASH_WIN__H
