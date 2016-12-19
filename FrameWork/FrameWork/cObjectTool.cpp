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
	m_BodyStuff = GETSINGLE(cObjMgr)->GetStuffList("³ª¹«");
}
void cObjectTool::Update()
{

	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPosition();
	playerPos.z += 2.0f;
	m_BodyStuff->SetPosition(playerPos);
	

}	