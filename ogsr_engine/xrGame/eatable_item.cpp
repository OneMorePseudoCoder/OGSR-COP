////////////////////////////////////////////////////////////////////////////
//	Module 		: eatable_item.cpp
//	Created 	: 24.03.2003
//  Modified 	: 29.01.2004
//	Author		: Yuri Dobronravin
//	Description : Eatable item
////////////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "eatable_item.h"
#include "physic_item.h"
#include "Level.h"
#include "entity_alive.h"
#include "EntityCondition.h"
#include "InventoryOwner.h"

CEatableItem::CEatableItem()
{
    m_fHealthInfluence = 0;
    m_fPowerInfluence = 0;
    m_fSatietyInfluence = 0;
    m_fRadiationInfluence = 0;
    m_fPsyHealthInfluence = 0;

    m_iPortionsNum = -1;

    m_physic_item = 0;
}

CEatableItem::~CEatableItem() {}

DLL_Pure* CEatableItem::_construct()
{
    m_physic_item = smart_cast<CPhysicItem*>(this);
    return (inherited::_construct());
}

void CEatableItem::Load(LPCSTR section)
{
    inherited::Load(section);

    m_fHealthInfluence = pSettings->r_float(section, "eat_health");
    m_fPowerInfluence = pSettings->r_float(section, "eat_power");
    m_fSatietyInfluence = pSettings->r_float(section, "eat_satiety");
    m_fRadiationInfluence = pSettings->r_float(section, "eat_radiation");
    m_fWoundsHealPerc = pSettings->r_float(section, "wounds_heal_perc");
    clamp(m_fWoundsHealPerc, 0.f, 1.f);
    m_fPsyHealthInfluence = READ_IF_EXISTS(pSettings, r_float, section, "eat_psy_health", 0.0f);
    m_fThirstInfluence = READ_IF_EXISTS(pSettings, r_float, section, "eat_thirst", 0.0f);

    m_iStartPortionsNum = pSettings->r_s32(section, "eat_portions_num");
    m_fMaxPowerUpInfluence = READ_IF_EXISTS(pSettings, r_float, section, "eat_max_power", 0.0f);
    VERIFY(m_iPortionsNum < 10000);
}

BOOL CEatableItem::net_Spawn(CSE_Abstract* DC)
{
    if (!inherited::net_Spawn(DC))
        return FALSE;

    m_iPortionsNum = m_iStartPortionsNum;

    return TRUE;
};

bool CEatableItem::Useful() const
{
    if (!inherited::Useful())
        return false;

    //проверить не все ли еще съедено
    if (Empty())
        return false;

    return true;
}

void CEatableItem::OnH_B_Independent(bool just_before_destroy)
{
    if (!Useful())
    {
        object().setVisible(FALSE);
        object().setEnabled(FALSE);
        if (m_physic_item)
            m_physic_item->m_ready_to_destroy = true;
    }
    inherited::OnH_B_Independent(just_before_destroy);
}

void CEatableItem::UseBy(CEntityAlive* entity_alive)
{
    SMedicineInfluenceValues V;
    V.Load(m_physic_item->cNameSect());

    CInventoryOwner* IO = smart_cast<CInventoryOwner*>(entity_alive);
    R_ASSERT(IO);
    R_ASSERT(m_pCurrentInventory == IO->m_inventory);
    R_ASSERT(object().H_Parent()->ID() == entity_alive->ID());

    entity_alive->conditions().ApplyInfluence(V, m_physic_item->cNameSect());

    for (u8 i = 0; i < (u8)eBoostMaxCount; i++)
    {
        if (pSettings->line_exist(m_physic_item->cNameSect().c_str(), ef_boosters_section_names[i]))
        {
            SBooster B;
            B.Load(m_physic_item->cNameSect(), (EBoostParams)i);
            entity_alive->conditions().ApplyBooster(B, m_physic_item->cNameSect());
        }
    }

    entity_alive->conditions().SetMaxPower(entity_alive->conditions().GetMaxPower() + m_fMaxPowerUpInfluence);

    //уменьшить количество порций
    if (m_iPortionsNum > 0)
        --(m_iPortionsNum);
    else
        m_iPortionsNum = 0;
}

void CEatableItem::ZeroAllEffects()
{
    m_fHealthInfluence = 0.f;
    m_fPowerInfluence = 0.f;
    m_fSatietyInfluence = 0.f;
    m_fRadiationInfluence = 0.f;
    m_fMaxPowerUpInfluence = 0.f;
    m_fPsyHealthInfluence = 0.f;
    m_fWoundsHealPerc = 0.f;
    m_fThirstInfluence = 0.f;
}

void CEatableItem::SetRadiation(float _rad) { m_fRadiationInfluence = _rad; }