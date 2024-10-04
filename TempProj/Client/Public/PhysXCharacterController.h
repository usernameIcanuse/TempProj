#pragma once
#include "PhysXController.h"
#include "Client_Defines.h"

BEGIN(Client)

class CPhysXCharacterController :
	public CPhysXController, public PxControllerBehaviorCallback
{
	GAMECLASS_H(CPhysXCharacterController);
	SHALLOW_COPY(CPhysXCharacterController);
	DECLARE_CLONABLE(CPhysXCharacterController, CComponent);

protected:
	HRESULT Initialize_Prototype();
	HRESULT Initialize(void* pArg) override;
	virtual void	Start() override;

public: // ������ ��Ʈ�ѷ� ����
	virtual bool filter(const PxController& a, const PxController& b) override;

public: // Hit Report
	virtual void onShapeHit(const PxControllerShapeHit& hit) override;
	virtual void onControllerHit(const PxControllersHit& hit) override;
	virtual void onObstacleHit(const PxControllerObstacleHit& hit) override;

	// PxControllerBehaviorCallback��(��) ���� ��ӵ�
	virtual PxControllerBehaviorFlags getBehaviorFlags(const PxShape& shape, const PxActor& actor) override;
	virtual PxControllerBehaviorFlags getBehaviorFlags(const PxController& controller) override;
	virtual PxControllerBehaviorFlags getBehaviorFlags(const PxObstacle& obstacle) override;




public:
	virtual void Init_Controller(const PxCapsuleControllerDesc& In_ControllerDesc, const _uint In_CollisionLayer) override;

public:
	virtual void						Synchronize_Transform(weak_ptr<CTransform> pTransform, _fvector In_vOffset = { 0.f, 0.f, 0.f }) override;
	virtual PxControllerCollisionFlags	Synchronize_Controller(weak_ptr<CTransform> pTransform, PxF32 elapsedTime, PxControllerFilters& filters, _fvector In_vOffset = { 0.f, 0.f, 0.f }) override;
	virtual PxControllerCollisionFlags	Set_Position(_fvector In_vPosition, PxF32 elapsedTime, PxControllerFilters& filters) override;
	virtual PxControllerCollisionFlags	MoveWithRotation(_fvector disp, PxF32 minDist, PxF32 elapsedTime, PxControllerFilters& filters, const PxObstacleContext* obstacles, weak_ptr<CTransform> pTransform, const _flag In_RootFlag = (_byte)ROOTNODE_FLAG::X + (_byte)ROOTNODE_FLAG::Y + (_byte)ROOTNODE_FLAG::Z) override;
	virtual PxControllerCollisionFlags	Move(_fvector disp, PxF32 minDist, PxF32 elapsedTime, PxControllerFilters& filters, const PxObstacleContext* obstacles = nullptr) override;
	virtual PxControllerCollisionFlags	MoveGravity(const _float fDeltaTime, PxControllerFilters& filters)  override;

public:

public:
	_bool Move_FootOffset(const _float fTimeDelta);

private:
	_float3 m_vPrePosition;
	PxShape* m_pLastCollisionShape = nullptr;
	PxRigidActor* m_pLastCollisionActor = nullptr;
	PxControllerCollisionFlags m_PreResultFlags;


private:
	void Free();

};

END