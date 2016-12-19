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
	GETSINGLE(cObjMgr)->AddStuff("³ª¹«", pTree);
}
void cObjectToolMgr::Render()
{

}