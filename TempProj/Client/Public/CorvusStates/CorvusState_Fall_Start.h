#pragma once
#include "CorvusStateBase.h"

BEGIN(Engine)
class CModel;
class CPhysXController;
END

BEGIN(Client)

class CCorvusState_Fall_Start :
    public CCorvusStateBase
{
    GAMECLASS_H(CCorvusState_Fall_Start);
    SHALLOW_COPY(CCorvusState_Fall_Start)
    CLONE_H(CCorvusState_Fall_Start, CComponent)

protected:
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void Start() override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;

public:
    void Call_AnimationEnd(_uint iEndAnimIndex);

protected:
    virtual void OnStateStart(const _float& In_fAnimationBlendTime) override;
    virtual void OnStateEnd() override;

protected:
    virtual void OnDestroy() override;
    void Free();


    // CNorMonStateBase��(��) ���� ��ӵ�
    virtual _bool Check_AndChangeNextState() override;

};

END