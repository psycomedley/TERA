#include "stdafx.h"
#include "cObjectTool.h"
#include "cPlayer.h"

cObjectTool::cObjectTool()
{
}


cObjectTool::~cObjectTool()
{
	
}
void cObjectTool::Setup()
{
	m_BodyStuff = GETSINGLE(cObjMgr)->GetStuffList("나무");
}
void cObjectTool::Update()
{

	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPosition();
	playerPos.z += 2.0f;
	m_BodyStuff->SetPosition(playerPos);
	
	ChangeBodyStuff();
}
void cObjectTool::ChangeBodyStuff()
{
	if (KEYBOARD->IsOnceKeyDown(DIK_1))
	{
		m_BodyStuff = GETSINGLE(cObjMgr)->GetStuffList("바리게이트_1");
	}
}