#pragma once
#include "ClientComponent.h"

BEGIN(Client)

class CPlayerStateBase;
class CRequirement_PlayerStatusMana;
class CRequirement_Time;

class CSkill_Base : public CClientComponent
{

public:
    GAMECLASS_H(CSkill_Base)
    CLONE_H(CSkill_Base, CComponent)

public:
                                        // CClientComponent��(��) ���� ��ӵ�
    virtual HRESULT                     Initialize_Prototype() override;
    virtual HRESULT                     Initialize(void* pArg) override;
    virtual void                        Start() override;
    virtual void                        Tick(_float fTimeDelta) override;
    virtual void                        LateTick(_float fTimeDelta) override;

public:
    _float                              Get_SkillCoolDown() { return m_fSkillCoolDown; }

    SKILL_NAME                          Get_SkillName() { return m_eSkillName; }
    SKILL_TYPE                          Get_SkillType() { return m_eSkillType; }
    virtual weak_ptr<CPlayerStateBase>  Get_SkillState() { return m_pSkillState; }
    virtual weak_ptr<CPlayerStateBase>  Get_ExpansionSkillState() { return m_pExpansionSkillState; }

    _bool                               Get_Unlock() { return m_bUnlock; }
    _uint                               Get_CurrentSkillLevel() { return m_iCurrentSkillLevel; }
    _uint                               Get_MaxSkillLevel() { return m_iMaxSkillLevel; }
    ITEM_NAME                           Get_RequirementSkillPiece() { return m_eRequirementSkillPiece; }

    void                                Set_CurrentSkillLevel(_uint iCurrentSkillLevel) { m_iCurrentSkillLevel = iCurrentSkillLevel; }
    void                                Set_Unlock(_bool bUnlock) { m_bUnlock = bUnlock; }



protected:
    virtual void                        RegisterThisSkillFromSkillSystem();

public:
    /*
     ������ �Ҹ��ϴ� ��ų�� �ƴ϶� ü���� �Ҹ��ϴ� ��ų�� �ִٸ�
      override�ؼ� ó���������.
    */
    virtual _bool   Is_UseAble();
    
    virtual void    UseSkill();

    _float  Get_RatioCoolDown();

    virtual void            Reset_Skill();

public:
    void                    Clear_Callback();

    FDelegate<>             Callback_StartSkill;//��ų�� �����Ҷ� �ߵ�
    FDelegate<_float>       Callback_UpdateCoolDown;//��Ÿ���� ���� �� ƽ���� �ߵ�
    FDelegate<>             Callback_EndCoolDown;//��Ÿ���� �� ������ �� �ߵ�

protected:
    virtual void            Init_SkillInfo() {};
    virtual void            Init_State() {};//��ų�� ��!��!��! ���¸� �����ϰ� �־�� �Ѵ�.

protected:
    virtual void            Start_Skill(_bool bExapnsion = false);
    virtual void            End_Skill();

protected:
    shared_ptr<CRequirementChecker>             m_pRequirementChecker;
    shared_ptr<CRequirement_Time>               m_pRequirementTime;


    shared_ptr<CRequirementChecker>             m_pExpansionChecker;
    shared_ptr<CRequirement_Time>               m_pExpansionTime;


    shared_ptr<CRequirement_PlayerStatusMana>   m_pRequirementMana;

    _bool                                       m_bUseAble = false;
    _bool                                       m_bInputedKey= false;
    _bool                                       m_bUnlock = false;


    SKILL_NAME                                  m_eSkillName;
    SKILL_TYPE                                  m_eSkillType;
    
    ITEM_NAME                                   m_eRequirementSkillPiece = ITEM_NAME::ITEM_NAME_END;

    _float                                      m_fSkillCoolDown;
    _float                                      m_fExpansionTime = 0.3f;
    
    
    _float                                      m_fRequiredCost;

    weak_ptr<CPlayerStateBase>                  m_pSkillState;
    weak_ptr<CPlayerStateBase>                  m_pExpansionSkillState;

    _uint                                       m_iMaxSkillLevel = 0;
    _uint                                       m_iCurrentSkillLevel = 0;
    
private:
    void                        Free();
};

END
