#pragma once
#include "StateBase.h"

BEGIN(Engine)
class CAnimation;
class CNavigation;
END

BEGIN(Client)

class CMonster;
class CAIStateBase abstract:
    public CStateBase
{
    GAMECLASS_H(CAIStateBase);

public:
    // CClientComponent��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual void    Start() override;
    virtual void    Tick(_float fTimeDelta) override;
    virtual void    LateTick(_float fTimeDelta) override;

public:
    virtual void            Init_Desc(void* In_pDesc) override;
    virtual _bool           Check_RequirementCoolDown(weak_ptr<CAIStateBase> pTargetState, const _float& In_fCoolTime);

public:
    _float                  Get_StateTimeAcc() const { return m_fStateTimeAcc; }
    shared_ptr<CMonster>    Get_OwnerMonster() const noexcept;
    virtual _bool           Check_Requirement() override;

protected:
    void                    Set_AtkPermitAndNoHurt(_bool AtkPermitAndNoHurt) { m_bAtkPermitAndNoHurt = AtkPermitAndNoHurt; }
    void                    Turn_ToThePlayer(_float fTimeDelta);
    _vector                 Get_InputToLookDir();
    void                    StartPositonLookAt(_float fTimeDelta);
    _bool                   Rotation_InputToLookDir();
    _bool                   Rotation_TargetToLookDir();
    _float                  Get_DistanceWithPlayer() const;
    _bool                   Check_RequirementIsTargeted();
   
    virtual void HitEffectSound() override;

public:
    virtual void           Call_OtherControllerHit(const PxControllersHit& In_hit) override;
  
protected:
    _float3                m_vLookAtDir;
    _float                 m_fCurrentRotateTime = 0.f;
    _float                 m_fStateTimeAcc = 100.f;
    MONSTERTYPE            m_eMonType =     MONSTERTYPE::TYPE_END; // ���� ���Ͱ� �����Ÿ������
    NORMONSTERIDLETYPE     m_eNorMonIdleType = NORMONSTERIDLETYPE::IDLEEND; // ������Ͱ� ����̵�Ÿ������
    weak_ptr<CTransform>   m_pTransformCom;  // ���� Ʈ�������޾ƿ��������ҷ�����
    _float4                m_fStartPosition;
    _bool                  m_bPatrol = false;
                           
    //TODO ������ ����      
    BOSSSTARTTYPE          m_eBossStartType = BOSSSTARTTYPE::BOSSSTARTEND;
                 

    //TODO �ӽ�
protected:                 
    _bool                  m_bAttackLookAtLimit = false; // �����ҋ��迧�ϴٰ� �������� Ǯ���
    _bool                  m_bAtkPermitAndNoHurt = false;

protected:
    _vector                Get_CurMonToStartMonDir();
    _float                 GetStartPositionToCurrentPositionDir();
    virtual void           TurnMechanism();
    _float                 ComputeAngleWithPlayer();
    _int                   ComputeDirectionToPlayer();
    _int                   Compute_DirectionToOtherPosition(const _float3& In_OtherPos);

private:
    weak_ptr<CMonster>     m_pOwnerFromMonster;

public: /* For. EventFunction */
    virtual void          OnDestroy() override;
    virtual void          OnEnable(void* _Arg = nullptr) override;
    virtual void          OnDisable() override;
                          
    virtual void          OnStateStart(const _float& In_fAnimationBlendTime) override;
    virtual void          OnStateEnd() override;

protected:
    void Free();

};

END