#include "stdafx.h"
#include "cStateCombo.h"
#include "cDynamicObj.h"
#include "cPlayer.h"
#include "cCamera.h"
#include "cCircleEffect.h"


cStateCombo::cStateCombo()
	: m_bNextAttack(false)
{
}


cStateCombo::~cStateCombo()
{
	SAFE_RELEASE(m_pCombo1Effect);
	SAFE_RELEASE(m_pCombo2Effect);
	SAFE_RELEASE(m_pCombo3Effect);
	SAFE_RELEASE(m_pCombo4Effect);
}



void cStateCombo::Start()
{
	ST_ANIMATION_INFO aniInfo(E_ANI_COMBO1, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO2, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO3, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO4, true, false);
	m_pParent->AddAnimation(aniInfo);
	aniInfo.SetInfo(E_ANI_COMBO5, true, false);
	m_pParent->AddAnimation(aniInfo);

	m_pParent->AnimationStart();
	
	StartCombo1 = false;
	StartCombo2 = false;
	StartCombo3 = false;
	StartCombo4 = false;

}


void cStateCombo::Update()
{
	vector<cDynamicObj*> monsterList = GETSINGLE(cObjMgr)->GetALLMonsterList();

	for (int i = 0; i < monsterList.size(); i++)
	{
//		if (GETSINGLE(cCollision)->Collision(&m_pParent->GetSphere(), &monsterList[i]->GetSphere()))
		if (GETSINGLE(cCollision)->CollisionOBB(&m_pParent->GetBox(), &monsterList[i]->GetBox()))
		{
			//Damage
			OutputDebugString("Hit\n");
		}
	}


	if (MOUSE->IsStayKeyDown(MOUSEBTN_LEFT))
		if (m_pParent->GetCurrentAnimPosition() > 0.5f)
			m_bNextAttack = true;

	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO1 ||
		m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO2 || 
		m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO3)
		m_pParent->Move(0.05f);

	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO4)
		if (m_pParent->GetCurrentAnimPosition() > 0.5f)
			m_pParent->Move(0.05f);
	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO5)
		if (m_pParent->GetCurrentAnimPosition() < 0.5f)
			m_pParent->Move(0.05f);

	if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO1)
	{
		if (m_pParent->GetCurrentAnimPosition() >= 0.31f && m_pParent->GetCurrentAnimPosition() <= 0.41f)
		{
			if (!StartCombo1)
			{
				m_pCombo1Effect = new cCircleEffect("Effect", "blueCircle.x");
				StartCombo1 = true;
				m_pCombo1Effect->Setup(1, 0.2f, true, D3DXVECTOR3(0.2f, 0.2f, 0.2f), D3DXVECTOR3(m_pParent->GetPosition().x,
					m_pParent->GetPosition().y + 1,
					m_pParent->GetPosition().z), m_pParent->GetAngle() + D3DX_PI/2);
				m_pCombo1Effect->Start();
			}
		}
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO2)
	{
		if (m_pParent->GetCurrentAnimPosition() >= 0.31f && m_pParent->GetCurrentAnimPosition() <= 0.41f)
		{
			if (!StartCombo2)
			{
				m_pCombo2Effect = new cCircleEffect("Effect", "blueCircle.x");
				StartCombo2 = true;
				m_pCombo2Effect->Setup(1, 0.2f, false, D3DXVECTOR3(0.2f, 0.2f, 0.2f), D3DXVECTOR3(m_pParent->GetPosition().x,
					m_pParent->GetPosition().y + 1,
					m_pParent->GetPosition().z), m_pParent->GetAngle() - D3DX_PI / 2);
				m_pCombo2Effect->Start();
			}
		}
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO4)
	{
		if (m_pParent->GetCurrentAnimPosition() >= 0.2f && m_pParent->GetCurrentAnimPosition() <= 0.37f)
		{
			if (!StartCombo3)
			{
				m_pCombo3Effect = new cCircleEffect("Effect", "blueCircle.x");
				StartCombo3 = true;
				m_pCombo3Effect->Setup(4, 0.5f, false, D3DXVECTOR3(0.2f, 0.2f, 0.2f), D3DXVECTOR3(m_pParent->GetPosition().x,
					m_pParent->GetPosition().y + 1,
					m_pParent->GetPosition().z), m_pParent->GetAngle() - D3DX_PI / 2);
				m_pCombo3Effect->Start();
			}
		}
	}
	else if (m_pParent->GetCurrentAnimInfo().nIndex == E_ANI_COMBO5)
	{
		if (m_pParent->GetCurrentAnimPosition() >= 0.27f && m_pParent->GetCurrentAnimPosition() <= 0.37f)
		{
			if (!StartCombo4)
			{
				m_pCombo4Effect = new cCircleEffect("Effect", "blueCircle.x");
				StartCombo4 = true;
				m_pCombo4Effect->Setup(4, 0.5f, true, D3DXVECTOR3(0.2f, 0.2f, 0.2f), D3DXVECTOR3(m_pParent->GetPosition().x,
					m_pParent->GetPosition().y + 1,
					m_pParent->GetPosition().z), m_pParent->GetAngle() + D3DX_PI / 2);
				m_pCombo4Effect->Start();
			}
		}
	}



	if (StartCombo1)
	{
		m_pCombo1Effect->SetPosition(D3DXVECTOR3(m_pParent->GetPosition().x,
			m_pParent->GetPosition().y + 1,
			m_pParent->GetPosition().z));
		m_pCombo1Effect->Update();
		m_pCombo1Effect->Render();
		if (!m_pCombo1Effect->isStart())
		{
			StartCombo1 = false;
			SAFE_RELEASE(m_pCombo1Effect);
		}
	}
	else if (StartCombo2)
	{
		m_pCombo2Effect->SetPosition(D3DXVECTOR3(m_pParent->GetPosition().x,
			m_pParent->GetPosition().y + 1,
			m_pParent->GetPosition().z));
		m_pCombo2Effect->Update();
		m_pCombo2Effect->Render();
		if (!m_pCombo2Effect->isStart())
		{
			StartCombo2 = false;
			SAFE_RELEASE(m_pCombo2Effect);
		}
	}
	else if (StartCombo3)
	{
		m_pCombo3Effect->SetPosition(D3DXVECTOR3(m_pParent->GetPosition().x,
			m_pParent->GetPosition().y + 1,
			m_pParent->GetPosition().z));
		m_pCombo3Effect->Update();
		m_pCombo3Effect->Render();
		if (!m_pCombo3Effect->isStart())
		{
			StartCombo3 = false;
			SAFE_RELEASE(m_pCombo3Effect);
		}
	}
	else if (StartCombo4)
	{
		m_pCombo4Effect->SetPosition(D3DXVECTOR3(m_pParent->GetPosition().x,
			m_pParent->GetPosition().y + 1,
			m_pParent->GetPosition().z));
		m_pCombo4Effect->Update();
		m_pCombo4Effect->Render();
		if (!m_pCombo4Effect->isStart())
		{
			StartCombo4 = false;
			SAFE_RELEASE(m_pCombo4Effect);
		}
	}
}

	
void cStateCombo::End()
{
	m_pParent->AnimationRemove();
	((cPlayer*)m_pParent)->ChangeState(E_STATE_WAIT);
}


