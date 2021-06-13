#ifndef H2XBASE_STRING_STRING_UTIL__H
#define H2XBASE_STRING_STRING_UTIL__H

#include <string>
#include <memory>

#include "h2xbase/btype.h"
#include "h2xbase/string/string_result.h"
#include "h2xbase/h2x_base_export.h"

namespace h2x {

/*
* ClassName: StringUtil
* Desc: �ַ����ۺϴ�����
* Author: zfs
* Date: 2021-05-19 23:19
*/
class H2XBASE_EXPORT StringUtil {
public:
    StringUtil();
    virtual ~StringUtil();

    /*
     * Function: StringPrintf
     * Desc: �ַ�����ʽ�����
     * Author: zhaofushou
     * Date: 2021-05-18 14:24
     * @result: ���ظ�ʽ������ַ���
     * @format: ��ʽ�ַ���
     * ����ֵ���ɹ�����true��ʧ�ܷ���false
     */
    static bool StringPrintf(StringResult<PathChar>& result, const char *format, ...);

    /*
     * Function: StringPrintfW
     * Desc: �ַ�����ʽ�����
     * Author: zhaofushou
     * Date: 2021-05-18 16:05
     * @result: ���ظ�ʽ������ַ���
     * @format: ��ʽ�ַ���
     * ����ֵ���ɹ�����true��ʧ�ܷ���false
     */
    static bool StringPrintfW(StringResult<PathWChar>& result, const wchar_t *format, ...);

    /*
     * FunctionName: GetNowDateString
     * Desc: ��ȡ��ǰ�����ַ���������2021-05-29
     * Author: zhaofushou
     * Date: 2021-05-29 14:12
     * @result: ���ص������ַ���
     * ����ֵ���ɹ�����true��ʧ�ܷ���false
     */
    static bool GetNowDateString(StringResult<PathChar>& result);

    /*
     * FunctionName: GetNowDateStringW
     * Desc: ��ȡ��ǰ�����ַ���������2021-05-29
     * Author: zhaofushou
     * Date: 2021-05-29 14:12
     * @result: ���ص������ַ���
     * ����ֵ���ɹ�����true��ʧ�ܷ���false
     */
    static bool GetNowDateStringW(StringResult<PathWChar>& result);

    /*
     * FunctionName: GetNowDatetimeString
     * Desc: ��ȡ��ǰ����ʱ���ַ���������2021-05-29 14:48:23.323
     * Author: zhaofushou
     * Date: 2021-05-29 14:12
     * @result: ���ص������ַ���
     * ����ֵ���ɹ�����true��ʧ�ܷ���false
     */
    static bool GetNowDatetimeString(StringResult<PathChar>& result);
    static bool GetNowDatetimeStringW(StringResult<PathWChar>& result);

    /*
     * FunctionName: GetDateLoggerFileNameW
     * Desc: ��ȡ������־�ļ����ƣ���չ��Ϊlog
     * Author: zhaofushou
     * Date: 2021-05-29 14:55
     * @prefix: �ļ���ǰ׺�����ص��ļ������ǰ׺���ļ������»�������
     * @result: ���ص������ַ���
     * ����ֵ���ɹ�����true��ʧ�ܷ���false
     */
    static bool GetDateLoggerFileNameW(const PathWString& prefix, StringResult<PathWChar>& result);

};

};

#endif // !H2XBASE_STRING_STRING_UTIL__H
