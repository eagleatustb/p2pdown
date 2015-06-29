#pragma once

#include "third_party/chromium/base/memory/scoped_ptr.h"
#include "third_party/chromium/base/message_loop/message_loop.h"

class DownloadTaskScheduler;
class MainApp
{
public:
    MainApp();
    ~MainApp();
    bool Init(base::MessageLoop* messageloop);
    bool Start();
    void Run();
    bool Stop();

    void Test();

private:
    scoped_refptr<DownloadTaskScheduler> downloadTaskScheduler_;
    base::MessageLoop* uiMessageLoop_;
    scoped_refptr<base::SequencedTaskRunner> runner_;
};

