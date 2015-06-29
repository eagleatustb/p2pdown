#pragma once
#include "third_party/chromium/base/memory/ref_counted.h"

// 下载协议结构类
class HashProtocol
    : public base::RefCountedThreadSafe<HashProtocol>
{
public:
    HashProtocol();
    ~HashProtocol();
};

