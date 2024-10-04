#pragma once
#include "Base.h"
#include "PxSimulationEventCallback.h"

BEGIN(Engine)
class CPhysXCollider;
class CPhysXController;

class CPhysX_Manager final : public CBase
{
	DECLARE_SINGLETON(CPhysX_Manager)

public:
	//enum PxShape
	//{
	//	SPHERE,
	//	BOX,


	//	SHAPE_END
	//}PXSHAPE;

	enum Scene
	{
		SCENE_CURRENT,
		SCENE_NEXT,
		SCENE_BEFORE,

		SCENE_END
	};

	typedef enum tagColliderShape
	{
		SHAPE_CHEESE,

		SHAPE_END
	}COLSHAPE;

public:
	PxConvexMesh* Get_ShapeTemplate(COLSHAPE eShape) { m_ShapeTemplate[eShape]; }
	void								Set_ShapeSphere(PxSphereGeometry* pGeometry) { m_pSphere = pGeometry; }
	void								Set_ShapeBox(PxBoxGeometry* pGeometry) { m_pBox = pGeometry; }

	void								Begin_PhysScene() { m_bSceneStart = true; }
	void								End_PhysScene() { m_bSceneStart = false; }

	void								Register_PhysXCollider(weak_ptr<CPhysXCollider> pPhysXCollider);
	weak_ptr<CPhysXCollider>			Find_PhysXCollider(const _uint In_iPhysXColliderIndex);

	void								Register_PhysXController(weak_ptr<CPhysXController> pPhysXController);
	weak_ptr<CPhysXController>			Find_PhysXController(const _uint In_iPhysXControllerIndex);

	void								Set_CurrentCameraControllerIndex(const _uint In_iPhysXCurrentCameraControllerIndex);
	_int								Get_CurrentCameraControllerIndex() const { return m_iCurrentCameraIndex; }

public:
	HRESULT	Initialize(const _uint In_iNumLayer);
	void	Tick(_float fTimeDelta);



public:
	void			Check_PhysXFilterGroup(const _uint In_iLeftLayer, const _uint In_iRightLayer);
	_uint			Get_PhysXFilterGroup(const _uint In_iIndex);

public:
	// Transform ���� (float3)��ġ�� (float4)���ʹϿ��� ����.
	HRESULT			Create_Scene(Scene eScene, PxVec3 Gravity = PxVec3(0.0f, -9.81f, 0.0f));
	HRESULT			Delete_Scene(Scene eScene);
	HRESULT			Change_Scene(Scene eNextScene, PxVec3 Gravity = PxVec3(0.0f, -9.81f, 0.0f));

	PxRigidDynamic* Create_DynamicActor(const PxTransform& t, const PxGeometry& geometry, PxMaterial* pMaterial = nullptr);
	PxRigidDynamic* Create_DynamicActor(const PxTransform& t);
	PxRigidStatic* Create_StaticActor(const PxTransform& t, const PxGeometry& geometry, PxMaterial* pMaterial = nullptr);
	PxRigidStatic* Create_StaticActor(const PxTransform& t);
	PxRevoluteJoint* Create_Joint();

	void			Add_DynamicActorAtCurrentScene(PxRigidDynamic& DynamicActor);
	void			Add_StaticActorAtCurrentScene(PxRigidStatic& StaticActor);

	void			Create_CylinderMesh(_float fRadiusBelow, _float fRadiusUpper, _float fHight, PxConvexMesh** ppOut);
	void			Create_ConvexMesh(PxVec3** pVertices, _uint iNumVertice, PxConvexMesh** ppOut);
	void			Create_ConvexMesh(const PxConvexMeshDesc& In_MeshDesc, PxConvexMesh** ppOut);
	void			Create_Material(_float fStaticFriction, _float fDynamicFriction, _float fRestitution, PxMaterial** ppOut);
	void			Create_Shape(const PxGeometry& Geometry, PxMaterial* pMaterial, const _bool isExculsive, const PxShapeFlags In_ShapeFlags, PxShape** ppOut);
	void			Create_MeshFromTriangles(const PxTriangleMeshDesc& In_MeshDesc, PxTriangleMesh** ppOut);
	void			Create_Controller(const PxCapsuleControllerDesc& In_ControllerDesc, PxController** ppOut);

private:
	void			Garbage_Collector();

private: /* For Garabage_Collector */
	_float					m_fTimeAcc = 0.f;

private:
	// Foundation�� �����ϴµ� �ʿ��� ����
	PxDefaultAllocator		m_Allocator;
	PxDefaultErrorCallback	m_ErrorCallback;
	PxFoundation* m_pFoundation;
	PxCudaContextManager* m_pCudaContextManager = nullptr;

	// PxFoundation�� �־�� Physics�� ������ �� �ִ�.
	PxPhysics* m_pPhysics;

	// CPU ���ҽ��� ȿ�������� ������ �� �ֵ��� �ϱ� ���� �����ϴ� ���� ��õ
	PxDefaultCpuDispatcher* m_pDispatcher = nullptr;

	// MeshCooking�� �ϱ� ���� ����
	PxCooking* m_pCooking = nullptr;

	// Scene
	//_uint					m_iNumScenes = 0;
	//typedef PxScene*		LPSCENE;
	PxScene* m_pScenes[SCENE_END];
	PxControllerManager* m_pControllerManager = nullptr;
	PxScene* m_pCurScene = nullptr;

	// m_pPhysics�� ����� createMaterial�ؼ� ���
	// �浹ü ������, Dynamic ������, ź������ �����Ͽ� ���
	PxMaterial* m_pMaterial;

	////Visual Debugger
	PxPvd* m_pPVD;

	PxRigidDynamic* m_pTemp = nullptr;


private:
	PxBoxGeometry* m_pBox = nullptr;
	PxSphereGeometry* m_pSphere = nullptr;

	PxConvexMesh* m_ShapeTemplate[SHAPE_END];
	_bool					m_bSceneStart = false;

private: /* For. Filter */
	vector<_uint>			m_arrCheck;

private:
	map<_uint, weak_ptr<CPhysXCollider>>	m_pPhysXCollders;
	map<_uint, weak_ptr<CPhysXController>>	m_pPhysXControllers;
	_int									m_iCurrentCameraIndex = -1;


public:
	//CollisionSimulationEventCallBack* m_pCollisionSimulationEventCallBack;

private:
	//void			Create_CheeseShape();
	//void			Create_Stack(const PxTransform& t, PxU32 size, PxReal halfExtent);



public:
	virtual void OnDestroy() override;

private:
	void Free();
};

END