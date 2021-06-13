#ifndef H2XBASE_FILE_FILE_PATH__H
#define H2XBASE_FILE_FILE_PATH__H

#include <string>
#include "build/build_config.h"
#include "../h2x_base_export.h"

#ifdef OS_WIN
#include <shlobj.h>
#endif // OS_WIN


namespace h2x {

#if defined(OS_POSIX)
    typedef std::string PathString;
#elif defined(OS_WIN)
    typedef std::string PathString;
    typedef std::wstring PathWString;
#endif

typedef PathString::value_type PathChar;
typedef PathWString::value_type PathWChar;

/*
 * ClassName: FilePath
 * Desc: �ļ�·��������
 */
class H2XBASE_EXPORT FilePath {
public:
	FilePath();
	virtual ~FilePath();

    /*
     * FunctionName: GetModulePath
     * Desc: ��ȡ��ǰEXEģ��·�������ֽڰ汾
     * Author: zhaofushou
     * Date: 2021-05-17 15:20
     * @dataBuf: ���շ���ֵ����
     * @dataBufSize: ��������С
     * @dataSize: ʵ�ʷ��ص����ݴ�С
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool GetModulePath(PathChar* dataBuf, size_t dataBufSize, int& dataSize);

    /*
     * FunctionName: GetModulePathW
     * Desc: ��ȡ��ǰEXEģ��·��
     * Author: zhaofushou
     * Date: 2021-05-17 15:20
     * @dataBuf: ���շ���ֵ����
     * @dataBufSize: ��������С
     * @dataSize: ʵ�ʷ��ص����ݴ�С
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool GetModulePathW(PathWChar* dataBuf, size_t dataBufSize, int& dataSize);

    /*
     * FunctionName: GetAppDataPathW
     * Description: ��ȡϵͳĬ��AppDataĿ¼
     * Author: zfs
     * Date: 2021-05-16 09:58
     * @dataBuf: �������ݵĻ�����
     * @dataBufSize: ��������С
     * @dataSize: ʵ����Ҫ���ݴ�С�����������Ϊ�գ�Ҳ�᷵����ʵ���ݴ�С
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool GetAppDataPathW(PathWChar* dataBuf, size_t dataBufSize, int& dataSize);

    /*
     * FuntionName: CheckFileIsExist
     * Desc: ����ļ���Ŀ¼�Ƿ���ڣ����ֽڰ汾
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @filePath: Ҫ����·��
     * @isDirectory: Ϊtrue���������Ŀ¼������������ļ�
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool CheckFileIsExist(const PathString& filePath, bool isDirectory);

    /*
     * FuntionName: CheckFileIsExistW
     * Desc: ����ļ���Ŀ¼�Ƿ����
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @filePath: Ҫ����·��
     * @isDirectory: Ϊtrue���������Ŀ¼������������ļ�
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool CheckFileIsExistW(const PathWString& filePath, bool isDirectory);

    /*
     * FuntionName: CreatePath
     * Desc: ����Ŀ¼������ݹ鴴���������Ҫ�Լ�����ݹ鴴�����⣩
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @path: Ҫ������Ŀ¼
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool CreatePath(const PathString& path);

    /*
     * FuntionName: CreatePathW
     * Desc: ����Ŀ¼������ݹ鴴���������Ҫ�Լ�����ݹ鴴�����⣩
     * Author: zfs
     * Data: 2021-05-16 10:08
     * @path: Ҫ������Ŀ¼
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool CreatePathW(const PathWString& path);

    /*
     * FunctionName: FileDelete
     * Desc: ɾ���ļ�
     * Author: zhaofushou
     * Date: 2021-05-16 15:29
     * @fileName: Ҫɾ�����ļ���
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool FileDelete(const PathString& fileName);

    /*
     * FunctionName: FileDeleteW
     * Desc: ɾ���ļ�
     * Author: zhaofushou
     * Date: 2021-05-16 15:29
     * @fileName: Ҫɾ�����ļ���
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool FileDeleteW(const PathWString& fileName);

    /*
     * FunctionName: GetFileSize
     * Desc: ��ȡ�ļ���С
     * Author: zhaofushou
     * Date: 2021-05-16 15:29
     * @fileName: �ļ���
     * @fileSize: ���ص��ļ���С
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool GetFileSize(const PathString& fileName, int64_t& fileSize);

    /*
     * FunctionName: GetFileSizeW
     * Desc: ��ȡ�ļ���С
     * Author: zhaofushou
     * Date: 2021-05-16 15:29
     * @fileName: �ļ���
     * @fileSize: ���ص��ļ���С
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    static bool GetFileSizeW(const PathWString& fileName, int64_t& fileSize);

};

} // end namespace h2x

#endif // !H2XBASE_FILE_FILE_PATH__H