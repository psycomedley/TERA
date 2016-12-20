#include "stdafx.h"
#include "cObjectTool.h"
#include "cPlayer.h"
#include "cStuff.h"

cObjectTool::cObjectTool()
	:m_RotDirection(0)
{
}


cObjectTool::~cObjectTool()
{
	
}
void cObjectTool::Setup()
{
	m_BodyStuff = GETSINGLE(cObjMgr)->GetStuffList("나무");
	m_vScaling = m_BodyStuff->GetScale();
	ResetVariable();

}
void cObjectTool::Update()
{

	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPosition();
	playerPos.z += 2.0f;
	m_BodyStuff->SetPosition(playerPos);
	
	ChangeBodyStuff();
	ChangeScaleAndAngle();
	AddClone();
}
void cObjectTool::Render()
{
	m_BodyStuff->Render(); // 바디 오브젝트만 렌더
}
void cObjectTool::ResetVariable()
{
	m_fRx, m_fRy, m_fRz = 0;
	m_vScaling = m_BodyStuff->GetScale();
}
void cObjectTool::ChangeBodyStuff()
{
	if (KEYBOARD->IsOnceKeyDown(DIK_1))
	{
		m_BodyStuff = GETSINGLE(cObjMgr)->GetStuffList("바리게이트_1");
		ResetVariable(); // 스케일, 회전 변수 다 0으로 초기화
	}

}
void cObjectTool::ChangeScaleAndAngle()
{
	// 회전할 축 선택
	if (KEYBOARD->IsOnceKeyDown(DIK_NUMPAD1))
	{
		m_RotDirection = 1; //x축
	}
	if (KEYBOARD->IsOnceKeyDown(DIK_NUMPAD2))
	{
		m_RotDirection = 2; //y축
	}
	if (KEYBOARD->IsOnceKeyDown(DIK_NUMPAD3))
	{
		m_RotDirection = 3; // z축
	}

	// 스케일
	if (KEYBOARD->IsStayKeyDown(DIK_UP))
	{
		m_vScaling.x += 0.001f; m_vScaling.y += 0.001f; m_vScaling.z += 0.001f;
		m_BodyStuff->SetScale(m_vScaling);
	}
	if (KEYBOARD->IsStayKeyDown(DIK_DOWN))
	{
		m_vScaling.x -= 0.001f; m_vScaling.y -= 0.001f; m_vScaling.z -= 0.001f;
		m_BodyStuff->SetScale(m_vScaling);
	}

	//회전
	switch (m_RotDirection)
	{
	case 1:
		if (KEYBOARD->IsStayKeyDown(DIK_RIGHT))
		{
			m_fRx += 0.03f;
			m_BodyStuff->SetfRotX(m_fRx);
		}
		if (KEYBOARD->IsStayKeyDown(DIK_LEFT))
		{
			m_fRx -= 0.03f;
			m_BodyStuff->SetfRotX(m_fRx);
		}
		break;
	case 2:
		if (KEYBOARD->IsStayKeyDown(DIK_RIGHT))
		{
			m_fRy += 0.03f;
			m_BodyStuff->SetfRotY(m_fRy);
		}
		if (KEYBOARD->IsStayKeyDown(DIK_LEFT))
		{
			m_fRy -= 0.03f;
			m_BodyStuff->SetfRotY(m_fRy);
		}
		break;
	case 3:
		if (KEYBOARD->IsStayKeyDown(DIK_RIGHT))
		{
			m_fRz += 0.03f;
			m_BodyStuff->SetfRotZ(m_fRz);
		}
		if (KEYBOARD->IsStayKeyDown(DIK_LEFT))
		{
			m_fRz -= 0.03f;
			m_BodyStuff->SetfRotZ(m_fRz);
		}
		break;
	default:
		break;
	}
}
void cObjectTool::AddClone()
{
	if (KEYBOARD->IsOnceKeyDown(DIK_SPACE))
	{
		cStuff* pcloneStuff = new cStuff("Object", "tree1.x");
		pcloneStuff = CopyInfoToClone(m_BodyStuff, pcloneStuff);
		GETSINGLE(cObjMgr)->AddCloneStuff(pcloneStuff);
	}
	
}
cStuff* cObjectTool::CopyInfoToClone(cStaticObj* BodyStuff, cStuff* CloneStuff)
{
	cStuff* cloneStuff = CloneStuff;
	cloneStuff->SetPosition(BodyStuff->GetPosition());
	cloneStuff->SetScale(BodyStuff->GetScale());
	cloneStuff->SetfRotX(BodyStuff->GetfRotX());
	cloneStuff->SetfRotY(BodyStuff->GetfRotY());
	cloneStuff->SetfRotZ(BodyStuff->GetfRotZ());

	return cloneStuff;
}