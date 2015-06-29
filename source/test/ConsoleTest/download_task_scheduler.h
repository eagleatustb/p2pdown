#pragma once

#include <map>

#include "third_party/chromium/base/memory/ref_counted.h"
#include "third_party/chromium/base/message_loop/message_loop.h"
#include "third_party/chromium/base/sequenced_task_runner.h"
#include "download_task.h"


// 本类函数都只提供单一功能，比如remove，不会先停止任务再删除，对于正在运行只会返回删除失败
// 由外层先下停止命令，任务在停止状态才能执行删除

class DownloadTaskScheduler 
    : public base::RefCountedThreadSafe<DownloadTaskScheduler>
{
public:
    DownloadTaskScheduler();
    ~DownloadTaskScheduler();
    bool Init(scoped_refptr<base::SequencedTaskRunner> outer_runner);

    // 设置各种回调函数，业务上绝对不能依赖外部控制对象

    bool Start();
    bool Stop();

    bool AddTask(const DownloadTaskParam& downloadtaskparam, DownloadTaskHandle* handle);
    bool Remove(const DownloadTaskHandle& handle);
    bool StartTask(const DownloadTaskHandle& handle);
    bool StopTask(const DownloadTaskHandle& handle);

private:
    void DoAddTask(const DownloadTaskParam& downloadtaskparam,
        const DownloadTaskHandle& handle);
    void DoRemove(const DownloadTaskHandle& handle);
    void DoStartTask(const DownloadTaskHandle& handle);
    void DoStopTask(const DownloadTaskHandle& handle);

    // 外部来的线程runner，反馈的任务都丢到这个线程里
    scoped_refptr<base::SequencedTaskRunner> outerRunner_;

    // 内部使用的线程runner，本类管理的线程任务都在这个runner执行
    scoped_refptr<base::SequencedTaskRunner> innerRunner_;

    std::map<DownloadTaskHandle, std::shared_ptr<DownloadTask>> taskMap_;
};

