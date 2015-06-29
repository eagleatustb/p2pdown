// ConsoleTest.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "third_party/chromium/base/threading/thread.h"
#include "third_party/chromium/base/at_exit.h"
#include "third_party/chromium/base/files/file_path.h"
#include "third_party/chromium/base/path_service.h"

#include "base/thread_pool.h"

#include "test/ConsoleTest/main_app.h"

void ThreadTest()
{
    base::Thread::Options logical_option(base::MessageLoop::TYPE_DEFAULT, 0);
    base::Thread logical_thread("logicalthread");
    logical_thread.StartWithOptions(logical_option);

    base::Thread::Options io_option(base::MessageLoop::TYPE_IO, 0);
    base::Thread io_thread("iothread");
    io_thread.StartWithOptions(io_option);

    io_thread.Stop();
    logical_thread.Stop();
}




int _tmain(int argc, _TCHAR* argv[])
{
    base::AtExitManager exit_manager; //设置退出处理函数，如果不设置，编译报断言，暂时没加dump等数据处理

    // 初始化日志文件
    logging::LoggingSettings logging_setting;
    base::FilePath path;
    PathService::Get(base::DIR_APP_DATA, &path);
    path = path.Append(L"ConsoleTest").Append(L"P2PConsoleTest.log");

    // 初始化性能监控模块

    // 初始化统计模块


    // 初始化基础模块
    michaeltan::ThreadPool::Init();
    base::MessageLoopForUI uiMainMessageLoop;
    MainApp mainApp;
    {
        // 初始化业务功能模块
        mainApp.Init(&uiMainMessageLoop);

        // 启动业务模块
        mainApp.Start();

        mainApp.Test();

        //停止业务模块
        mainApp.Stop();

        // 清理业务功能模块
    }


    // 清理基础模块
    michaeltan::ThreadPool::StopAllThread();

	return 0;
}

