#pragma once
#include "ClientComponent.h"

BEGIN(Client)

class CRequirementChecker;
class CRequirement_Time;
class CRequirement_PlayerStatusMana;

class CSkill_Interface : public CClientComponent
{
public:
    GAMECLASS_H(CSkill_Interface)

    /*
     ������ �Ҹ��ϴ� ��ų�� �ƴ϶� ü���� �Ҹ��ϴ� ��ų�� �ִٸ�
      override�ؼ� ó���������.
    */
    virtual _bool   Is_UseAble()    PURE;
    virtual void    UseSkill()      PURE;

protected:
    virtual void            Init_SkillInfo()   PURE;
    virtual void            Init_State()       PURE;//��ų�� ��!��!��! ���¸� �����ϰ� �־�� �Ѵ�.


protected:
    virtual void            Start_Skill() PURE;
    virtual void            End_Skill() PURE;



};

END