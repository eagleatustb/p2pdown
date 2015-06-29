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



// �������ⲿ�������ӵ�downloadtaskscheduler�й��������ڻص�ʱ��Ҫ�����Ƿ񻹴����������
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

    // ���ø��ֻص�������ҵ���Ͼ��Բ�������DownloadTaskScheduler�������ⲿ���ƶ���

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

    // �ڲ�ʹ�õ��߳�runner�����������߳����������runnerִ��
    scoped_refptr<base::SequencedTaskRunner> innerRunner_;

};

