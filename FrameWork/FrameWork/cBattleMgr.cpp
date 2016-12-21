#include "stdafx.h"
#include "cBattleMgr.h"
#include "cDynamicObj.h"
#include "cText.h"
#include "cPlayer.h"

cBattleMgr::cBattleMgr()
	: m_bHit(false)
	, m_fDamageTime(600.0f)
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
	cSingleton::Release();
}


void cBattleMgr::PlayerDamage(bool bDoubleHit)
{
	cPlayer* pParent = (cPlayer*)GETSINGLE(cObjMgr)->GetPlayer();
	vector<cDynamicObj*> monsterList = GETSINGLE(cObjMgr)->GetALLMonsterList();

	for (int i = 0; i < monsterList.size(); i++)
	{
		if (!bDoubleHit)
		{
			if (!monsterList[i]->GetHit() && GETSINGLE(cCollision)->Collision(((cPlayer*)pParent), monsterList[i]))
			{
				float damage = monsterList[i]->Damaged(pParent->GetInfo());
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
			if (GETSINGLE(cCollision)->Collision(((cPlayer*)pParent), monsterList[i]))
			{
				float damage = monsterList[i]->Damaged(pParent->GetInfo());
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


void cBattleMgr::EnemyDamage(cDynamicObj* pParent, cBoundingSphere sphere, bool bMultieHit /*= false*/, float fDamageTime /*= 0.0f*/)
{
	cDynamicObj* pTarget = GETSINGLE(cObjMgr)->GetPlayer();
	if (!bMultieHit)
	{
		if (!pTarget->GetHit() && GETSINGLE(cCollision)->Collision(&pTarget->GetSphere(), &sphere))
		{
			float damage = pTarget->Damaged(pParent->GetInfo());
			if (damage == -1)
				return;
			m_vecHitted.push_back(pTarget);
			GETSINGLE(cTextMgr)->AddList("MonsterDamage");
			cText* text = GETSINGLE(cTextMgr)->GetLastTextInList();
			text->SetTextFloat(damage);
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
				float damage = pTarget->Damaged(pParent->GetInfo());
				if (damage == -1)
					return;
				m_vecHitted.push_back(pTarget);
				GETSINGLE(cTextMgr)->AddList("MonsterDamage");
				cText* text = GETSINGLE(cTextMgr)->GetLastTextInList();
				text->SetTextFloat(damage);
				text->SetPosition(D3DXVECTOR2(GetWindowWidth() / 2 + GetFromIntTo(-200, 200), GetWindowHeight() / 2 + GetFromIntTo(-50, 50)));
				text->Start();
				m_fDamageTime = 0.0f;
			}
		}
	}
}


void cBattleMgr::Reset()
{
	m_fDamageTime = 600.0f;
	for (int i = 0; i < m_vecHitted.size(); i++)
		m_vecHitted[i]->SetHit(false);
	m_vecHitted.clear();
	m_bHit = false;
	m_bMultiHit = false;
}


void cBattleMgr::ResetList()
{
	for (int i = 0; i < m_vecHitted.size(); i++)
		m_vecHitted[i]->SetHit(false);
	m_vecHitted.clear();
}