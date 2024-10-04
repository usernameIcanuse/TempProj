#pragma once
#include "Base.h"

BEGIN(Engine)

class CCustomPxAllocatorCallback :
    public physx::PxAllocatorCallback
{
    // PxAllocatorCallback��(��) ���� ��ӵ�
    virtual void* allocate(size_t size, const char* typeName, const char* filename, int line) override;
    virtual void deallocate(void* ptr) override;
};

END