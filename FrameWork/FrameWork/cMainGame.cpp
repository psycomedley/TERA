#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cStaticMesh.h"
#include "cDynamicMesh.h"
#include "cCube.h"
#include "cRay.h"
#include "cPlayer.h"
#include "cMap.h"
#include "cOrca.h"
#include "cGrid.h"
#include "cEffect.h"
#include "cStaticMeshEffect.h"
#include "cDynamicMeshEffect.h"
#include "cCircleEffect.h"
#include "cRushEffect.h"
#include "cUIImageView.h"
#include "cUITextView.h"
#include "cStuff.h"

//임시


cMainGame::cMainGame()
	: m_bLockMouse(true)
	, m_cObjectTree(NULL)
	, m_pEffect3(NULL)
{
}


cMainGame::~cMainGame()
{
	///////////////임시////////////////
	SAFE_DELETE(m_pGrid);

	SAFE_DELETE(m_pEffect);
	SAFE_DELETE(m_pEffect2);
<<<<<<< HEAD
	SAFE_RELEASE(m_pDynamicMeshEffect);
=======
	SAFE_DELETE(m_pEffect3);
	

>>>>>>> 3559cb776a48bde22a42c86a47aaad83acc43564
	SAFE_RELEASE(m_pCircleEffect);
	SAFE_RELEASE(m_pRushEffect);

	///////////////////////////////////

	SAFE_RELEASE(m_pMap);
	SAFE_RELEASE(m_cObjectTree);
	Release();

//	SAFE_RELEASE(m_pPlayer);
//	SAFE_RELEASE(m_pBoss);
}


HRESULT cMainGame::Setup()
{
	ShowCursor(false);
	/*POINT pWinPos;
	pWinPos.x = GetWindowWidth() / 2;
	pWinPos.y = GetWindowHeight() / 2;
	ClientToScreen(g_hWnd, &pWinPos);

	SetCursorPos(pWinPos.x, pWinPos.y);*/

	if (FAILED(GETSINGLE(cDevice)->Setup()))
	{
		MSGBOX("Device Setup Fail");
		return E_FAIL;
	}

	if (FAILED(GETSINGLE(cTimeMgr)->Setup()))
	{
		MSGBOX("TimeMgr Setup Fail");
		return E_FAIL;
	}

	SetShader();

	cDynamicObj* pPlayer = new cPlayer("Popori", "Popori.X");
	pPlayer->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DX_PI / 2);
	pPlayer->SetRevision(matR);
	pPlayer->SetRevisionAngle(D3DX_PI / 2);
	pPlayer->SetPosition(D3DXVECTOR3(20, 0, 0));
	GETSINGLE(cObjMgr)->SetPlayer(pPlayer);

	cDynamicObj* pBoss = new cOrca("Monster", "Orca.X");
	pBoss->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pBoss->SetRevision(matR);
	pBoss->SetRevisionAngle(D3DX_PI / 2);
	GETSINGLE(cObjMgr)->AddMonster(((cOrca*)pBoss)->GetInfo().sName, pBoss);

	/*cDynamicObj* m_pBoss2 = new cOrca("Monster", "Orca.X");
	m_pBoss2->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	m_pBoss2->SetRevision(matR);
	m_pBoss2->SetPosition(D3DXVECTOR3(10, 0, 0));
	GETSINGLE(cObjMgr)->AddMonster(((cOrca*)m_pBoss2)->GetInfo().sName, m_pBoss2);*/

	GETSINGLE(cCameraMgr)->Setup();
	GETSINGLE(cCameraMgr)->GetCamera()->SetVecTarget(&GETSINGLE(cObjMgr)->GetPlayer()->GetCameraFocus());

	m_pMap = new cMap("Map","fieldmap1.x");
	

	///////////////임시////////////////

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	/*m_pBoss2 = new cMonster("Monster", "Orca.X");
	m_pBoss2->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	m_pBoss2->SetRevision(matR);
	m_pBoss2->SetPosition(D3DXVECTOR3(10, 0, 0));*/

	m_pEffect = new cEffect;
//	m_pEffect->Setup("Effect/G_MagicArray002_Tex.tga", 20, 20, 1, 1, 0.01f, true);
	m_pEffect->Setup(20, 20, 1, EFFECT_ALPHABLEND);
	m_pEffect->SetTexture("Effect/G_MagicArray002_Tex.tga", E_TEXTURE1);
	m_pEffect->SetPosition(D3DXVECTOR3(0, 0, 0));
	m_pEffect->SetTechnique(E_TECH_BLUE);
	m_pEffect->SetAngle(D3DX_PI / 2);

	m_pEffect2 = new cEffect;
