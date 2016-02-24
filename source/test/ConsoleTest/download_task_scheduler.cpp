

#include "third_party/chromium/base/bind.h"
#include "base/thread_pool.h"
#include "test/ConsoleTest/download_task_scheduler.h"
#include <utility>

DownloadTaskScheduler::DownloadTaskScheduler()
{
}


DownloadTaskScheduler::~DownloadTaskScheduler()
{
}

bool DownloadTaskScheduler::Init(scoped_refptr<base::SequencedTaskRunner> outer_runner)
{
    outerRunner_ = outer_runner;
    innerRunner_ = michaeltan::ThreadPool::GetNamedSequenceTaskRunner("downloadtaskscheduler");

    // 传inner_runner_给这个类所管理的模块，供回调任务使用

    return false;
}

bool DownloadTaskScheduler::Start()
{
    return false;
}

bool DownloadTaskScheduler::Stop()
{
    return false;
}

bool DownloadTaskScheduler::AddTask(const DownloadTaskParam& downloadtaskparam,
                                    DownloadTaskHandle* handle)
{
    DownloadTaskHandle temp = DownloadTaskHandle::GetHandle();
    if (!temp.IsVaild())
        return false;

    *handle = temp;

    return innerRunner_->PostNonNestableTask(
        FROM_HERE,
        base::Bind(&DownloadTaskScheduler::DoAddTask, base::Unretained(this), 
        downloadtaskparam, temp));
}

void DownloadTaskScheduler::DoAddTask(const DownloadTaskParam& downloadtaskparam,
                                      const DownloadTaskHandle& handle)
{
    std::shared_ptr<DownloadTask> downloadtask;
    downloadtask.reset(new DownloadTask);
    downloadtask->Init(downloadtaskparam);

    auto res = taskMap_.insert(std::make_pair(handle, downloadtask));
    if (!res.second)
        return ;
    
    // 通知结果
    // outerRunner_->PostNonNestableTask()
    return;
}

bool DownloadTaskScheduler::Remove(const DownloadTaskHandle& handle)
{
    return innerRunner_->PostNonNestableTask(
        FROM_HERE,
        base::Bind(&DownloadTaskScheduler::DoRemove, base::Unretained(this),
                   handle));
}

void DownloadTaskScheduler::DoRemove(const DownloadTaskHandle& handle)
{
    auto sizetype = taskMap_.erase(handle);

    // 通知结果
    // outerRunner_->PostNonNestableTask()
    return ;
}

bool DownloadTaskScheduler::StartTask(const DownloadTaskHandle& handle)
{
    return innerRunner_->PostNonNestableTask(
        FROM_HERE,
        base::Bind(&DownloadTaskScheduler::DoStartTask, base::Unretained(this),
        handle));
}

void DownloadTaskScheduler::DoStartTask(const DownloadTaskHandle& handle)
{
    auto findresult = taskMap_.find(handle);
    bool result = false;
    if (findresult != taskMap_.end())
    {
        const std::shared_ptr<DownloadTask>& ref = findresult->second;
        result = ref->Run();
    }
    else
    {
        result = false;
    }

    // 通知结果
    // outerRunner_->PostNonNestableTask()
}

bool DownloadTaskScheduler::StopTask(const DownloadTaskHandle& handle)
{
    return innerRunner_->PostNonNestableTask(
        FROM_HERE,
        base::Bind(&DownloadTaskScheduler::DoStopTask, base::Unretained(this),
        handle));
}

void DownloadTaskScheduler::DoStopTask(const DownloadTaskHandle& handle)
{
    // 通知结果
    // outerRunner_->PostNonNestableTask()
    return ;
}