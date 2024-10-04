#include "stdafx.h"
#include "InventorySorter.h"
#include "GameInstance.h"
#include "Client_Defines.h"
#include "UI_ItemSlot.h"
#include "Item.h"
#include "UI_ShuffleIcon.h"
#include "UI_Inventory.h"
#include "CUtils_EasingTransform.h"
#include "EasingComponent_Transform.h"
#include "EasingComponent_Bezier.h"
#include "UIManager.h"
#include "ImGui_Manager.h"
#include "SMath.h"
#include "UIManager.h"



GAMECLASS_C(CInventorySorter)


HRESULT CInventorySorter::Initialize()
{
	m_fItemSlotSotringStartPos = { 148.f, 78.f };//Left Top


	return S_OK;
}

vector<weak_ptr<CUI_ItemSlot>> CInventorySorter::Sorting_Start(vector<weak_ptr<CUI_ItemSlot>>& vecItemSlot, _float fItemSlotOffset, _uint iSortType,
    SORTING_ANIMATION_TYPE eAnimType)
{
	//���� ����.
    m_iSortType = iSortType;

	m_vecItemSlot = vecItemSlot;

	m_fItemSlotOffset = fItemSlotOffset;

    m_fSortTime = 0.5f;

    switch (eAnimType)
    {
    case Client::CInventorySorter::SORTING_ANIMATION_TYPE::SORTING_ANIMATION_MOBILE:
	SetPostionToSortedReadyItemSlots();
        Start_Sort_TypeMobile(iSortType);
        Start_Animation_TypeMobile();
        break;
    case Client::CInventorySorter::SORTING_ANIMATION_TYPE::SORTING_ANIMATION_QUICK:
        MyQuickSort(m_vecItemSlot, 0, m_vecItemSlot.size() - 1);
        m_SortFlowList.clear();
        break;
    case Client::CInventorySorter::SORTING_ANIMATION_TYPE::SORTING_ANIMATION_QUICK_FLOW_BEZIER:
        Make_ShuffleIcon();
        MyQuickSort(m_vecItemSlot, 0, m_vecItemSlot.size() - 1);
        for (auto& elem : m_vecItemSlot)
        {
            elem.lock()->Set_RenderIcon(false);
        }
        Start_Animation_TypeFlow();
        break;
    default:
        break;
    }
    return m_vecItemSlot;
}


void CInventorySorter::Call_OnEndTransformItemSlot()//������ ���ĵǴ� ������ ������ ������ ��
{


}

void CInventorySorter::SetPostionToSortedReadyItemSlots()//�����ؾߵǴ� �����ܵ� ���� �ø�
{
	weak_ptr<CUI_ShuffleIcon> pShuffleIcon;

	for(_uint i = 0 ; i < m_vecItemSlot.size();i++)
	{
		pShuffleIcon = GAMEINSTANCE->Add_GameObject<CUI_ShuffleIcon>(LEVEL_STATIC);

		pShuffleIcon.lock()->Set_UIPosition(m_fItemSlotSotringStartPos.x +  i * m_fItemSlotOffset,
			m_fItemSlotSotringStartPos.y, 64.f, 64.f, CUI::ALIGN_LEFTTOP);
	
        pShuffleIcon.lock()->Bind_Item(m_vecItemSlot[i].lock()->Get_BindItem());
		m_listShuffleIcon.push_back(pShuffleIcon);
	}
}

void CInventorySorter::Start_Sort_TypeMobile(_uint iSortType)
{
	CUI_Inventory::INVENTORY_SORTTYPE eSortType = (CUI_Inventory::INVENTORY_SORTTYPE)iSortType;

	sort(m_vecItemSlot.begin(), m_vecItemSlot.end(),
    [&](weak_ptr<CUI_ItemSlot> pFirst, weak_ptr<CUI_ItemSlot> pSecond)
    {
        switch (eSortType)
        {
        case Client::CUI_Inventory::INVENTORY_SORTTYPE::SORT_BY_DATE:
        {
            if (pFirst.lock()->Get_BindItem().lock()->Get_CreatedTime() <
                pSecond.lock()->Get_BindItem().lock()->Get_CreatedTime())
            {
            //    _float2 fPosDest = pFirst.lock()->GetPos();
           //     _float2 fPosSour = pSecond.lock()->GetPos();

           //     pFirst.lock()->Set_UIPosition(fPosSour.x, fPosSour.y);
           //     pSecond.lock()->Set_UIPosition(fPosDest.x, fPosDest.y);
   
                return true;
            }
        }
        break;
        case Client::CUI_Inventory::INVENTORY_SORTTYPE::SORT_BY_TYPE:
            if (pFirst.lock()->Get_BindItem().lock()->Get_Type() <
                pSecond.lock()->Get_BindItem().lock()->Get_Type())
            {
            //    _float2 fPosDest = pFirst.lock()->GetPos();
           //     _float2 fPosSour = pSecond.lock()->GetPos();

            //    pFirst.lock()->Set_UIPosition(fPosSour.x, fPosSour.y);
            //    pSecond.lock()->Set_UIPosition(fPosDest.x, fPosDest.y);


                return true;

            }
            break;
        case Client::CUI_Inventory::INVENTORY_SORTTYPE::SORT_BY_QUANTITY:
            if (pFirst.lock()->Get_BindItem().lock()->Get_CurrentQuantity() >
                pSecond.lock()->Get_BindItem().lock()->Get_CurrentQuantity())
            {
            //    _float2 fPosDest = pFirst.lock()->GetPos();
            //   _float2 fPosSour = pSecond.lock()->GetPos();
            //  pFirst.lock()->Set_UIPosition(fPosSour.x, fPosSour.y);
            //   pSecond.lock()->Set_UIPosition(fPosDest.x, fPosDest.y);


                return true;
            }
            break;
        default:
            break;
        }
         return false;
    });
    list<weak_ptr<CUI_ShuffleIcon>>::iterator iter = m_listShuffleIcon.begin();
    //������ ������ ������ ����ε�.
    for (auto& elem : m_vecItemSlot)
    {
        elem.lock()->UnBind_Item();
        iter->lock()->Bind_Target(elem);
        ++iter;
    }
}

