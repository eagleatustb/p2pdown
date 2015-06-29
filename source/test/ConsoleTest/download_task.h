#pragma once
#include <memory>
#include "third_party/chromium/base/basictypes.h"
#include "third_party/chromium/base/memory/scoped_ptr.h"

class DownloadTaskHandle
{
public:
    DownloadTaskHandle();
    ~DownloadTaskHandle();
    bool IsVaild();
    bool operator<(const DownloadTaskHandle& right) const;
    static DownloadTaskHandle GetHandle();
    static uint64 staticHandle;
private:
    explicit DownloadTaskHandle(uint64 handle);
    uint64 handle_;
};

class DownloadTaskParam
{
    std::string hash;
    std::string param1;
};



// 任务由外部创建，扔到downloadtaskscheduler中管理副本，在回调时需要测试是否还存在这个任务
class DownloadTaskScheduler;
class HashProtocol;
class DownloadTask : 
    public std::enable_shared_from_this<DownloadTask>
{
public:
    friend class DownloadTaskScheduler;
    DownloadTask();
    DownloadTask(const DownloadTask& downloadtask);
    ~DownloadTask();

    bool Init(const DownloadTaskParam& downloadtaskparam);

    // 设置各种回调函数，业务上绝对不能依赖DownloadTaskScheduler或其他外部控制对象

    static void SendHashProtocalCallback(std::weak_ptr<DownloadTask> wptr);


protected:
    enum class TASK_STATE
    {
        TASK_STATE_NOT_READY = 0,
        TASK_STATE_READY,
        TASK_STATE_PAUSE,
        TASK_STATE_RUN,
        TASK_STATE_FINISH,
    };

    bool Run();
    void DoRun();
    void DoSendHashProtocol();

private:
    TASK_STATE taskState_;
    DownloadTaskParam downloadTaskParam_;
    scoped_ptr<HashProtocol> hashProtocal_;

    // 内部使用的线程runner，本次下载线程任务都在这个runner执行
    scoped_refptr<base::SequencedTaskRunner> innerRunner_;

};

