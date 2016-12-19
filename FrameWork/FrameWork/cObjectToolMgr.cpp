#include "stdafx.h"
#include "cObjectToolMgr.h"
#include "cStuff.h"
#include "cStaticMesh.h"
#include "cStaticObj.h"


cObjectToolMgr::cObjectToolMgr()
{
}


cObjectToolMgr::~cObjectToolMgr()
{
}
void cObjectToolMgr::Setup()
{
	

	cStaticObj* pTree = new cStuff("Object", "tree1.x");
	pTree->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	pTree->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	//pTree->SetIsCullMode(true);
	//pTree->SetSubSetNum(0);
	GETSINGLE(cObjMgr)->AddStuff("나무", pTree);

	cStuff* pBarricate = new cStuff("Object/바리게이트", "barricate1.x");
	pBarricate->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 20.0f));
	pBarricate->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	GETSINGLE(cObjMgr)->AddStuff("바리게이트_1", pBarricate);

	cStuff* pBarricatePole = new cStuff("Object/바리게이트_기둥", "barricatePole.x");
	pBarricatePole->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 20.0f));
	pBarricatePole->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	GETSINGLE(cObjMgr)->AddStuff("바리게이트_기둥", pBarricatePole);

}
void cObjectToolMgr::Update()
{
}
void cObjectToolMgr::Render()
{

}