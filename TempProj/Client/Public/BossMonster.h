#pragma once
#include "Monster.h"

BEGIN(Client)

class CMobWeapon;
class CStatus_Boss;
class CMonsterHPBar_Boss;

class CBossMonster :
    public CMonster
{
    GAMECLASS_H(CBossMonster);
    CLONE_H(CBossMonster, CGameObject);

public:
    //typedef struct tagBossMonsterStateLinkDesc
    //{
    //    BOSSSTARTTYPE        eBossStartType;
    //    _uint                m_iAtkCounterGauge;//���������ٱ�¥���� ������������¥���Կ�  
    //    MONSTERTYPE          eMontype;
    //    //TODO �߸�
    //    _float3            vYame;
    //}STATE_LINK_MONSTER_DESC;



public:
    void Set_TargetCharacter(weak_ptr<CCharacter> In_pCharacter);
    weak_ptr<CCharacter> Get_TargetCharacter() const;
    virtual _float  Get_CamOffset() const { return 0.f; }
    _float  Get_TimeAcc() const { return m_fTimeAcc; }

    //void Set_DissolveAmount(const _float& In_fAmount) { m_fDissolveAmount = In_fAmount; }


public:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual HRESULT Start() override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual void Before_Render(_float fTimeDelta) override;
    virtual HRESULT Render(ID3D11DeviceContext* pDeviceContext) override;
    virtual HRESULT Render_ShadowDepth(_fmatrix In_LightViewMatrix, _fmatrix In_LightProjMatrix, ID3D11DeviceContext* pDeviceContext) override;

    weak_ptr<CMonsterHPBar_Boss>  Get_HPBar();

protected:
    virtual void Bind_HPBar();
    virtual void Release_Monster();
protected:
    virtual void SetUp_ShaderResource() override;

    virtual void OnCollisionEnter(weak_ptr<CCollider> pMyCollider, weak_ptr<CCollider> pOtherCollider) override;
    virtual void OnCollisionStay(weak_ptr<CCollider> pMyCollider, weak_ptr<CCollider> pOtherCollider) override;
    virtual void OnCollisionExit(weak_ptr<CCollider> pMyCollider, weak_ptr<CCollider> pOtherCollider) override;
    //��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnEnable(void* _Arg = nullptr) override;
    //��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnDisable() override;

protected:
    _float      m_fTimeAcc = 0.f;
    //_float      m_fDissolveAmount = 0.f;

protected:
    weak_ptr<CPhysXCollider> m_pPhysXColliderCom;
protected:
    weak_ptr<CStateBase> m_pStandState;

    weak_ptr<CCharacter>      m_pTargetCharacter; // = player
    weak_ptr<CTexture>        m_pDissolveTextureCom;
    MONSTERWEAPONTYPE         m_eMonWeaPonType = MONSTERWEAPONTYPE::MON_WEAPON_END;

private:
    void Free();


};

END