#pragma once
#include "Base.h"
#include "Client_Defines.h"


BEGIN(Client)

class CUI_ItemPopup;

class CItemPopup_Queue : public CBase
{
public:
	void		AddPopup(ITEM_NAME eItemName);
	void		Call_EndFadeOut(weak_ptr<CUI_ItemPopup> pItemPopup);


private:
	void		Pull_Popup();

	void		Create_PopupUI(ITEM_NAME eItemName);

	
private:
	_uint		m_iMaxViewPopup = 4;
	_float		m_fPopupOffset = 105.f;

	list<weak_ptr<CUI_ItemPopup>>	m_pItemPopupList;//���� �������� �ִ� �༮��

	queue<weak_ptr<CUI_ItemPopup>>	m_pItemPopupQueue;//�������� ��⿭�� �ɸ� �༮��


public:
	static shared_ptr<CItemPopup_Queue>	Create();

};

END
