#include "stdafx.h"
#include "CorvusStates/Talent_Effect_Growing_FeadtherLV2.h"
#include "GameManager.h"

GAMECLASS_C(CTalent_Effect_Growing_FlyingLV2);
CLONE_C(CTalent_Effect_Growing_FlyingLV2, CComponent);


_flag CTalent_Effect_Growing_FlyingLV2::Check_Requirement(weak_ptr<CPlayer> pPlayer)
{
    return (_flag)TALENT_EFFECT_FLAG::GROWING_FEATHER_LV2;
}

void CTalent_Effect_Growing_FlyingLV2::Bind_Talent_Effect(weak_ptr<CPlayer> pPlayer)
{
    return;
}

void CTalent_Effect_Growing_FlyingLV2::UnBind_Talent_Effect(weak_ptr<CPlayer> pPlayer)
{
    return;
}

void CTalent_Effect_Growing_FlyingLV2::Free()
{
}
