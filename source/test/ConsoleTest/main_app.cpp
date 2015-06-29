#include "main_app.h"

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

bool MainApp::Start()
{
    downloadTaskScheduler_->Start();
    return false;
}

void MainApp::Run()
{
    uiMessageLoop_->Run();
}

void MainApp::Test()
{
    DownloadTaskHandle handle;
    DownloadTaskParam downloadtaskparam;
    if (downloadTaskScheduler_->AddTask(downloadtaskparam, &handle))
    {
        if (!handle.IsVaild())
            return;
    }
    
    return;
}

bool MainApp::Stop()
{
    return false;
}