//	m_pEffect2->Setup("Effect/fire.tga", 10, 10, 4, 4, 0.01f , false, 1);
	//m_pEffect2->Setup(20, 20);
	//m_pEffect2->SetTexture("Effect/A_Gr001_emis.tga", E_TEXTURE1);
	//m_pEffect2->SetTexture("Effect/A_Gra001_emis.tga", E_TEXTURE2);
	//m_pEffect2->SetTexture("Effect/A_NorGr001_emis.tga", E_BUMPMAP);
	//m_pEffect2->SetPosition(D3DXVECTOR3(10, 10, 10));
	//m_pEffect2->SetTechnique(E_TECH_WAVE);

	/*m_pEffect2->Setup(5, 5, 1, EFFECT_ALPHABLEND | EFFECT_BILLBOARING);
	m_pEffect2->SetTexture("Effect/attack2.tga", E_TEXTURE1);
	m_pEffect2->SetPosition(D3DXVECTOR3(20, 5, 10));
	m_pEffect2->SetTechnique(E_TECH_FRAMEADD);
	m_pEffect2->SetTotalFrame(4, 4, 16);*/

	m_pEffect2->Setup(10, 10, 1, EFFECT_ALPHABLEND | EFFECT_BILLBOARING | EFFECT_CUTTEDFRAME);
	m_pEffect2->SetTexture("Effect/Lens00_emis.tga", E_TEXTURE1);
	m_pEffect2->SetTexture("Effect/Lens04_emis.tga", E_TEXTURE2);
	m_pEffect2->SetTexture("Effect/A_Lightning001_emis.tga", E_TEXTURE3);
	m_pEffect2->SetTexture("Effect/bumpnoisesemi64.tga", E_BUMPMAP);
	m_pEffect2->SetTotalFrame(4, 4, 16);
	m_pEffect2->SetPosition(D3DXVECTOR3(20, 5, 10));
	m_pEffect2->SetTechnique(E_TECH_Orca1);
	m_pEffect2->SetLoop(true);

	/*m_pEffect3 = new cEffect;
	m_pEffect3->Setup(10, 10);
	m_pEffect3->SetTexture("Effect/Lens04_emis.tga", E_TEXTURE1);
	m_pEffect3->SetPosition(D3DXVECTOR3(20, 5, 10));
	m_pEffect3->SetTechnique(E_TECH_BLUE);*/



	//임시 세팅 (비정상 동작중)
	//m_pDynamicMeshEffect = new cDynamicMeshEffect("Effect", "Circle.X");
	//m_pDynamicMeshEffect->SetPosition(D3DXVECTOR3(30, 0, 0));
	//m_pDynamicMeshEffect->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));

	m_cObjectTree = new cStuff("Object/나뭇잎","Leaf1.x");
	
	m_pCircleEffect = new cCircleEffect("Effect", "blueCircle.x");



	//m_pCircleEffect->SetScale(D3DXVECTOR3(0.0000001f, 0.0000001f, 0.0000001f));
	m_pCircleEffect->Setup(60, 0.2f, true, D3DXVECTOR3(0.2f,0.2f,0.2f),D3DXVECTOR3(20,1.5f,0));

	m_pRushEffect = new cRushEffect("Effect", "RushEffect.x");
	m_pRushEffect->Setup(16, 0.3f, true, D3DXVECTOR3(0.05f, 0.05f, 0.05f), D3DXVECTOR3(25, 1.5f, 0));



	SetLighting();

//	GETSINGLE(cTextMgr)->AddAlphaText(E_FONT_BOSS, "그아아앗", 3, D3DXVECTOR2(GetWindowWidth() / 2, 150), ST_SIZE(500, 50), XWHITE, 128, 1);

	SetUI();

	///////////////////////////////////

	return S_OK;
}