void CInventorySorter::Start_Animation_TypeMobile()
{
    if (m_listShuffleIcon.empty())
        return;

    weak_ptr<CUI_ShuffleIcon> pIcon = m_listShuffleIcon.front();

    m_listShuffleIcon.erase(m_listShuffleIcon.begin());

    pIcon.lock()->Get_Component<CEasingComponent_Transform>().lock()->Callback_LerpEnd
        += bind(&CInventorySorter::Start_Animation_TypeMobile, this);
        
    pIcon.lock()->Start_Lerp(m_fSortTime);

    for (auto& elem : m_listShuffleIcon)//��ĭ�� ������ �����.
    {
        elem.lock()->Pull_Lerp();
    }

}
void CInventorySorter::Make_ShuffleIcon()
{
    weak_ptr<CUI_ShuffleIcon> pShuffleIcon;

    m_vecShuffleIcon.clear();

    for (auto& elem : m_vecItemSlot)
    {
        _float2 ItemSlotPos = elem.lock()->GetPos();
        
        pShuffleIcon = GAMEINSTANCE->Add_GameObject<CUI_ShuffleIcon>(LEVEL_STATIC);
        pShuffleIcon.lock()->Set_UIPosition(ItemSlotPos.x, ItemSlotPos.y, 64.f, 64.f);
        pShuffleIcon.lock()->Bind_Item(elem.lock()->Get_BindItem());
        pShuffleIcon.lock()->Bind_Target(elem);


        m_vecShuffleIcon.push_back(pShuffleIcon);//���߿� �ִϸ��̼� Ǯ�� Ÿ���� ���������� ��ȯ�Ǳ� ���� ����Ʈ
    }
}
/*
    �ּ� ����� iLeft�� ����Ʈ�� ���� ����(0)
    iRight�� ����Ʈ�� ���� ������(size)
*/
void CInventorySorter::MyQuickSort(vector<weak_ptr<CUI_ItemSlot>>& vecItemSlots, _int iLeft, _int iRight)
{
    if (iLeft >= iRight)//���� ����
    {
        return;
    }

    _int    iPivot = MyPartition(vecItemSlots, iLeft, iRight, m_iSortType);

    MyQuickSort(vecItemSlots, iLeft, iPivot - 1);//���� �������� ������ ����
    MyQuickSort(vecItemSlots, iPivot + 1, iRight);//���� �������� �������� ���� 
}

