#include "main_app.h"

#include "third_party/chromium/base/bind.h"
#include "base/thread_pool.h"

#include "download_task.h"
#include "test/ConsoleTest/download_task_scheduler.h"

MainApp::MainApp()
    :uiMessageLoop_(nullptr)
{
}


MainApp::~MainApp()
{
}

bool MainApp::Init(base::MessageLoop* messageloop)
{
    if (!messageloop)
        return false;

    uiMessageLoop_ = messageloop;
    runner_ = michaeltan::ThreadPool::GetNamedSequenceTaskRunner("mainapp");
    downloadTaskScheduler_ = new DownloadTaskScheduler;
    downloadTaskScheduler_->Init(runner_);
    return true;
}

void MainApp::Run()
{
    uiMessageLoop_->Run();
}

bool MainApp::Stop()
{
    return false;
}


bool MainApp::Start()
{
    uiMessageLoop_->PostTask(FROM_HERE,
                             base::Bind(&MainApp::DoStart,
                             base::Unretained(this)));
    return true;
}

void MainApp::DoStart()
{
    downloadTaskScheduler_->Start();
}

bool MainApp::Test()
{
    uiMessageLoop_->PostTask(FROM_HERE,
                             base::Bind(&MainApp::DoTest,
                             base::Unretained(this)));
    return true;
}

void MainApp::DoTest()
{
    DownloadTaskHandle handle;
    DownloadTaskParam downloadtaskparam;
    if (!downloadTaskScheduler_->AddTask(downloadtaskparam, &handle))
    {
        return;
    }
    if (!handle.IsVaild())
        return;
    downloadTaskScheduler_->StartTask(handle);

    return;
}

