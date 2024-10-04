#pragma once

#include "GameObject.h"


BEGIN(Engine)

class ENGINE_DLL CCamera abstract : public CGameObject
{
	GAMECLASS_H(CCamera)


public:
	typedef struct CameraDesc
	{
		/*
		1. Ʈ������������ Ŭ�󿡼� �����ߴ�.
		2. ������ü�� �����Ͽ� ������ ī�޶� Ʈ������ ������Ʈ�� �������� �߰��ϰ�ʹ�.
		3. ���������� Ŭ�󿡼� �߰��� Ʈ������ ������ ������ �����ش�.
		*/
		_float4		vEye;
		_float4		vAt;
		_float		fFovy;
		_float		fAspect;
		_float		fNear;
		_float		fFar;

	}CAMERADESC;
protected:
	CCamera(const CCamera& Prototype);
	
public:
	virtual HRESULT Initialize_Prototype();
	virtual HRESULT Initialize(void* pArg);
	virtual HRESULT Start() override;
	virtual void Tick(_float fTimeDelta);
	virtual void LateTick(_float fTimeDelta);
	virtual HRESULT Render(ID3D11DeviceContext* pDeviceContext);

public:
	void Init_Camera(const CAMERADESC& CameraDesc);

protected:
	CAMERADESC						m_CameraDesc;

	/* Ŭ�󿡼� �߰��� Ʈ�������� �ƴ϶�. �������� ������ �߰��ϴ� Ʈ�������̴�.  */
	/* Ŭ�󳻿��� ���� �������� �� �� �ֱ� ������, ���� Ŭ�󿡼��� Ʈ������ �±׸� Ȯ���� �� �ֶǷ� ���ֱ�����. */

protected:
	virtual HRESULT Bind_PipeLine();
	

public:
	//virtual CGameObject* Clone(void* pArg) = 0;
	void Free();
};

END