void cMainGame::Update()
{
	if (IsActive())
	{
		if (KEYBOARD->IsOnceKeyDown(DIK_SCROLL))
			m_bLockMouse = !m_bLockMouse;

		GETSINGLE(cInput)->Update();

		if (m_bLockMouse)
			LockMouse();
		/*D3DXVECTOR3 playerPos = m_pPlayer->GetPosition();*/


		GETSINGLE(cCameraMgr)->Update();

		GETSINGLE(cTextMgr)->Update();

		GETSINGLE(cUIMgr)->Update();
	}



	///////////////임시////////////////

	if (IsActive())
	{
		if (KEYBOARD->IsOnceKeyDown(DIK_E))
		{
			if (m_pEffect->GetProcess())
				m_pEffect->Stop();
			else
				m_pEffect->Start();
		}
		if (KEYBOARD->IsOnceKeyDown(DIK_R))
		{
			if (m_pEffect2->GetProcess())
			{
				m_pEffect2->Stop();
		//		m_pEffect3->Stop();
			}
			else
			{
				m_pEffect2->Start();
			//	m_pEffect3->Start();
			}
		}

//		if (KEYBOARD->IsOnceKeyDown(DIK_R))
//			m_pEffect2->Start();
		if (KEYBOARD->IsOnceKeyDown(DIK_Q))
		{
			//m_pDynamicMeshEffect->Start();
			//m_pCircleEffect->Start();
			m_pRushEffect->Start();
		}
		if (KEYBOARD->IsOnceKeyDown(DIK_T))
		{
			auto orca = GETSINGLE(cObjMgr)->GetMonsterList("Orca")->begin();
			((cOrca*)*orca)->SetHp(((cOrca*)*orca)->GetInfo().fHp - 5);
		}
		//	char szStr[16] = { '\0', };
		//	sprintf_s(szStr, sizeof(szStr), "%.0f%%", ((cOrca*)*orca)->GetInfo().fHp / (float)((cOrca*)*orca)->GetInfo().fMaxHp * 100);
		//	((cUITextView*)m_pUIBossHp->FindChildByTag(2))->SetText(szStr);
		//	((cUIImageView*)m_pUIBossHp->FindChildByTag(1))->SetScaleX(((cOrca*)*orca)->GetInfo().fHp / (float)((cOrca*)*orca)->GetInfo().fMaxHp);
		//}
	}


	CHAR str[16];
	wsprintf(str, TEXT("FPS : %d"), GETSINGLE(cTimeMgr)->getFrameRate());
	SetWindowText(g_hWnd, str);


	/*if (KEYBOARD->IsStayKeyDown(DIK_I))
	{
		m_pBoss->SetPosition(m_pBoss->GetPosition() - m_pBoss->GetDirection() * 0.1);
	}*/

	/*if (m_pBoss)
		m_pBoss->Update();*/
//	if(MOUSE->IsOnceKeyDown(MOUSEBTN_LEFT))
//m_pDynamicMeshEffect->Setup();

	if (m_pEffect)
		m_pEffect->Update();
	if (m_pEffect2)
		m_pEffect2->Update();
	if (m_pEffect3)
		m_pEffect3->Update();
	if (m_pCircleEffect)
	{
		m_pCircleEffect->Update();
	}
	if (m_pRushEffect)
	{
		m_pRushEffect->Update();
	}

	m_pMap->Update();
	///////////////////////////////////

	GETSINGLE(cInput)->EndFrame();
}


