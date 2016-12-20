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
	

	cStuff* pTree = new cStuff("Object", "tree1.x");
	pTree->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	pTree->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pTree->SetIsCullMode(true);
	pTree->SetSubSetNum(0);
	pTree->SetFoldername("Object");
	pTree->SetFilename("tree1.x");
	GETSINGLE(cObjMgr)->AddStuff("����", pTree);

	cStuff* pBarricate = new cStuff("Object/�ٸ�����Ʈ", "barricate1.x");
	pBarricate->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 40.0f));
	pBarricate->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBarricate->SetFoldername("Object/�ٸ�����Ʈ");
	pBarricate->SetFilename("barricate1.x");
	GETSINGLE(cObjMgr)->AddStuff("�ٸ�����Ʈ_1", pBarricate);

	cStuff* pBarricatePole = new cStuff("Object/�ٸ�����Ʈ_���", "barricatePole.x");
	pBarricatePole->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBarricatePole->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBarricatePole->SetFoldername("Object/�ٸ�����Ʈ_���");
	pBarricatePole->SetFilename("barricatePole.x");
	GETSINGLE(cObjMgr)->AddStuff("�ٸ�����Ʈ_���", pBarricatePole);

}
void cObjectToolMgr::Update()
{
}
void cObjectToolMgr::Render()
{

}