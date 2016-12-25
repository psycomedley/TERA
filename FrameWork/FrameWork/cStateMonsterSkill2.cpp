#include "stdafx.h"
#include "cStateMonsterSkill2.h"
#include "cDynamicObj.h"
#include "cBoundingSphere.h"


cStateMonsterSkill2::cStateMonsterSkill2()
{
}


cStateMonsterSkill2::~cStateMonsterSkill2()
{
}


void cStateMonsterSkill2::Start()
{
	ST_ANIMATION_INFO aniInfo(m_nSkillIndex, true, true);
	m_pParent->AddAnimation(aniInfo);
	m_pParent->AnimationStart();
}


void cStateMonsterSkill2::Update()
{
	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_ATTACK)
	{
		if (m_pParent->GetCurrentAnimPosition() >= 0.36f && m_pParent->GetCurrentAnimPosition() <= 0.45f)
		{
			//cBoundingSphere* sphere = new cBoundingSphere;
			//D3DXVECTOR3 vec = m_pParent->GetPosition();
			//vec.x += m_pParent->GetDirection().x * -5;
			//sphere->Setup(&vec, 2.5);
			//GETSINGLE(cDevice)->BeginRender();
			//sphere->Render(sphere->GetCenter(), D3DXVECTOR3(1, 1, 1));
			//GETSINGLE(cDevice)->EndRender();
			
			cBoundingSphere sphere;
			D3DXVECTOR3 vec = m_pParent->GetPosition();
			vec.x += m_pParent->GetDirection().x * -5;
			sphere.SetCenter(vec);
			sphere.SetRadius(3);


			GETSINGLE(cBattleMgr)->EnemyDamage(m_pParent, sphere);
			PlaySound(E_SOUND_ATK);
		}
	}
}


void cStateMonsterSkill2::End()
{
	GETSINGLE(cBattleMgr)->Reset(E_MONSTER);

	m_pParent->AnimationRemove();
	m_pParent->ChangeState(E_STATE_WAIT);
}


void cStateMonsterSkill2::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	m_bSoundPlay = false;
	m_bSoundPlay2 = false;
	End();
}
