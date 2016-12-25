#include "stdafx.h"
#include "cObjectToolMgr.h"
#include "cStuff.h"
#include "cStaticMesh.h"
#include "cStaticObj.h"
#include "cPlayer.h"


cObjectToolMgr::cObjectToolMgr()
	: m_PrevPlayerPos(0,0,0)
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
	GETSINGLE(cObjMgr)->AddStuff("나무", pTree);

	cStuff* pBarricate = new cStuff("Object/바리게이트", "barricate1.x");
	pBarricate->SetPosition(D3DXVECTOR3(10.0f, 0.0f, 40.0f));
	pBarricate->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBarricate->SetFoldername("Object/바리게이트");
	pBarricate->SetFilename("barricate1.x");
	GETSINGLE(cObjMgr)->AddStuff("바리게이트_1", pBarricate);

	cStuff* pBarricatePole = new cStuff("Object/바리게이트_기둥", "barricatePole.x");
	pBarricatePole->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBarricatePole->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBarricatePole->SetFoldername("Object/바리게이트_기둥");
	pBarricatePole->SetFilename("barricatePole.x");
	GETSINGLE(cObjMgr)->AddStuff("바리게이트_기둥", pBarricatePole);

}
void cObjectToolMgr::Update()
{
	//======================== 충돌 처리

	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	vector<cDynamicObj*> pVecAllMonster = GETSINGLE(cObjMgr)->GetALLMonsterList();

	vector<cStaticObj*> vecCloneStuff = *(GETSINGLE(cObjMgr)->GetAllCloneStuff());
	cBoundingBox* playerBox = &(pPlayer->GetBox());

	for (size_t i = 0; i < vecCloneStuff.size(); ++i)
	{
	
		cBoundingBox* stuffBox = &(vecCloneStuff[i]->GetBox());
		// 캐릭터와 오브젝트 충돌
		if (GETSINGLE(cCollision)->Collision(playerBox, stuffBox))
		{
			D3DXVECTOR3 CurPos = pPlayer->GetPosition();
			D3DXVECTOR3 afterPos = pPlayer->GetPrevPosition();
			pPlayer->SetPosition(pPlayer->GetPrevPosition());
		}
		if (i + 1 == vecCloneStuff.size())
		{
			pPlayer->SetPrevPosition(pPlayer->GetPosition());
		}

		//몬스터와 오브젝트 충돌
		for (size_t j = 0; j < pVecAllMonster.size(); ++j)
		{
			if (pVecAllMonster[j]->GetInfo().sName == "Globe") continue;
			cBoundingBox* MosterBox = &(pVecAllMonster[j]->GetBox());

			if (GETSINGLE(cCollision)->Collision(MosterBox, stuffBox))
			{
				pVecAllMonster[j]->SetPosition(pVecAllMonster[j]->GetPrevPosition());
			}
	
			if (i + 1 == vecCloneStuff.size())
			{
				pVecAllMonster[j]->SetPrevPosition(pVecAllMonster[j]->GetPosition());
			}
		}

	}
	///===============================
}
void cObjectToolMgr::Render()
{

}