_int	 CInventorySorter::MyPartition(vector<weak_ptr<CUI_ItemSlot>>& vecItemSlots, _int iLeft, _int iRight, 
        _uint iSortType)
{
    _int    iPivot = iLeft;
    weak_ptr<CUI_ItemSlot>   pPivotSlot = m_vecItemSlot[iPivot];
    _int    i = iLeft, j = iRight;

    //i�� j�� ���� = �ǹ� �˻簡 ������.
    while (i < j)
    {
        //����->�ǹ����� �˻�.
        //�ǹ����� ū �༮�� �ִ��� �˻��ؾ��ϴϱ� 
        //�ǹ����� ������ j�̵�
        while (!CheckCondition(vecItemSlots[iPivot].lock()->Get_BindItem(), vecItemSlots[j].lock()->Get_BindItem(),
            iSortType))
        {
            --j;
        }

        //�ǹ����� ���� �༮�� �ö����� �ѱ�.
        while ( i < j &&
            CheckCondition(vecItemSlots[iPivot].lock()->Get_BindItem(), vecItemSlots[i].lock()->Get_BindItem(),
            iSortType))
        {
            ++i;
        }
        MySwap(vecItemSlots, i, j);
        if (i != j)
        {
            m_SortFlowList.push_back(i);
            m_SortFlowList.push_back(j);
        }


    }

    vecItemSlots[iLeft] = vecItemSlots[i];
    vecItemSlots[i] = pPivotSlot;

    if (i != iLeft)
    {
        m_SortFlowList.push_back(iLeft);
        m_SortFlowList.push_back(i);
    }
    return i;
}
void CInventorySorter::MySwap(vector<weak_ptr<CUI_ItemSlot>>& vecItemSlots, _int iLeft, _int iRight)
{
    weak_ptr<CUI_ItemSlot> pItemSlot = vecItemSlots[iLeft];
    vecItemSlots[iLeft] = vecItemSlots[iRight];
    vecItemSlots[iRight] = pItemSlot;
}
void CInventorySorter::Start_Animation_TypeFlow()
{
    if (m_SortFlowList.empty())//���� ����. �Ȱ��� ���ĵ� ������ ���Կ��� ������ ���ε�����
    {
        for (_uint i = 0 ; i < m_vecShuffleIcon.size();i++)
        {
            m_vecShuffleIcon[i].lock()->Set_Enable(false);
        }
        m_SortFlowList.clear();
        for (auto& elem : m_vecItemSlot)
        {
            elem.lock()->Set_RenderIcon(true);
        }
        GET_SINGLE(CUIManager)->Set_UIAnimation(false);
        return;
    }
    _int            iDest = m_SortFlowList.front();

    m_SortFlowList.pop_front();
    
    _int            iSour = m_SortFlowList.front();

    m_SortFlowList.pop_front();


    weak_ptr<CUI_ShuffleIcon> pDescIcon = m_vecShuffleIcon[iDest];
   weak_ptr<CUI_ShuffleIcon> pSourIcon = m_vecShuffleIcon[iSour];


   pDescIcon.lock()->Get_Component<CEasingComponent_Bezier>().lock()->Callback_LerpEnd
        += bind(&CInventorySorter::Start_Animation_TypeFlow, this); //�ΰ� �̾Ƽ� �ϳ� ���°Ŷ�, ���� �ݹ鿡�� �޾Ƶ�.

   //string strShuffleSoundKey = "CardShot_0";
   //_int     iRandom = SMath::Random(1, 3);
   //
   //strShuffleSoundKey += to_string(iRandom);
   //strShuffleSoundKey += ".ogg";

   GAMEINSTANCE->PlaySound2D("CardShot_03.ogg", GET_SINGLE(CUIManager)->Get_SoundType(UI_SOUND_TYPE::SOUND_EFFECT));

   pDescIcon.lock()->Start_SwapLerp(pSourIcon.lock()->GetPos(), 0.5f, m_fSortTime);
   pSourIcon.lock()->Start_SwapLerp(pDescIcon.lock()->GetPos(), -0.5f, m_fSortTime);

   weak_ptr<CUI_ShuffleIcon> pTempIcon = m_vecShuffleIcon[iDest];

   m_vecShuffleIcon[iDest] = m_vecShuffleIcon[iSour];//������ ������.
   m_vecShuffleIcon[iSour] = pTempIcon;

}
/*
    Right�� �� Ŭ�� �����ؾ� �������� ������ ������.

*/
_bool CInventorySorter::CheckCondition(weak_ptr<CItem> pLeftItem, weak_ptr<CItem> pRightItem, _uint iSortType)
{
    CUI_Inventory::INVENTORY_SORTTYPE eSortType = (CUI_Inventory::INVENTORY_SORTTYPE)iSortType;

    switch (eSortType)
    {
    case Client::CUI_Inventory::INVENTORY_SORTTYPE::SORT_BY_TYPE:
        if (pLeftItem.lock()->Get_Type() <= pRightItem.lock()->Get_Type())
            return true;   
        break;
    case Client::CUI_Inventory::INVENTORY_SORTTYPE::SORT_BY_DATE:
        if (pLeftItem.lock()->Get_CreatedTime() <= pRightItem.lock()->Get_CreatedTime())
            return true;
        break;
    case Client::CUI_Inventory::INVENTORY_SORTTYPE::SORT_BY_QUANTITY:
        if (pLeftItem.lock()->Get_CurrentQuantity() <= pRightItem.lock()->Get_CurrentQuantity())
            return true;
        break;
    }
    return false;
}

shared_ptr<CInventorySorter> CInventorySorter::Create()
{
	shared_ptr<CInventorySorter> pInstance = make_shared<CInventorySorter>();

	pInstance->Initialize();

	return pInstance;
}


void CInventorySorter::Free()
{
		
}
