#include "stdafx.h"
#include "cBattleMgr.h"
#include "cDynamicObj.h"
#include "cText.h"
#include "cPlayer.h"

cBattleMgr::cBattleMgr()
	: m_bHit(false)
	, m_fDamageTime(600.0f)
	, m_bHitted(false)
{
}


cBattleMgr::~cBattleMgr()
{
}


void cBattleMgr::Update()
{
	if (m_bMultiHit)
		m_fDamageTime += GETSINGLE(cTimeMgr)->getElapsedTime();
}


void cBattleMgr::Release()
{
	/*for each(auto p in m_vecHitted)
	{
		p->Release();
	}*/
	cSingleton::Release();
}


void cBattleMgr::PlayerDamage(bool bDoubleHit, float fAddDamage)
{
	cPlayer* pParent = (cPlayer*)GETSINGLE(cObjMgr)->GetPlayer();
	vector<cDynamicObj*> monsterList = GETSINGLE(cObjMgr)->GetALLMonsterList();

	for (int i = 0; i < monsterList.size(); i++)
	{
		if (!bDoubleHit)
		{
			if (monsterList[i]->GetPassedVanishTime() > 0.0f)
				continue;
			if (!monsterList[i]->GetHit() && GETSINGLE(cCollision)->Collision(((cPlayer*)pParent), monsterList[i]))
			{
				float damage = monsterList[i]->Damaged(pParent->GetInfo(), fAddDamage);
				if (damage == -1)
					continue;
				m_vecHitted.push_back(monsterList[i]);
				GETSINGLE(cTextMgr)->AddList("PlayerDamage");
				cText* text = GETSINGLE(cTextMgr)->GetLastTextInList();
				text->SetTextFloat(damage);
				text->SetPosition(D3DXVECTOR2(GetWindowWidth() / 2 + GetFromIntTo(-200, 200), GetWindowHeight() / 2 + GetFromIntTo(-50, 50)));
				text->Start();
			}
		}
		else
		{
			if (monsterList[i]->GetPassedVanishTime() > 0.0f)
				continue;
			if (GETSINGLE(cCollision)->Collision(((cPlayer*)pParent), monsterList[i]))
			{
				float damage = monsterList[i]->Damaged(pParent->GetInfo(), fAddDamage);
				if (damage == -1)
					return;
				m_vecHitted.push_back(monsterList[i]);
				GETSINGLE(cTextMgr)->AddList("PlayerDamage");
				cText* text = GETSINGLE(cTextMgr)->GetLastTextInList();
				text->SetTextFloat(damage);
				text->SetPosition(D3DXVECTOR2(GetWindowWidth() / 2 + GetFromIntTo(-100, 100), GetWindowHeight() / 2 + GetFromIntTo(-50, 50)));
				text->Start();
			}
		}
	}
}


void cBattleMgr::EnemyDamage(cDynamicObj* pParent, cBoundingSphere sphere, float fAddDamage /*= 0.0f*/, bool bMultieHit /*= false*/, float fDamageTime /*= 0.0f*/)
{
	cPlayer* pTarget = (cPlayer*)GETSINGLE(cObjMgr)->GetPlayer();
	if (!bMultieHit)
	{
		if (!m_bHitted && GETSINGLE(cCollision)->Collision(&pTarget->GetSphere(), &sphere))
		{
			float damage = pTarget->Damaged(pParent->GetInfo(), fAddDamage);
			if (damage == -1)
				return;
			m_bHitted = true;
			//m_vecHitted.push_back(pTarget);
			GETSINGLE(cTextMgr)->AddList("MonsterDamage");
			cText* text = GETSINGLE(cTextMgr)->GetLastTextInList();
			text->SetTextFloat(-damage);
			text->SetPosition(D3DXVECTOR2(GetWindowWidth() / 2 + GetFromIntTo(-200, 200), GetWindowHeight() / 2 + GetFromIntTo(-50, 50)));
			text->Start();
		}
	}
	else
	{
		m_bMultiHit = bMultieHit;
		if (m_fDamageTime > fDamageTime)
		{
			if (GETSINGLE(cCollision)->Collision(&pTarget->GetSphere(), &sphere))
			{
				float damage = pTarget->Damaged(pParent->GetInfo(), fAddDamage);
				if (damage == -1)
					return;
				m_bHitted = true;
				//m_vecHitted.push_back(pTarget);
				GETSINGLE(cTextMgr)->AddList("MonsterDamage");
				cText* text = GETSINGLE(cTextMgr)->GetLastTextInList();
				text->SetTextFloat(-damage);
				text->SetPosition(D3DXVECTOR2(GetWindowWidth() / 2 + GetFromIntTo(-200, 200), GetWindowHeight() / 2 + GetFromIntTo(-50, 50)));
				text->Start();
				m_fDamageTime = 0.0f;
			}
		}
	}
}


void cBattleMgr::Reset(E_OBJTYPE eType)
{
	switch (eType)
	{
	case E_MONSTER:
		m_bHitted = false;
		break;
	case E_PLAYER:
		m_fDamageTime = 600.0f;
		for (int i = 0; i < m_vecHitted.size(); i++)
			m_vecHitted[i]->SetHit(false);
		m_vecHitted.clear();
		m_bMultiHit = false;
		m_bHit = false;
		break;
	}
}


void cBattleMgr::ResetList(E_OBJTYPE eType)
{
	switch (eType)
	{
	case E_MONSTER:
		m_bHitted = false;
		break;
	case E_PLAYER:
		for (int i = 0; i < m_vecHitted.size(); i++)
			m_vecHitted[i]->SetHit(false);
		m_vecHitted.clear();
		break;
	}
}