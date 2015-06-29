
#include <memory>
#include "third_party/chromium/base/memory/ref_counted.h"
#include "third_party/chromium/base/message_loop/message_loop.h"
#include "third_party/chromium/base/sequenced_task_runner.h"
#include "third_party/chromium/base/bind.h"
#include "base/thread_pool.h"
#include "download_task.h"
#include "hash_protocol.h"
#include "easy_udp.h"

uint64 DownloadTaskHandle::staticHandle = 0;

DownloadTaskHandle DownloadTaskHandle::GetHandle()
{
    return DownloadTaskHandle(++staticHandle);
}

DownloadTaskHandle::DownloadTaskHandle()
    :handle_(0)
{
}

DownloadTaskHandle::DownloadTaskHandle(uint64 handle)
    : handle_(handle)
{
}

DownloadTaskHandle::~DownloadTaskHandle()
{
}

bool DownloadTaskHandle::IsVaild()
{
    return handle_ > 0;
}

bool DownloadTaskHandle::operator<(const DownloadTaskHandle& right) const
{
    return (right.handle_ < this->handle_);
}

DownloadTask::DownloadTask()
    :hashProtocal_(new HashProtocol)
    , taskState_(TASK_STATE::TASK_STATE_NOT_READY)
{
}


DownloadTask::DownloadTask(const DownloadTask& downloadtask)
{
}

DownloadTask::~DownloadTask()
{
}

bool DownloadTask::Init(const DownloadTaskParam& downloadtaskparam)
{
    assert(taskState_ == TASK_STATE::TASK_STATE_NOT_READY);
    // 检查参数合法性
    downloadTaskParam_ = downloadtaskparam;
    taskState_ = TASK_STATE::TASK_STATE_READY;

    innerRunner_ = michaeltan::ThreadPool::GetNamedSequenceTaskRunner("DownloadTask");
    return true;
}

// 外部线程调用
bool DownloadTask::Run()
{
    return innerRunner_->PostNonNestableTask(FROM_HERE,
        base::Bind(&DownloadTask::DoRun, base::Unretained(this)));
}

void DownloadTask::DoRun()
{
    // 获取服务器信息，初始化重试策略

    // 若初始化失败，回调

    bool ret =innerRunner_->PostNonNestableTask(FROM_HERE,
        base::Bind(&DownloadTask::DoSendHashProtocol, base::Unretained(this)));

    if (!ret)
    {
        // 若抛任务失败，则回调通知
    }
}
void DownloadTask::DoSendHashProtocol()
{
    if (taskState_ != TASK_STATE::TASK_STATE_READY)
    {
        // 回调通知状态错误
    }
    taskState_ = TASK_STATE::TASK_STATE_RUN;
    std::vector<uint8> data(1024, 3);

    //typedef std::function<void(std::weak_ptr<DownloadTask>)> SendCallback;
    SendCallback callback = std::bind(&DownloadTask::SendHashProtocalCallback,
         std::weak_ptr<DownloadTask>(shared_from_this()));

    EasyUdp easyudp;
    // 异步发送数据
    easyudp.Send(data, callback, 0);

    UdpSend udpsend;
    auto cb = base::Bind(&DownloadTask::SendHashProtocalCallback,
        std::weak_ptr<DownloadTask>(shared_from_this()));
    easyudp.BindSend(udpsend, cb);
}

void DownloadTask::SendHashProtocalCallback(std::weak_ptr<DownloadTask> wptr)
{
    auto obj = wptr.lock();
    if (!obj)
        return;

    return;
}