void cStateCombo::OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo)
{
	if (m_bNextAttack)
	{
		if (animInfo.nIndex == E_ANI_COMBO1 ||
			animInfo.nIndex == E_ANI_COMBO2 ||
			animInfo.nIndex == E_ANI_COMBO3 ||
			animInfo.nIndex == E_ANI_COMBO4)
		{
			//if (((cPlayer*)m_pParent)->GetKeyDir() == DIRECTION_NONE)
			//	m_pParent->SetAngle(GETSINGLE(cCameraMgr)->GetCamera()->GetCamRotX());
			//else
		//	if (m_pParent->IsMoveAble())
			if (((cPlayer*)m_pParent)->GetKeyDir() == DIRECTION_NONE)
				m_pParent->SetAngle(GETSINGLE(cCameraMgr)->GetCamera()->GetCamRotX());
			else
				m_pParent->SetAngle(GETSINGLE(cCameraMgr)->GetCamera()->GetCamRotX() + ((cPlayer*)m_pParent)->GetTempAngle());
			pController->AnimationNext();
			m_bNextAttack = false;
		}
	}
	else
	{
		if (animInfo.nIndex == E_ANI_COMBO1R ||
			animInfo.nIndex == E_ANI_COMBO2R ||
			animInfo.nIndex == E_ANI_COMBO3R ||
			animInfo.nIndex == E_ANI_COMBO4R)
		{
			if (m_bNextAttack)
			{
				pController->AnimationNext();
				m_bNextAttack = false;
			}
			else
				End();
		}
		else
		{
			m_pParent->AnimationRemove();
			ST_ANIMATION_INFO aniInfo;
			switch (animInfo.nIndex)
			{
			case E_ANI_COMBO1:
				aniInfo.SetInfo(E_ANI_COMBO1R, true, true);
				break;
			case E_ANI_COMBO2:
				aniInfo.SetInfo(E_ANI_COMBO2R, true, true);
				break;
			case E_ANI_COMBO3:
				aniInfo.SetInfo(E_ANI_COMBO3R, true, true);
				break;
			case E_ANI_COMBO4:
				aniInfo.SetInfo(E_ANI_COMBO4R, true, true);
				break;
			}
			m_pParent->AddAnimation(aniInfo);
			pController->AnimationNext();
		}
	}
	
	if (animInfo.nIndex == E_ANI_COMBO5)
		End();
}

