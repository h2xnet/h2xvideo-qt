#ifndef H2XCORE_H2X_APPLICATION__H
#define H2XCORE_H2X_APPLICATION__H

#include <string>
#include "h2xcore/h2x_core_export.h"

namespace h2x {

class Cache;
class Config;
class Context;
class Middleware;
class Router;

// ������־����
class AppLogger;
class AppCoreLogger;
class ContextLogger;
class ContextCoreLogger;
class ControllerLogger;
class Listen;
class ListenTable;
class ServiceLogger;

/*
 * ClassName: Application
 * Desc: Ӧ���࣬һ��Ӧ��ֻ������һ��ʵ��
 * Author: zfs
 * Date: 2021-05-16 17:12
 */
class H2XCORE_EXPORT Application {
public:
    /*
     * ���캯��˵��
     * @argc��Ӧ��������������
     * @argv: Ӧ�����������б�
     * @cfg:Ӧ�����ö������Ϊ�գ��򴴽�Ĭ�϶��󣬲�Ϊ�����ô���Ķ���
     */
    Application(int argc, char *argv[], const Config* cfg);
    virtual ~Application();

    /*
     * FunctionName: exec
     * Desc: ��ʼ����Ӧ��
     * Author: zfs
     * Date: 2021-06-12 16:00
     * ����ֵ���ɹ�����true,ʧ�ܷ���false
     */
    virtual bool exec(); 

    /*
     * FunctionName: beforeStart
     * Desc: ��Ӧ�÷�������ǰ������ô˺����ص�֪ͨ��һ��Ӧ��ֻ��֪ͨһ��
     * Author: zfs
     * Date: 2021-06-05 09:38
     */
    virtual void beforeStart();

    /*
     * FunctionName: onStarted
     * Desc: ��Ӧ�÷���������ɺ󣬻���ô˺����ص�֪ͨ��һ��Ӧ��ֻ��֪ͨһ��
     * Author: zfs
     * Date: 2021-06-05 09:38
     */
    virtual void onStarted();
    virtual bool once(const std::string& name);

    /*
     * FunctionName: on
     * Desc: ע���¼������������˺���ע����¼���ÿ�η�������֪ͨ
     * Author: zfs
     * Date: 2021-06-05 09:38
     * @name: �¼����ƣ���Ҫ�б���error�¼�,request�¼���response�¼���
     */
    virtual bool on(const std::string& name);

    /*
     * FunctionName: createAnonymousContext
     * Desc: ����һ�������������Ķ���
     */
    Context* createAnonymousContext();

	/*
	 * setName : ����Ӧ������
	 * Author: zfs
	 * Date: 2021-05-17 12:38
	 */
	void setName(const char* name, size_t nameSize) {
		if (name && nameSize > 0) {
			name_ = std::string(name, nameSize);
		}
		else {
			name_ = "h2xapp";
		}
	}

	/*
	 * getName: ��ȡӦ������
	 * Author: zfs
	 * Date: 2021-05-17 12:38
	*/
	const char* getName() {
		return name_.c_str();
	}

	/*
	 * FunctionName: getConfig
	 * Desc: ��ȡ����ָ��
	 * Author: zhaofushou
	 * Date: 2021-05-17 12:40
	 */
	Config* getConfig() const {
		return cfg_;
	}

protected:
    // Ӧ����������
    int argc_;
    char** argv_;

	// Ӧ������
	std::string name_;

    // ���ö���
	Config* cfg_;

    // �������
    Cache* cache_;

    // ��������
    ListenTable* listens_;

    // �м������
    Middleware* middlewares_;

    // ·�ɶ���
    Router* router_;
};

} // end namespace h2x

#endif // !H2XCORE_H2X_APPLICATION__H
