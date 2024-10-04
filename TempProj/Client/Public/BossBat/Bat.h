#pragma once
#include "BossMonster.h"


BEGIN(Client)

class CBat :
    public CBossMonster
{
    GAMECLASS_H(CBat);
    CLONE_H(CBat, CGameObject);

public:
    virtual _float  Get_CamOffset() const override {
        return 0.5f;
    }

public:
    // CGameObject��(��) ���� ��ӵ�
    virtual HRESULT Initialize_Prototype() override;
    virtual HRESULT Initialize(void* pArg) override;
    virtual HRESULT Start() override;
    virtual void Tick(_float fTimeDelta) override;
    virtual void LateTick(_float fTimeDelta) override;
    virtual HRESULT Render(ID3D11DeviceContext* pDeviceContext) override;
    virtual void SetUp_ShaderResource() override;
    virtual void CollsionContent(_float fScale = 1.8f)override;
public:
    virtual void Init_Desc() override;

private:
    weak_ptr<class CEffect_Trail> m_pTrailEffect;
    weak_ptr<CBoneNode> m_pTrailBoneNode;

private:
   // virtual void Move_RootMotion_Internal() override;


private:
    virtual void OnCollisionEnter(weak_ptr<CCollider> pMyCollider, weak_ptr<CCollider> pOtherCollider) override;
    virtual void OnCollisionStay(weak_ptr<CCollider> pMyCollider, weak_ptr<CCollider> pOtherCollider) override;
    virtual void OnCollisionExit(weak_ptr<CCollider> pMyCollider, weak_ptr<CCollider> pOtherCollider) override;
    //��ü�� ���°� Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnEventMessage(_uint iArg) override;
    virtual void OnEnable(void* _Arg = nullptr) override;
    //��ü�� ���°� ��Ȱ��ȭ ���·� ����� ��, ȣ��Ǵ� �̺�Ʈ�Դϴ�.
    virtual void OnDisable() override;

private:
    void Free();

};

END