void cMainGame::Render()
{
	GETSINGLE(cDevice)->BeginRender();

	POINT pos = MOUSE->GetWindowPos();
//	POINT pos;
//	GetCursorPos(&pos);
	char msg[128];

	POINT ptPosition;
	GetCursorPos(&ptPosition);
	
	OutputInteger(msg, "x", ptPosition.x);
	OutputInteger(msg, "y", ptPosition.y);

//	if (MOUSE->IsOnceKeyDown(MOUSEBTN_LEFT))
//	{
//		POINT p = MOUSE->GetWindowPos();
//
//		cRay r;
//		r = cRay::CalcWorldSpace(p);
//
//		cBoundingSphere sphere = m_pBoss->GetSphere();
//		cBoundingSphere sphere2 = m_pBoss2->GetSphere();
//		r = r.WorldToLocal(sphere.GetCenter());
//
//		cRay r2;
//		r2 = cRay::CalcWorldSpace(p);
//		r2 = r2.WorldToLocal(sphere2.GetCenter());
//
//		//	bool pick = r.IsPick(sphere);
//		if (GETSINGLE(cCollision)->Collision(&sphere, &r))
//		{
//			static int c = 2;
//			m_pPlayer->SetAnimationIdxBlend(++c % 5);
//		}
//		if (GETSINGLE(cCollision)->Collision(&sphere2, &r2))
//		{
//			static int c = 2;
//			m_pPlayer->SetAnimationIdxBlend(++c % 5);
//		}
////		if (GETSINGLE())
//	}

	GETSINGLE(cObjMgr)->Render();

	GETSINGLE(cTextMgr)->Render();

	GETSINGLE(cUIMgr)->Render();

	if (m_pMap)
		m_pMap->Render();

	///////////////임시////////////////
	
	m_pGrid->Render();



	/*if (m_pPlayer)
	m_pPlayer->UpdateAndRender();*/
	//	m_pPlayer->Bounding_Render();

	//if (m_pBoss)
	//{
	//	m_pBoss->UpdateAndRender();
//	//	m_pBoss->Bounding_Render();
	//}

	if (m_pCircleEffect)
	{
		m_pCircleEffect->Render();
	}
	if (m_pRushEffect)
	{
		m_pRushEffect->Render();
	}
	//if (m_pDynamicMeshEffect)
	//{
	//	m_pDynamicMeshEffect->Render();
	//}




	if (m_pEffect)
		m_pEffect->Render();
	if (m_pEffect2)
		m_pEffect2->Render();
	if (m_pEffect3)
		m_pEffect3->Render();





	
	if (m_cObjectTree)
		m_cObjectTree->Render();
	

	///////////////////////////////////

	GETSINGLE(cDevice)->EndRender();
}


void cMainGame::Release()
{
	SAFE_DELETE(cube);

	GETSINGLE(cTextureMgr)->Release();
	GETSINGLE(cTimeMgr)->Release();
	GETSINGLE(cInput)->Release();
	GETSINGLE(cMeshMgr)->Release();
	GETSINGLE(cCollision)->Release();
	GETSINGLE(cObjMgr)->Release();
	GETSINGLE(cObjectMgr)->Release();
	GETSINGLE(cShaderMgr)->Release();
	GETSINGLE(cFontMgr)->Release();
	GETSINGLE(cTextMgr)->Release();
	GETSINGLE(cCameraMgr)->Release();
	GETSINGLE(cUIMgr)->Release();
	GETSINGLE(cShaderMgr)->Release();

	GETSINGLE(cDevice)->Release();
}

