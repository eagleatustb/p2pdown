#pragma once
#include <vector>
#include <functional>
#include "third_party/chromium/base/basictypes.h"
#include "third_party/chromium/base/callback.h"
#include <memory>
#include "third_party/chromium/base/basictypes.h"
#include "third_party/chromium/base/memory/scoped_ptr.h"

#include "third_party/chromium/base/bind.h"
#include "third_party/chromium/base/memory/ref_counted.h"
#include "third_party/chromium/base/message_loop/message_loop.h"
#include "third_party/chromium/base/sequenced_task_runner.h"

using base::Closure;

class DownloadTask;
typedef std::function<void(std::weak_ptr<DownloadTask>)> SendCallback;

class UdpSend
{

};

class UdpReceive
{

};


class EasyUdp:
    public std::enable_shared_from_this<EasyUdp>
{
public:
    static std::shared_ptr<EasyUdp> GetShare();
    ~EasyUdp();
    bool Send(const std::vector<uint8>& data, const SendCallback& callback,
                  uint32 mstimeout);

    bool BindSend(UdpSend udpsend, const base::Closure& closure);

private:
    EasyUdp();

    static std::shared_ptr<EasyUdp>* easyUdp;
    bool Init();

    void DoSend(const std::vector<uint8>& data, const SendCallback& callback,
        uint32 mstimeout);
    // 内部使用的线程runner，本次下载线程任务都在这个runner执行
    scoped_refptr<base::SequencedTaskRunner> innerRunner_;

};

