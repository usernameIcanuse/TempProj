#pragma once
#include "BossMonster.h"


BEGIN(Client)

class CUrd :
    public CBossMonster
{
    GAMECLASS_H(CUrd);
    CLONE_H(CUrd, CGameObject);

public:
    virtual _float  Get_CamOffset() const override {
        return 0.5f;
    }
    void  Set_MoveScale(const _float3& In_vMoveScale) { m_vMoveScale = In_vMoveScale; }
    // �������̾ȵǴ°� ����Ʈ�� ���۷��� �ּ� 8����Ʈ �Ȱ���  12����Ʈ  ���۷������̵� �����ߴ� ������� ��

    _uint  Get_CurrentDecoIndex() {
        return m_iDecoIndex;
    }
    list<weak_ptr<CJavelinWeapon>>    Get_JavelinWeapons() { return m_pJavelinWeapons; }
    list<weak_ptr<CMobWeapon>>      Get_DecoWeapons() { return   m_pDecoWeapons; }
private:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual HRESULT Start() override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render(ID3D11DeviceContext* pDeviceContext) override;
    virtual void SetUp_ShaderResource() override;
    virtual void Init_Desc() override;

public:
    void Use_DecoWeapon();
    void Reset_Weapon();
 


private:
    weak_ptr<class CEffect_Trail>   m_pTrailEffect;
    list<weak_ptr<CJavelinWeapon>>  m_pJavelinWeapons;
    list<weak_ptr<CMobWeapon>>      m_pDecoWeapons;
    weak_ptr<CBoneNode> m_pTrailBoneNode;
    _float3             m_vMoveScale = {1.f,1.f,1.f};
    _uint               m_iDecoIndex = 0;

private:
    virtual void Move_RootMotion_Internal() override;
    virtual void OnCollisionEnter(weak_ptr<CCollider> pMyCollider, weak_ptr<CCollider> pOtherCollider) override;
    virtual void OnCollisionStay(weak_ptr<CCollider> pMyCollider, weak_ptr<CCollider> pOtherCollider) override;
    virtual void OnCollisionExit(weak_ptr<CCollider> pMyCollider, weak_ptr<CCollider> pOtherCollider) override;
    virtual void OnEventMessage(_uint iArg) override;
    //��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnEnable(void* _Arg = nullptr) override;

    //��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnDisable() override;

private:
    void Free();

};

END
