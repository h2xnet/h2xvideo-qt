#ifndef H2XBASE_THREAD_PLUGIN_THREAD_H
#define H2XBASE_THREAD_PLUGIN_THREAD_H

#include "h2xbase/thread/thread.h"
#include "h2xbase/task/event_loop.h"
#include "h2xbase/h2x_base_export.h"

namespace h2x {

class PluginManager;

/*
 * ClassName: PluginThread
 * Desc: 插件线程类，插件与框架之间最大的区别是插件走事件任务模式，而框架走线程任务模式
 * 事件任务模式中，传递的是任务参数，在插件内需要解析参数，然后用参数初始化，进行执行
 * 线程任务模式中，传递的是线程函数，直接调用就行
 * Author: zfs
 * Date: 2021-08-15 11:32
 */
class H2XBASE_EXPORT PluginThread : public Thread
{
public:
    PluginThread();
    virtual ~PluginThread();

private:
    friend class PluginManager;
};

} // end namespace h2x

#endif // H2XBASE_THREAD_PLUGIN_THREAD_H
