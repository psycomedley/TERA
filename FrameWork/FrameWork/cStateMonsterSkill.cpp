#include "stdafx.h"
#include "cStateMonsterSkill.h"
#include "cDynamicObj.h"


cStateMonsterSkill::cStateMonsterSkill()
{
}


cStateMonsterSkill::~cStateMonsterSkill()
{
}


void cStateMonsterSkill::Start()
{
	ST_ANIMATION_INFO aniInfo(m_nSkillIndex, true, true);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateMonsterSkill::Update()
{
	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_ATTACK)
	{
		if (m_pParent->GetCurrentAnimPosition() >= 0.25f && m_pParent->GetCurrentAnimPosition() <= 0.43f)
		{
			GETSINGLE(cBattleMgr)->EnemyDamage(m_pParent, m_pParent->GetSphere());
			PlaySound(E_SOUND_ATK);
		}
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_SKILL1)
	{
		PlaySound(E_SOUND_SKILL1);
		if (m_pParent->GetCurrentAnimPosition() >= 0.64f && m_pParent->GetCurrentAnimPosition() <= 0.86f)
		{
			m_pParent->Move(0.4f);

			GETSINGLE(cBattleMgr)->EnemyDamage(m_pParent, m_pParent->GetSphere(), 100);
		//	GETSINGLE(cSoundMgr)->Play(m_pParent->GetSoundKey(E_SOUND_SKILL1));
		}
	}
}


void cStateMonsterSkill::End()
{
	GETSINGLE(cBattleMgr)->Reset(E_MONSTER);

	m_pParent->AnimationRemove();
	m_pParent->ChangeState(E_STATE_WAIT);
}


void cStateMonsterSkill::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	End();
	m_bSoundPlay = false;
	m_bSoundPlay2 = false;
}