//임시
void cMainGame::SetLighting()
{
	D3DLIGHT9 stLight;
	ZeroMemory(&stLight, sizeof(D3DLIGHT9));
	stLight.Ambient = stLight.Diffuse = stLight.Specular = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	D3DXVECTOR3 vDir(1, -1, 1);
	D3DXVec3Normalize(&vDir, &vDir);
	stLight.Direction = vDir;
	stLight.Type = D3DLIGHT_DIRECTIONAL;

	g_pD3DDevice->SetLight(0, &stLight);
	g_pD3DDevice->LightEnable(0, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
}


void cMainGame::SetUI()
{
	//////////////////////////////////////////////////////////
	//						CrossHair						//
	//////////////////////////////////////////////////////////

	LPD3DXSPRITE				pSprite;
	D3DXCreateSprite(g_pD3DDevice, &pSprite);
	cUIImageView* pCrossHair = new cUIImageView;
	//	m_pUIImage->SetSize(ST_SIZE(1, 1));
	pCrossHair->SetTexture("UI/normalBg.tga", 8, 4);
	pCrossHair->SetCurrentFrame(8);
	pCrossHair->SetCenterPosition(D3DXVECTOR3(GetWindowWidth() / 2, GetWindowHeight() / 2, 0));

	pCrossHair->SetSprite(pSprite);

	GETSINGLE(cUIMgr)->AddUI("CrossHair", pCrossHair);
	GETSINGLE(cUIMgr)->AddList("CrossHair");

	//////////////////////////////////////////////////////////
	//						Boss Hp							//
	//////////////////////////////////////////////////////////

	cUIImageView* ui = new cUIImageView;
	ui->SetTexture("UI/GageBoss.tga", 1, 1);
	//	m_pUIImage->SetPosition()
	ui->SetCenterPosition(D3DXVECTOR3(GetWindowWidth() / 2 + 223, 32, 0));
	ui->SetSprite(pSprite);

	cUIImageView* ui2 = new cUIImageView;
	ui2->SetTexture("UI/GageBoss_IB1.tga", 1, 1);
	ui2->SetPosition(D3DXVECTOR3(49, 17, 0));
	ui2->SetColor(XRED);
	//	ui2->SetScaleX(0.5f);
	ui2->SetSprite(pSprite);
	ui2->SetTag(1);
	ui->AddChild(ui2);

	cUITextView* ui3 = new cUITextView;
	ui3->SetFont(GETSINGLE(cFontMgr)->GetFont(E_FONT_BOSS_STATUS));
	ui3->SetSize(ST_SIZE(100, 56));
	ui3->SetPosition(D3DXVECTOR3(223, 0, 0));
	ui3->SetTag(2);
	ui->AddChild(ui3);

	//	m_pUIBossHp = ui;
	GETSINGLE(cUIMgr)->AddUI("Orca", ui);

	//////////////////////////////////////////////////////////
	//						Player Hp						//
	//////////////////////////////////////////////////////////

	//HPbg
	cUIImageView* pUI = new cUIImageView;
	pUI->SetTexture("UI/GageBar_I3.tga", 1, 1);
	//	m_pUIImage->SetPosition()
	pUI->SetCenterPosition(D3DXVECTOR3(GetWindowWidth() / 2 + 20, GetWindowHeight() - 100, 0));
	pUI->SetScaleX(1.5);
	pUI->SetScaleY(1.5);
	pUI->SetSprite(pSprite);

	//MPbg
	cUIImageView* pUI2 = new cUIImageView;
	pUI2->SetTexture("UI/GageBar_I3.tga", 1, 1);
	pUI2->SetPosition(D3DXVECTOR3(0, pUI->GetSize().fHeight, 0));
	pUI2->SetScaleX(1.5);
	pUI2->SetScaleY(1.5);
	pUI2->SetSprite(pSprite);
	pUI->AddChild(pUI2);

	//HP
	cUIImageView* pUI3 = new cUIImageView;
	pUI3->SetTexture("UI/GageBar_IC.tga", 1, 1);
	pUI3->SetPosition(D3DXVECTOR3(6, 13, 0));
	pUI3->SetScaleX(1.5);
	pUI3->SetScaleY(1.5);
	pUI3->SetTag(1);
	pUI3->SetSprite(pSprite);
	pUI->AddChild(pUI3);

	////HP Text
	//cUITextView* pUI4 = new cUITextView;
	//pUI4->SetFont(GETSINGLE(cFontMgr)->GetFont(E_FONT_BOSS_STATUS));
	//pUI4->SetSize(ST_SIZE(100, 56));
	//pUI4->SetPosition(D3DXVECTOR3(20, 0, 0));
	//pUI4->SetTag(2);
	//pUI->AddChild(pUI4);

	//MP
	cUIImageView* pUI5 = new cUIImageView;
	pUI5->SetTexture("UI/GageBar_IF.tga", 1, 1);
	pUI5->SetPosition(D3DXVECTOR3(6, pUI->GetSize().fHeight + 13, 0));
	pUI5->SetScaleX(1.5);
	pUI5->SetScaleY(1.5);
	pUI5->SetTag(3);
	pUI5->SetSprite(pSprite);
	pUI->AddChild(pUI5);



	//	m_pUIPlayerHp = pUI;
	GETSINGLE(cUIMgr)->AddUI("Player", pUI);
	GETSINGLE(cUIMgr)->AddList("Player");

	SAFE_RELEASE(pSprite);
}


void cMainGame::SetShader()
{
	//MultiAnimation
	D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL, NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	g_pD3DDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion > D3DVS_VERSION(1, 1))
		pmac = mac;

	GETSINGLE(cShaderMgr)->AddEffect(E_SHADER_DYNAMICMESH, "MultiAnimation.hpp", pmac);

	///////////////////////////////////////////////////////////////

	//Test
	/*D3DXMACRO mac[2] =
	{
		{ "MATRIX_PALETTE_SIZE_DEFAULT", "35" },
		{ NULL, NULL }
	};

	D3DCAPS9 caps;
	D3DXMACRO *pmac = NULL;
	g_pD3DDevice->GetDeviceCaps(&caps);
	if (caps.VertexShaderVersion > D3DVS_VERSION(1, 1))
		pmac = mac;*/

	GETSINGLE(cShaderMgr)->AddEffect(E_SHADER_EFFECT, "Effect.hpp");
}