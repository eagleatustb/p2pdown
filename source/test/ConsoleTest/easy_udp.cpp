#include "easy_udp.h"
#include "base/thread_pool.h"
#include "third_party/chromium/base/bind.h"
#include "test/ConsoleTest/download_task_scheduler.h"

EasyUdp::EasyUdp()
{

}

EasyUdp::~EasyUdp()
{

}

bool EasyUdp::Init()
{
    innerRunner_ = michaeltan::ThreadPool::GetNamedSequenceTaskRunner("easyudp");
    return true;
}

bool EasyUdp::Send(const std::vector<uint8>& data, const SendCallback& callback,
    uint32 mstimeout)
{
    innerRunner_->PostNonNestableTask(FROM_HERE,
        base::Bind(&EasyUdp::DoSend, base::Unretained(this), data, callback, mstimeout));

    //callback();
    return false;
}

bool EasyUdp::BindSend(UdpSend udpsend, const base::Closure& closure)
{
    return true;
}

void EasyUdp::DoSend(const std::vector<uint8>& data, const SendCallback& callback,
    uint32 mstimeout)
{

}