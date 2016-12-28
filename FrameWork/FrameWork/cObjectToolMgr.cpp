#include "stdafx.h"
#include "cObjectToolMgr.h"
#include "cStuff.h"
#include "cStaticMesh.h"
#include "cStaticObj.h"
#include "cPlayer.h"


cObjectToolMgr::cObjectToolMgr()
	:m_PlayerPrevPos(10,0,100)
{
}


cObjectToolMgr::~cObjectToolMgr()
{
}
void cObjectToolMgr::Setup()
{
	//m_PlayerPrevPos = GETSINGLE(cObjMgr)->GetPlayer()->GetPosition();

	cStuff* pTree = new cStuff("Object", "tree1.x");
	pTree->SetPosition(D3DXVECTOR3(0.0f, 0.0f, 50.0f));
	pTree->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pTree->SetIsCullMode(true);
	pTree->SetSubSetNum(0);
	pTree->SetFoldername("Object");
	pTree->SetFilename("tree1.x");
	GETSINGLE(cObjMgr)->AddStuff("나무", pTree);

	cStuff* pTree2 = new cStuff("Object/나무2", "tree2.x");
	pTree2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pTree2->SetScale(D3DXVECTOR3(0.04f, 0.04f, 0.04f));
	pTree2->SetIsCullMode(true);
	pTree2->SetSubSetNum(1);
	pTree2->SetFoldername("Object/나무2");
	pTree2->SetFilename("tree2.x");
	GETSINGLE(cObjMgr)->AddStuff("나무2", pTree2);

	cStuff* pTree3 = new cStuff("Object/나무4", "tree4.x");
	pTree3->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pTree3->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pTree3->SetIsCullMode(true);
	pTree3->SetSubSetNum(1);
	pTree3->SetFoldername("Object/나무4");
	pTree3->SetFilename("tree4.x");
	GETSINGLE(cObjMgr)->AddStuff("나무4", pTree3);

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

	cStuff* pCampFire = new cStuff("Object/캠프파이어", "campFire.x");
	pCampFire->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pCampFire->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pCampFire->SetFoldername("Object/캠프파이어");
	pCampFire->SetFilename("campFire.x");
	GETSINGLE(cObjMgr)->AddStuff("캠프파이어", pCampFire);

	cStuff* pBoard = new cStuff("Object/게시판", "board.x");
	pBoard->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBoard->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBoard->SetFoldername("Object/게시판");
	pBoard->SetFilename("board.x");
	GETSINGLE(cObjMgr)->AddStuff("게시판", pBoard);

	cStuff* pBarricateSmallX = new cStuff("Object/바리게이트엑스", "barricateSmallX.x");
	pBarricateSmallX->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBarricateSmallX->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBarricateSmallX->SetFoldername("Object/바리게이트엑스");
	pBarricateSmallX->SetFilename("barricateSmallX.x");
	GETSINGLE(cObjMgr)->AddStuff("작은바리게이트엑스", pBarricateSmallX);

	cStuff* pBarricateLargeX = new cStuff("Object/바리게이트큰엑스", "barricateLargeX.x");
	pBarricateLargeX->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBarricateLargeX->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBarricateLargeX->SetFoldername("Object/바리게이트큰엑스");
	pBarricateLargeX->SetFilename("barricateLargeX.x");
	GETSINGLE(cObjMgr)->AddStuff("큰바리게이트엑스", pBarricateLargeX);

	cStuff* pCircleBarrell = new cStuff("Object/원형통", "CircleBarrell.x");
	pCircleBarrell->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pCircleBarrell->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pCircleBarrell->SetFoldername("Object/원형통");
	pCircleBarrell->SetFilename("CircleBarrell.x");
	GETSINGLE(cObjMgr)->AddStuff("원형통", pCircleBarrell);

	cStuff* pChair = new cStuff("Object/의자", "chair.x");
	pChair->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pChair->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pChair->SetFoldername("Object/의자");
	pChair->SetFilename("chair.x");
	GETSINGLE(cObjMgr)->AddStuff("의자", pChair);

	cStuff* pSmallBox = new cStuff("Object/작은상자", "SmallBox.x");
	pSmallBox->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pSmallBox->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pSmallBox->SetFoldername("Object/작은상자");
	pSmallBox->SetFilename("SmallBox.x");
	GETSINGLE(cObjMgr)->AddStuff("작은상자", pSmallBox);

	cStuff* pLargeBox = new cStuff("Object/큰상자", "LargeBox.x");
	pLargeBox->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pLargeBox->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pLargeBox->SetFoldername("Object/큰상자");
	pLargeBox->SetFilename("LargeBox.x");
	GETSINGLE(cObjMgr)->AddStuff("큰상자", pLargeBox);

	cStuff* pCart = new cStuff("Object/카트", "cart.x");
	pCart->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pCart->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pCart->SetFoldername("Object/카트");
	pCart->SetFilename("cart.x");
	GETSINGLE(cObjMgr)->AddStuff("카트", pCart);

	cStuff* pPot = new cStuff("Object/항아리", "Pot.x");
	pPot->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pPot->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pPot->SetFoldername("Object/항아리");
	pPot->SetFilename("Pot.x");
	GETSINGLE(cObjMgr)->AddStuff("항아리", pPot);

	cStuff* pBreakTree1 = new cStuff("Object/나무밑둥", "BreakTree1.x");
	pBreakTree1->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBreakTree1->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBreakTree1->SetFoldername("Object/나무밑둥");
	pBreakTree1->SetFilename("BreakTree1.x");
	GETSINGLE(cObjMgr)->AddStuff("나무밑둥", pBreakTree1);

	cStuff* pBreakTree2 = new cStuff("Object/장작", "BreakTree2.x");
	pBreakTree2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBreakTree2->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBreakTree2->SetFoldername("Object/장작");
	pBreakTree2->SetFilename("BreakTree2.x");
	GETSINGLE(cObjMgr)->AddStuff("장작", pBreakTree2);

	cStuff* pRock1 = new cStuff("Object/돌1", "Rock1.x");
	pRock1->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pRock1->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pRock1->SetFoldername("Object/돌1");
	pRock1->SetFilename("Rock1.x");
	GETSINGLE(cObjMgr)->AddStuff("돌1", pRock1);

	cStuff* pGrass1 = new cStuff("Object/풀1", "grass1.x");
	pGrass1->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pGrass1->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pGrass1->SetFoldername("Object/풀1");
	pGrass1->SetFilename("grass1.x");
	GETSINGLE(cObjMgr)->AddStuff("풀1", pGrass1);

	cStuff* pGrass2 = new cStuff("Object/풀2", "Grass2.x");
	pGrass2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pGrass2->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pGrass2->SetFoldername("Object/풀2");
	pGrass2->SetFilename("Grass2.x");
	pGrass2->SetIsCullMode(true);
	pGrass2->SetSubSetNum(0);
	GETSINGLE(cObjMgr)->AddStuff("풀2", pGrass2);

	cStuff* pGrass3 = new cStuff("Object/풀3", "Grass3.x");
	pGrass3->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pGrass3->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pGrass3->SetFoldername("Object/풀3");
	pGrass3->SetFilename("Grass3.x");
	pGrass2->SetIsCullMode(true);
	pGrass2->SetSubSetNum(1);
	GETSINGLE(cObjMgr)->AddStuff("풀3", pGrass3);

	cStuff* pHouse1 = new cStuff("Object/집1", "house1.x");
	pHouse1->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse1->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse1->SetFoldername("Object/집1");
	pHouse1->SetFilename("house1.x");
	GETSINGLE(cObjMgr)->AddStuff("집1", pHouse1);

	cStuff* pHouse2 = new cStuff("Object/집2", "house2.x");
	pHouse2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse2->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse2->SetFoldername("Object/집2");
	pHouse2->SetFilename("house2.x");
	GETSINGLE(cObjMgr)->AddStuff("집2", pHouse2);

	cStuff* pHouse3 = new cStuff("Object/집3", "house3.x");
	pHouse3->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse3->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse3->SetFoldername("Object/집3");
	pHouse3->SetFilename("house3.x");
	GETSINGLE(cObjMgr)->AddStuff("집3", pHouse3);

	cStuff* pHouse4 = new cStuff("Object/집4", "house4.x");
	pHouse4->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse4->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse4->SetFoldername("Object/집4");
	pHouse4->SetFilename("house4.x");
	GETSINGLE(cObjMgr)->AddStuff("집4", pHouse4);

	cStuff* pHouse5 = new cStuff("Object/집5", "house5.x");
	pHouse5->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse5->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse5->SetFoldername("Object/집5");
	pHouse5->SetFilename("house5.x");
	GETSINGLE(cObjMgr)->AddStuff("집5", pHouse5);

	cStuff* pGate = new cStuff("Object/문", "Gate.x");
	pGate->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pGate->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pGate->SetFoldername("Object/문");
	pGate->SetFilename("Gate.x");
	GETSINGLE(cObjMgr)->AddStuff("문", pGate);

	cStuff* pWell = new cStuff("Object/우물", "Well.x");
	pWell->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pWell->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pWell->SetFoldername("Object/우물");
	pWell->SetFilename("Well.x");
	GETSINGLE(cObjMgr)->AddStuff("우물", pWell);
}
void cObjectToolMgr::Update()
{
	//======================== 충돌 처리

	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	vector<cDynamicObj*> pVecAllMonster = GETSINGLE(cObjMgr)->GetALLMonsterList();

	vector<cStaticObj*> vecCloneStuff = *(GETSINGLE(cObjMgr)->GetAllCloneStuff());
	cBoundingBox* playerBox = &(pPlayer->GetBox());
	D3DXVECTOR3 prePosition;

	for (size_t i = 0; i < vecCloneStuff.size(); ++i)
	{
		string filename = ((cStuff*)vecCloneStuff[i])->GetFilename();
		if (i + 1 == vecCloneStuff.size())
		{
			pPlayer->SetPrevPosition(pPlayer->GetPosition());
			m_PlayerPrevPos = pPlayer->GetPosition();
		}
		if (filename == "grass1.x") 	continue;
		else if (filename == "Grass2.x") continue;
		else if (filename == "Grass3.x") continue;
		else if (filename == "Gate.x") continue;

		cBoundingBox* stuffBox = &(vecCloneStuff[i]->GetBox());
		
		// 캐릭터와 오브젝트 충돌
		
		if (GETSINGLE(cCollision)->Collision(playerBox, stuffBox))
		{
			D3DXVECTOR3 CurPos = pPlayer->GetPosition();
			D3DXVECTOR3 afterPos = pPlayer->GetPrevPosition();
			pPlayer->SetPosition(m_PlayerPrevPos);
		}
	
		

		//몬스터와 오브젝트 충돌
		/*for (size_t j = 0; j < pVecAllMonster.size(); ++j)
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
		}*/

	}
	///===============================
}
void cObjectToolMgr::Render()
{

}
void cObjectToolMgr::Release()
{
	cSingleton::Release();
}