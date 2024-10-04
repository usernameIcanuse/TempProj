#pragma once
#include "NorMonsterStateBase.h"

BEGIN(Engine)
class CModel;
END

BEGIN(Client)

class CNorMonState_Run :
	public CNorMonsterStateBase
{
	GAMECLASS_H(CNorMonState_Run);
	CLONE_H(CNorMonState_Run, CComponent)
		SHALLOW_COPY(CNorMonState_Run)

public:
	void  Set_ClosePlayer(_bool ClosePlayer) { m_bClosePlayer = ClosePlayer; }
	void  Set_MonIdleType(NORMONSTERIDLETYPE IDLETYPE);
	void  Set_GardnerAtkIndex(_uint GardnerAtkIndex) {	m_iGardnerAtkIndex = GardnerAtkIndex;}
	void  Set_GardnerPlusAtkIndex(_uint GardnerAtkIndex) { m_iGardnerAtkIndex += GardnerAtkIndex; }
	void  Set_RunCheck(_bool RunCheck) { m_bRunCheck = RunCheck; }


protected:
	virtual HRESULT Initialize_Prototype() override;
	virtual HRESULT Initialize(void* pArg) override;
	virtual void Start() override;
	virtual void Tick(_float fTimeDelta) override;
	virtual void LateTick(_float fTimeDelta) override;

protected:
	virtual void OnStateStart(const _float& In_fAnimationBlendTime) override;
	virtual void OnStateEnd() override;
	virtual _bool Check_AndChangeNextState() override;


private:
	_float m_fMaxSpeed = 7.f;
	_float m_fCurrentSpeed = 3.6f;
	_float m_fAccel = 0.f;
	_bool  m_bRunCheck = false; // ���̵鿡�� ������ ������ 8������ �ѹ������� �����̰� �ٽþ��̵�ΰ��� �ٽ÷����� �״������� �����ϰԲ�«
	// 8���� ���������� �޽� ������������ Ʈ��ιٲ��� 
	_uint  m_iGardnerAtkIndex = 0;


	//TODO �߸�
	_bool m_bClosePlayer = true;
private:
	virtual void OnEventMessage(_uint iArg) override;
	void Call_AnimationEnd(_uint iEndAnimIndex);
protected:
	virtual void OnDestroy() override;
	void Free();

};

END
