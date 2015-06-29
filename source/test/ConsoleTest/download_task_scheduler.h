#pragma once

#include <map>

#include "third_party/chromium/base/memory/ref_counted.h"
#include "third_party/chromium/base/message_loop/message_loop.h"
#include "third_party/chromium/base/sequenced_task_runner.h"
#include "download_task.h"


// ���ຯ����ֻ�ṩ��һ���ܣ�����remove��������ֹͣ������ɾ����������������ֻ�᷵��ɾ��ʧ��
// ���������ֹͣ���������ֹͣ״̬����ִ��ɾ��

class DownloadTaskScheduler 
    : public base::RefCountedThreadSafe<DownloadTaskScheduler>
{
public:
    DownloadTaskScheduler();
    ~DownloadTaskScheduler();
    bool Init(scoped_refptr<base::SequencedTaskRunner> outer_runner);

    // ���ø��ֻص�������ҵ���Ͼ��Բ��������ⲿ���ƶ���

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

    // �ⲿ�����߳�runner�����������񶼶�������߳���
    scoped_refptr<base::SequencedTaskRunner> outerRunner_;

    // �ڲ�ʹ�õ��߳�runner�����������߳����������runnerִ��
    scoped_refptr<base::SequencedTaskRunner> innerRunner_;

    std::map<DownloadTaskHandle, std::shared_ptr<DownloadTask>> taskMap_;
};

