// ConsoleTest.cpp : �������̨Ӧ�ó������ڵ㡣
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
    base::AtExitManager exit_manager; //�����˳�����������������ã����뱨���ԣ���ʱû��dump�����ݴ���

    // ��ʼ����־�ļ�
    logging::LoggingSettings logging_setting;
    base::FilePath path;
    PathService::Get(base::DIR_APP_DATA, &path);
    path = path.Append(L"ConsoleTest").Append(L"P2PConsoleTest.log");

    // ��ʼ�����ܼ��ģ��

    // ��ʼ��ͳ��ģ��


    // ��ʼ������ģ��
    michaeltan::ThreadPool::Init();
    base::MessageLoopForUI uiMainMessageLoop;
    MainApp mainApp;
    {
        // ��ʼ��ҵ����ģ��
        mainApp.Init(&uiMainMessageLoop);

        // ����ҵ��ģ��
        mainApp.Start();

        mainApp.Test();

        //ֹͣҵ��ģ��
        mainApp.Stop();

        // ����ҵ����ģ��
    }


    // �������ģ��
    michaeltan::ThreadPool::StopAllThread();

	return 0;
}

