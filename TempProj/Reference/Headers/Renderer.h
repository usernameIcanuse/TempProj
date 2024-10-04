#pragma once

/* ȭ�鿡 �׷������� ��ü���� �׸��� ������� ��Ƽ� �����ϳ�.  */
/* ������ �ִ� ��ü���� �����Լ��� ȣ�����ֳ�. */

#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CRenderer : public CComponent
{
	GAMECLASS_H(CRenderer)
	DECLARE_CLONABLE(CRenderer, CComponent)
	 
public:
	HRESULT Add_RenderGroup(RENDERGROUP	eGroup, weak_ptr<class CGameObject> pGameObject);
	//�ؽ�ó ó��
	/*HRESULT Set_Textures_From_Key(const _tchar* _Str_Key, MEMORY_TYPE _eType = MEMORY_TYPE::MEMORY_END);
	HRESULT Bind_Texture(_uint _iIndex);
	HRESULT UnBind_Texture();
	LPDIRECT3DBASETEXTURE9 Get_Texture(_uint _iIndex);*/

public:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void	Start() override;

protected:
	void Free();
};

END