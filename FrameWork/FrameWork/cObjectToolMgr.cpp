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
	GETSINGLE(cObjMgr)->AddStuff("����", pTree);

	cStuff* pTree2 = new cStuff("Object/����2", "tree2.x");
	pTree2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pTree2->SetScale(D3DXVECTOR3(0.04f, 0.04f, 0.04f));
	pTree2->SetIsCullMode(true);
	pTree2->SetSubSetNum(1);
	pTree2->SetFoldername("Object/����2");
	pTree2->SetFilename("tree2.x");
	GETSINGLE(cObjMgr)->AddStuff("����2", pTree2);

	cStuff* pTree3 = new cStuff("Object/����4", "tree4.x");
	pTree3->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pTree3->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pTree3->SetIsCullMode(true);
	pTree3->SetSubSetNum(1);
	pTree3->SetFoldername("Object/����4");
	pTree3->SetFilename("tree4.x");
	GETSINGLE(cObjMgr)->AddStuff("����4", pTree3);

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

	cStuff* pCampFire = new cStuff("Object/ķ�����̾�", "campFire.x");
	pCampFire->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pCampFire->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pCampFire->SetFoldername("Object/ķ�����̾�");
	pCampFire->SetFilename("campFire.x");
	GETSINGLE(cObjMgr)->AddStuff("ķ�����̾�", pCampFire);

	cStuff* pBoard = new cStuff("Object/�Խ���", "board.x");
	pBoard->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBoard->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBoard->SetFoldername("Object/�Խ���");
	pBoard->SetFilename("board.x");
	GETSINGLE(cObjMgr)->AddStuff("�Խ���", pBoard);

	cStuff* pBarricateSmallX = new cStuff("Object/�ٸ�����Ʈ����", "barricateSmallX.x");
	pBarricateSmallX->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBarricateSmallX->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBarricateSmallX->SetFoldername("Object/�ٸ�����Ʈ����");
	pBarricateSmallX->SetFilename("barricateSmallX.x");
	GETSINGLE(cObjMgr)->AddStuff("�����ٸ�����Ʈ����", pBarricateSmallX);

	cStuff* pBarricateLargeX = new cStuff("Object/�ٸ�����Ʈū����", "barricateLargeX.x");
	pBarricateLargeX->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBarricateLargeX->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBarricateLargeX->SetFoldername("Object/�ٸ�����Ʈū����");
	pBarricateLargeX->SetFilename("barricateLargeX.x");
	GETSINGLE(cObjMgr)->AddStuff("ū�ٸ�����Ʈ����", pBarricateLargeX);

	cStuff* pCircleBarrell = new cStuff("Object/������", "CircleBarrell.x");
	pCircleBarrell->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pCircleBarrell->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pCircleBarrell->SetFoldername("Object/������");
	pCircleBarrell->SetFilename("CircleBarrell.x");
	GETSINGLE(cObjMgr)->AddStuff("������", pCircleBarrell);

	cStuff* pChair = new cStuff("Object/����", "chair.x");
	pChair->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pChair->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pChair->SetFoldername("Object/����");
	pChair->SetFilename("chair.x");
	GETSINGLE(cObjMgr)->AddStuff("����", pChair);

	cStuff* pSmallBox = new cStuff("Object/��������", "SmallBox.x");
	pSmallBox->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pSmallBox->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pSmallBox->SetFoldername("Object/��������");
	pSmallBox->SetFilename("SmallBox.x");
	GETSINGLE(cObjMgr)->AddStuff("��������", pSmallBox);

	cStuff* pLargeBox = new cStuff("Object/ū����", "LargeBox.x");
	pLargeBox->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pLargeBox->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pLargeBox->SetFoldername("Object/ū����");
	pLargeBox->SetFilename("LargeBox.x");
	GETSINGLE(cObjMgr)->AddStuff("ū����", pLargeBox);

	cStuff* pCart = new cStuff("Object/īƮ", "cart.x");
	pCart->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pCart->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pCart->SetFoldername("Object/īƮ");
	pCart->SetFilename("cart.x");
	GETSINGLE(cObjMgr)->AddStuff("īƮ", pCart);

	cStuff* pPot = new cStuff("Object/�׾Ƹ�", "Pot.x");
	pPot->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pPot->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pPot->SetFoldername("Object/�׾Ƹ�");
	pPot->SetFilename("Pot.x");
	GETSINGLE(cObjMgr)->AddStuff("�׾Ƹ�", pPot);

	cStuff* pBreakTree1 = new cStuff("Object/�����ص�", "BreakTree1.x");
	pBreakTree1->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBreakTree1->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBreakTree1->SetFoldername("Object/�����ص�");
	pBreakTree1->SetFilename("BreakTree1.x");
	GETSINGLE(cObjMgr)->AddStuff("�����ص�", pBreakTree1);

	cStuff* pBreakTree2 = new cStuff("Object/����", "BreakTree2.x");
	pBreakTree2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pBreakTree2->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pBreakTree2->SetFoldername("Object/����");
	pBreakTree2->SetFilename("BreakTree2.x");
	GETSINGLE(cObjMgr)->AddStuff("����", pBreakTree2);

	cStuff* pRock1 = new cStuff("Object/��1", "Rock1.x");
	pRock1->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pRock1->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pRock1->SetFoldername("Object/��1");
	pRock1->SetFilename("Rock1.x");
	GETSINGLE(cObjMgr)->AddStuff("��1", pRock1);

	cStuff* pGrass1 = new cStuff("Object/Ǯ1", "grass1.x");
	pGrass1->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pGrass1->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pGrass1->SetFoldername("Object/Ǯ1");
	pGrass1->SetFilename("grass1.x");
	GETSINGLE(cObjMgr)->AddStuff("Ǯ1", pGrass1);

	cStuff* pGrass2 = new cStuff("Object/Ǯ2", "Grass2.x");
	pGrass2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pGrass2->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pGrass2->SetFoldername("Object/Ǯ2");
	pGrass2->SetFilename("Grass2.x");
	pGrass2->SetIsCullMode(true);
	pGrass2->SetSubSetNum(0);
	GETSINGLE(cObjMgr)->AddStuff("Ǯ2", pGrass2);

	cStuff* pGrass3 = new cStuff("Object/Ǯ3", "Grass3.x");
	pGrass3->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pGrass3->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pGrass3->SetFoldername("Object/Ǯ3");
	pGrass3->SetFilename("Grass3.x");
	pGrass2->SetIsCullMode(true);
	pGrass2->SetSubSetNum(1);
	GETSINGLE(cObjMgr)->AddStuff("Ǯ3", pGrass3);

	cStuff* pHouse1 = new cStuff("Object/��1", "house1.x");
	pHouse1->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse1->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse1->SetFoldername("Object/��1");
	pHouse1->SetFilename("house1.x");
	GETSINGLE(cObjMgr)->AddStuff("��1", pHouse1);

	cStuff* pHouse2 = new cStuff("Object/��2", "house2.x");
	pHouse2->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse2->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse2->SetFoldername("Object/��2");
	pHouse2->SetFilename("house2.x");
	GETSINGLE(cObjMgr)->AddStuff("��2", pHouse2);

	cStuff* pHouse3 = new cStuff("Object/��3", "house3.x");
	pHouse3->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse3->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse3->SetFoldername("Object/��3");
	pHouse3->SetFilename("house3.x");
	GETSINGLE(cObjMgr)->AddStuff("��3", pHouse3);

	cStuff* pHouse4 = new cStuff("Object/��4", "house4.x");
	pHouse4->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse4->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse4->SetFoldername("Object/��4");
	pHouse4->SetFilename("house4.x");
	GETSINGLE(cObjMgr)->AddStuff("��4", pHouse4);

	cStuff* pHouse5 = new cStuff("Object/��5", "house5.x");
	pHouse5->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pHouse5->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pHouse5->SetFoldername("Object/��5");
	pHouse5->SetFilename("house5.x");
	GETSINGLE(cObjMgr)->AddStuff("��5", pHouse5);

	cStuff* pGate = new cStuff("Object/��", "Gate.x");
	pGate->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pGate->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pGate->SetFoldername("Object/��");
	pGate->SetFilename("Gate.x");
	GETSINGLE(cObjMgr)->AddStuff("��", pGate);

	cStuff* pWell = new cStuff("Object/�칰", "Well.x");
	pWell->SetPosition(D3DXVECTOR3(5.0f, 0.0f, 40.0f));
	pWell->SetScale(D3DXVECTOR3(0.07f, 0.07f, 0.07f));
	pWell->SetFoldername("Object/�칰");
	pWell->SetFilename("Well.x");
	GETSINGLE(cObjMgr)->AddStuff("�칰", pWell);
}
void cObjectToolMgr::Update()
{
	//======================== �浹 ó��

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
		
		// ĳ���Ϳ� ������Ʈ �浹
		
		if (GETSINGLE(cCollision)->Collision(playerBox, stuffBox))
		{
			D3DXVECTOR3 CurPos = pPlayer->GetPosition();
			D3DXVECTOR3 afterPos = pPlayer->GetPrevPosition();
			pPlayer->SetPosition(m_PlayerPrevPos);
		}
	
		

		//���Ϳ� ������Ʈ �浹
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