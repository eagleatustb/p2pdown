#pragma once
#include "third_party/chromium/base/memory/ref_counted.h"

// ����Э��ṹ��
class HashProtocol
    : public base::RefCountedThreadSafe<HashProtocol>
{
public:
    HashProtocol();
    ~HashProtocol();
};

