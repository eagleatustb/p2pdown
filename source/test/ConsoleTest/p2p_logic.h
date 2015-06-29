#pragma once
class P2pLogic
{
public:
    P2pLogic();
    ~P2pLogic();

    // 模块基本管理
    bool StartModule();
    bool StopModule();

    // 添加一个文件到下载队列
    bool AddDownloadFile();
    bool RemoveDownloadFile();


};

