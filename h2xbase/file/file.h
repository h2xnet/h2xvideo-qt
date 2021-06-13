#ifndef H2XBASE_FILE_FILE__H
#define H2XBASE_FILE_FILE__H

#include "build/build_config.h"
#include "h2xbase/h2x_base_export.h"
#include "h2xbase/file/file_path.h"

#ifdef OS_WIN
#include <Windows.h>
#endif // OS_WIN


namespace h2x {

/*
 * ClassName: File
 * Desc: �ļ�������
 * Author: zfs
 * Date: 2021-05-16 10:25
 */
class H2XBASE_EXPORT File {
public:
	File();
	virtual ~File();

    bool Open(const PathWChar* fileName, const PathWChar* mode = L"a+");

    void Close();

    /*
     * FunctionName: Read
     * Desc: ��ȡ�ļ�����
     * Author: zhaofushou
     * Date: 2021-05-29 16:21
     * @buff: ��Ŷ�ȡ���ݵĻ�����
     * @buffSize: ��������С
     * @readDataSize: ʵ�ʶ�ȡ�����ݳ���
     * ����ֵ���������ֽ��������С��0����������
     */
    int Read(byte* buff, size_t buffSize, int& readDataSize);

    //
    // Write : �����ļ�����
    //
    int Write(const char* data, size_t dataSize);

    //
    // Print : ��ʽ��д���ļ�����
    //
    int Print(const char* format, ...);

    int Print(const char* format, const va_list& ap);

    //
    // PrintW : ��ʽ��д���ļ����ݣ�unicodeģʽ����Ҫ���ڰ����������������
    //
    int PrintW(const wchar_t* format, ...);

    int PrintW(const wchar_t* format, const va_list& ap);

private:
    FILE* ff_;

};

} // end namespace h2x

#endif // !H2XBASE_FILE_FILE__H
