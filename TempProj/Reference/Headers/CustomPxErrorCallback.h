#pragma once
#include "Base.h"

class CCustomPxErrorCallback :
    public physx::PxErrorCallback
{
    // PxErrorCallback��(��) ���� ��ӵ�
    virtual void reportError(PxErrorCode::Enum code, const char* message, const char* file, int line) override;
};

