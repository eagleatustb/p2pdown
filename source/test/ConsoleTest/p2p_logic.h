#pragma once
class P2pLogic
{
public:
    P2pLogic();
    ~P2pLogic();

    // ģ���������
    bool StartModule();
    bool StopModule();

    // ���һ���ļ������ض���
    bool AddDownloadFile();
    bool RemoveDownloadFile();


};

