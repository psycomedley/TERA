#include "stdafx.h"
#include "iState.h"
#include "cDynamicObj.h"
#include "cText.h"


iState::iState()
	: m_bHit(false)
	, m_fDamageTime(600.0f)
{
}


iState::~iState()
{
}


void iState::AddDamage(bool bDoubleHit)
{
	vector<cDynamicObj*> monsterList = GETSINGLE(cObjMgr)->GetALLMonsterList();

	for (int i = 0; i < monsterList.size(); i++)
	{
		if (!bDoubleHit)
		{
			if (!monsterList[i]->GetHit() && GETSINGLE(cCollision)->Collision(((cPlayer*)m_pParent), monsterList[i]))
			{
				float damage = monsterList[i]->Damaged(m_pParent->GetInfo());
				if (damage == -1)
					return;
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
			if (GETSINGLE(cCollision)->Collision(((cPlayer*)m_pParent), monsterList[i]))
			{
				float damage = monsterList[i]->Damaged(m_pParent->GetInfo());
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

//나중에 바꿉시다
void iState::AddEnemyDamage(cBoundingSphere sphere, bool bDoubleHit, float fDamageTime)
{
	cDynamicObj* pTarget = GETSINGLE(cObjMgr)->GetPlayer();
	if (!bDoubleHit)
	{
	if (!pTarget->GetHit() && GETSINGLE(cCollision)->Collision(&pTarget->GetSphere(), &sphere))
		{
			float damage = pTarget->Damaged(m_pParent->GetInfo());
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
		if (m_fDamageTime > fDamageTime)
		{
			if (GETSINGLE(cCollision)->Collision(&pTarget->GetSphere(), &pTarget->GetSphere()))
			{
				float damage = pTarget->Damaged(m_pParent->GetInfo());
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
