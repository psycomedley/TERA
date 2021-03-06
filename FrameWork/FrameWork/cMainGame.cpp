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
#include "cObjectTool.h"
#include "cText.h"
#include "cCamera.h"
#include "cGuardian.h"
#include "cGardener.h"
#include "cUIButton.h"
#include "cSkyBox.h"


cMainGame::cMainGame()
	: m_bLockMouse(true)
	, m_cObjectTool(NULL)
{
}


cMainGame::~cMainGame()
{
	///////////////임시////////////////

	SAFE_RELEASE(m_cObjectTool);


	//SAFE_RELEASE(m_pRushEffect);

	///////////////////////////////////


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
	GETSINGLE(cSoundMgr)->Setup();
	GETSINGLE(cFrustum)->Setup();

	SetShader();
	SetEffect();
	SetUI();
	SetLighting();

	cText* pText = new cText;
	pText->Setup(E_FONT_DAMAGE, "PlayerDamage", "1", D3DXVECTOR2(100, 100), ST_SIZE(80, 50), XYELLOW,
		TEXT_ALPHA | TEXT_MOVE | TEXT_SHOWTIME | TEXT_MOVEAFTERTIME);
	pText->SetShowTime(1.0f);
	pText->SetAlphaTime(0.5f);
	pText->SetMoveSpeed(0.5f);
	pText->SetDirection(DIRECTION_UP);
	pText->SetMoveTime(0.5f);
	GETSINGLE(cTextMgr)->AddText(pText);

	pText = new cText;
	pText->Setup(E_FONT_MONSTERDAMAGE, "MonsterDamage", "1", D3DXVECTOR2(100, 100), ST_SIZE(80, 50), XRED,
		TEXT_ALPHA | TEXT_MOVE | TEXT_SHOWTIME | TEXT_MOVEAFTERTIME);
	pText->SetShowTime(2.0f);
	pText->SetAlphaTime(0.5f);
	pText->SetMoveSpeed(0.5f);
	pText->SetDirection(DIRECTION_UP);
	pText->SetMoveTime(0.5f);
	GETSINGLE(cTextMgr)->AddText(pText);

	pText = new cText;
	pText->Setup(E_FONT_MONSTERDAMAGE, "RegenHP", "1", D3DXVECTOR2(100, 100), ST_SIZE(80, 50), XGREEN,
		TEXT_ALPHA | TEXT_MOVE | TEXT_SHOWTIME | TEXT_MOVEAFTERTIME);
	pText->SetShowTime(0.2f);
	pText->SetAlphaTime(0.5f);
	pText->SetMoveSpeed(0.5f);
	pText->SetDirection(DIRECTION_UP);
	pText->SetMoveTime(0.5f);
	GETSINGLE(cTextMgr)->AddText(pText);

	pText = new cText;
	pText->Setup(E_FONT_MONSTERDAMAGE, "RegenMP", "1", D3DXVECTOR2(100, 100), ST_SIZE(80, 50), XBLUE,
		TEXT_ALPHA | TEXT_MOVE | TEXT_SHOWTIME | TEXT_MOVEAFTERTIME);
	pText->SetShowTime(0.2f);
	pText->SetAlphaTime(0.5f);
	pText->SetMoveSpeed(0.5f);
	pText->SetDirection(DIRECTION_UP);
	pText->SetMoveTime(0.5f);
	GETSINGLE(cTextMgr)->AddText(pText);



	cDynamicObj* pPlayer = new cPlayer("Popori", "Popori.X");
	pPlayer->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DX_PI / 2);
	pPlayer->SetRevision(matR);
	pPlayer->SetRevisionAngle(D3DX_PI / 2);
	GETSINGLE(cObjMgr)->SetPlayer(pPlayer);

	cDynamicObj* pBoss = new cOrca("Monster", "Orca.X");
	pBoss->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pBoss->SetRevision(matR);
	pBoss->SetRevisionAngle(D3DX_PI / 2);
	pBoss->SetPosition(D3DXVECTOR3(245, 0, 30));
	GETSINGLE(cObjMgr)->AddMonster(((cOrca*)pBoss)->GetInfo().sName, pBoss);

	SetCamera();
	
	// 일반몬스터 셋팅
	MonsterPositionSetting();


	//	GETSINGLE(cCameraMgr)->Setup();
	GETSINGLE(cCameraMgr)->GetCamera("MainCamera")->SetVecTarget(&GETSINGLE(cObjMgr)->GetPlayer()->GetCameraFocus());

	GETSINGLE(cObjectToolMgr)->Setup();

	//	m_pMap = new cMap("Map","fieldmap1.x");
	cMap* pMap = new cMap("Map", "fieldmap1.x");
	GETSINGLE(cObjMgr)->SetMap(pMap);

	m_cObjectTool = new cObjectTool;
	m_cObjectTool->Setup();

	//	GETSINGLE(cSoundMgr)->Play(pMap->GetSoundKey(E_MAP_SOUND_BGM));

	///////////////임시////////////////


	cSkyBox* pSkyBox = new cSkyBox;
	GETSINGLE(cObjMgr)->SetSkyBox(pSkyBox);


	GETSINGLE(cObjMgr)->Setup();

	//m_pEffect4 = new cEffect;
	//m_pEffect4->Setup(10, 10, 1, EFFECT_ALPHABLEND);
	//m_pEffect4->SetTexture("Effect/D_BaPho_CrackMake002_Emis.tga", E_TEXTURE1);
	//m_pEffect4->SetPosition(D3DXVECTOR3(10, 0, 10));
	//m_pEffect4->AddTechList(E_TECH_NORMAL);
	//D3DXMATRIXA16 rotationMat;
	//D3DXMatrixRotationX(&rotationMat, D3DX_PI / 2);
	//m_pEffect4->SetMatRotation(rotationMat);




	//임시 세팅 (비정상 동작중)
	//m_pDynamicMeshEffect = new cDynamicMeshEffect("Effect", "Circle.X");
	//m_pDynamicMeshEffect->SetPosition(D3DXVECTOR3(30, 0, 0));
	//m_pDynamicMeshEffect->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));


	//	m_pCircleEffect = new cCircleEffect("Effect", "blueCircle.x");



	//m_pCircleEffect->SetScale(D3DXVECTOR3(0.0000001f, 0.0000001f, 0.0000001f));
	//	m_pCircleEffect->Setup(60, 0.2f, true, D3DXVECTOR3(0.2f,0.2f,0.2f),D3DXVECTOR3(20,1.5f,0));

	//m_pRushEffect = new cRushEffect("Effect", "RushEffect2.x");
	//m_pRushEffect->Setup(40, 0.015f, true, D3DXVECTOR3(0.005f, 0.005f, 0.005f), D3DXVECTOR3(25, 1.5f, 0));



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

		GETSINGLE(cFrustum)->Update();

		GETSINGLE(cCameraMgr)->Update();

		GETSINGLE(cTextMgr)->Update();

		GETSINGLE(cBattleMgr)->Update();

		GETSINGLE(cUIMgr)->Update();

		GETSINGLE(cEventMgr)->Update();
	}
	

	if (KEYBOARD->IsOnceKeyDown(DIK_F5))
		g_nRenderOption ^= RENDER_BOUNDINGPLAYER;
	if (KEYBOARD->IsOnceKeyDown(DIK_F6))
		g_nRenderOption ^= RENDER_BOUNDINGWEAPON;
	if (KEYBOARD->IsOnceKeyDown(DIK_F7))
		g_nRenderOption ^= RENDER_BOUNDINGMONSTER;
	if (KEYBOARD->IsOnceKeyDown(DIK_F8))
		g_nRenderOption ^= RENDER_BOUNDINGOBJECT;
	if (KEYBOARD->IsOnceKeyDown(DIK_F9))
		g_nRenderOption ^= RENDER_FRUSTUMCULL;
	if (KEYBOARD->IsOnceKeyDown(DIK_F11))
		g_nRenderOption ^= RENDER_BOUNDINGBOX;
	if (KEYBOARD->IsOnceKeyDown(DIK_F12))
		g_nRenderOption ^= RENDER_BOUNDINGSPHERE;


	// 오브젝트 툴 켜고끄기
	if (KEYBOARD->IsToggleKey(VK_F3))
	{
		if (m_cObjectTool)
			m_cObjectTool->Update();
	}
	//충돌 on/off용
	if (KEYBOARD->IsToggleKey(VK_F1))
	{
		int a = 0;
	}
	else
	{
		GETSINGLE(cObjectToolMgr)->Update();
	}

	///////////////임시////////////////

	CHAR str[16];
	wsprintf(str, TEXT("FPS : %d"), GETSINGLE(cTimeMgr)->getFrameRate());
	SetWindowText(g_hWnd, str);


	/*if (m_pBoss)
	m_pBoss->Update();*/
	//	if(MOUSE->IsOnceKeyDown(MOUSEBTN_LEFT))
	//m_pDynamicMeshEffect->Setup();

	GETSINGLE(cEffectMgr)->Update();
	//if (m_pCircleEffect)
	//{
	//	m_pCircleEffect->Update();
	//}
	//if (m_pRushEffect)
	//{
	//	m_pRushEffect->Update();
	//}

	GETSINGLE(cObjMgr)->Update();


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

	//	OutputInteger(msg, "x", ptPosition.x);
	//	OutputInteger(msg, "y", ptPosition.y);

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

	

	if (KEYBOARD->IsToggleKey(VK_F2))
	{
		m_cObjectTool->Render();
	}

	GETSINGLE(cObjMgr)->Render();
	GETSINGLE(cEffectMgr)->Render();
	GETSINGLE(cUIMgr)->Render();
	GETSINGLE(cTextMgr)->Render();


	///////////////임시////////////////




	//if (m_pCircleEffect)
	//{
	//	m_pCircleEffect->Render();
	//}
	//if (m_pRushEffect)
	//{
	//	m_pRushEffect->Render();
	//}
	//if (m_pDynamicMeshEffect)
	//{
	//	m_pDynamicMeshEffect->Render();
	//}








	///////////////////////////////////

	GETSINGLE(cDevice)->EndRender();
}


void cMainGame::Release()
{
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
	GETSINGLE(cEffectMgr)->Release();
	GETSINGLE(cSoundMgr)->Release();
	GETSINGLE(cBattleMgr)->Release();
	GETSINGLE(cObjectToolMgr)->Release();
	GETSINGLE(cEventMgr)->Release();

	GETSINGLE(cDevice)->Release();

}


void cMainGame::SetCamera()
{ 
	cCamera* pCamera = new cCamera;
	pCamera->Setup();
	GETSINGLE(cCameraMgr)->AddCamera("MainCamera", pCamera);
	GETSINGLE(cCameraMgr)->SetCurrentCamera("MainCamera");

	pCamera = new cCamera;
	pCamera->Setup();
	pCamera->SetCamDist(-30);
	pCamera->SetControl(false);
	pCamera->SetTarget(GETSINGLE(cObjMgr)->GetMonsterList("Orca")->front());

	GETSINGLE(cCameraMgr)->AddCamera("EventCamera", pCamera);
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
	ui2->SetTag(E_UITAG_HP);
	ui->AddChild(ui2);

	cUITextView* ui3 = new cUITextView;
	ui3->SetFont(GETSINGLE(cFontMgr)->GetFont(E_FONT_BOSS_STATUS));
	ui3->SetSize(ST_SIZE(100, 56));
	ui3->SetPosition(D3DXVECTOR3(223, 0, 0));
	ui3->SetTag(E_UITAG_HPTEXT);
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
	pUI3->SetTag(E_UITAG_HP);
	pUI3->SetSprite(pSprite);
	pUI->AddChild(pUI3);

	//HP Text
	cUITextView* pUI4 = new cUITextView;
	pUI4->SetFont(GETSINGLE(cFontMgr)->GetFont(E_FONT_BOSS_STATUS));
	pUI4->SetSize(ST_SIZE(400, 56));
	pUI4->SetPosition(D3DXVECTOR3(36, -3, 0));
	pUI4->SetTag(E_UITAG_HPTEXT);
	pUI->AddChild(pUI4);

	//MP
	cUIImageView* pUI5 = new cUIImageView;
	pUI5->SetTexture("UI/GageBar_IF.tga", 1, 1);
	pUI5->SetPosition(D3DXVECTOR3(6, pUI->GetSize().fHeight + 13, 0));
	pUI5->SetScaleX(1.5);
	pUI5->SetScaleY(1.5);
	pUI5->SetTag(E_UITAG_MP);
	pUI5->SetSprite(pSprite);
	pUI->AddChild(pUI5);

	//MP Text
	cUITextView* pUI6 = new cUITextView;
	pUI6->SetFont(GETSINGLE(cFontMgr)->GetFont(E_FONT_BOSS_STATUS));
	pUI6->SetSize(ST_SIZE(400, 56));
	pUI6->SetPosition(D3DXVECTOR3(36, 29, 0));
	pUI6->SetTag(E_UITAG_MPTEXT);
	pUI->AddChild(pUI6);

	//Text
	cUITextView* pUI7 = new cUITextView;
	pUI7->SetFont(GETSINGLE(cFontMgr)->GetFont(E_FONT_BOSS_STATUS));
	pUI7->SetSize(ST_SIZE(55, 56));
	pUI7->SetText("HP");
	pUI7->SetPosition(D3DXVECTOR3(0, -3, 0));
	pUI->AddChild(pUI7);

	pUI7 = new cUITextView;
	pUI7->SetFont(GETSINGLE(cFontMgr)->GetFont(E_FONT_BOSS_STATUS));
	pUI7->SetSize(ST_SIZE(55, 56));
	pUI7->SetText("MP");
	pUI7->SetPosition(D3DXVECTOR3(0, 29, 0));
	pUI->AddChild(pUI7);

	//	m_pUIPlayerHp = pUI;
	GETSINGLE(cUIMgr)->AddUI("Player", pUI);



	////임시
	//pSprite;
	//D3DXCreateSprite(g_pD3DDevice, &pSprite);
	//cUIImageView* p = new cUIImageView;
	////	m_pUIImage->SetSize(ST_SIZE(1, 1));
	//p->SetTexture("UI/ComboCounter_I3.tga", 1, 1);
	//p->SetCurrentFrame(0);
	//p->SetCenterPosition(D3DXVECTOR3(GetWindowWidth() / 2, GetWindowHeight() / 2, 0));

	//p->SetSprite(pSprite);

	//GETSINGLE(cUIMgr)->AddUI("p", p);
	//GETSINGLE(cUIMgr)->AddList("p");





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

	GETSINGLE(cShaderMgr)->AddEffect(E_SHADER_MAP, "mapShader.fx");
}


void cMainGame::SetEffect()
{
	D3DXMATRIXA16 m, m2, m3;
	cEffect* pEffect = new cEffect;
	//오르카 스킬1 (구체)
	pEffect->Setup(5, 5, 1, EFFECT_ALPHABLEND | EFFECT_BILLBOARING | EFFECT_CUTTEDFRAME /*| EFFECT_LOOPEDFRAME*/);
	pEffect->SetTexture("Effect/Lens00_emis.tga", E_TEXTURE1);
	pEffect->SetTexture("Effect/Lens04_emis.tga", E_TEXTURE2);
	pEffect->SetTexture("Effect/A_Lightning001_emis.tga", E_TEXTURE3);
	pEffect->SetTexture("Effect/bumpnoisesemi64.tga", E_BUMPMAP);
	pEffect->SetTotalFrame(4, 4, 16);
	pEffect->SetPosition(D3DXVECTOR3(20, 5, 10));
	pEffect->AddTechList(E_TECH_ORCA1);
	pEffect->AddTechList(E_TECH_ORCA1_REMOVE);
	//	pEffect->SetTechnique(E_TECH_ORCA1);
	pEffect->SetNextTime(0.03);
	pEffect->SetLoop(true);
	pEffect->SetRemoveTime(3.0f);
	//	pEffect->SetLoopTimes(20);
	pEffect->SetName("orca1");

	GETSINGLE(cEffectMgr)->AddEffect(pEffect->GetName(), pEffect);

	//오르카 평타
	pEffect = new cEffect;
	pEffect->Setup(150, 150, 1, EFFECT_ALPHABLEND);
	pEffect->SetTexture("Effect/D_CircleDecal001_Emis.tga", E_TEXTURE1);
	pEffect->SetTexture("Effect/K_BlueCaustic001_emis.tga", E_TEXTURE2);
	//m_pEffect2->SetTexture("Effect/B_NormalMap005_Mask.tga", E_BUMPMAP);
	pEffect->SetPosition(D3DXVECTOR3(22, 2, 10));
	pEffect->AddTechList(E_TECH_ORCA2);
	//	pEffect->SetTechnique(E_TECH_ORCA2);

	//m_pEffect2->SetAngle(D3DX_PI / 2);
	D3DXMatrixRotationX(&m, D3DX_PI / 2);
	pEffect->SetMatRotation(m);

	pEffect->SetLoop(false);
	pEffect->SetRemoveTime(2);
	pEffect->SetName("orca2");

	GETSINGLE(cEffectMgr)->AddEffect(pEffect->GetName(), pEffect);

	//오르카 백어택
	pEffect = new cEffect;
	pEffect->Setup(20, 20, 1, EFFECT_ALPHABLEND);
	pEffect->SetTexture("Effect/B_160Trail001_emis.tga", E_TEXTURE1);
	pEffect->SetTexture("Effect/K_BlueCaustic001_emis.tga", E_TEXTURE2);
	pEffect->SetPosition(D3DXVECTOR3(20, 2, 10));
	pEffect->AddTechList(E_TECH_BACKATK);
	//	pEffect->SetTechnique(E_TECH_BACKATK);

	D3DXMatrixRotationX(&m, D3DX_PI / 2);
	D3DXMatrixRotationY(&m2, D3DX_PI / 4);
	m3 = m * m2;
	pEffect->SetMatRotation(m3);
	//	m_pEffect2->SetAngle(D3DX_PI / 2);
	//	m_pEffect2->SetLoop(false);
	pEffect->SetRemoveTime(3);
	pEffect->SetName("orcaBackAtk");

	GETSINGLE(cEffectMgr)->AddEffect(pEffect->GetName(), pEffect);

	//마법진
	pEffect = new cEffect;
	pEffect->Setup(20, 20, 1, EFFECT_ALPHABLEND);
	pEffect->SetTexture("Effect/G_MagicArray002_Tex.tga", E_TEXTURE1);
	pEffect->SetPosition(D3DXVECTOR3(0, 0, 0));

	pEffect->SetAngle(D3DX_PI / 2);

	pEffect->AddTechList(E_TECH_MAGICARRAY);
	//	pEffect->SetTechnique(E_TECH_MAGICARRAY);
	//	D3DXMATRIXA16 ma;
	//	D3DXMatrixRotationX(&ma, D3DX_PI / 2);
	pEffect->SetMatRotation(m);
	pEffect->SetRemoveTime(5);
	pEffect->SetName("MagicArray");

	GETSINGLE(cEffectMgr)->AddEffect(pEffect->GetName(), pEffect);


	//구체 공격
	pEffect = new cEffect;
	pEffect->Setup(150, 150, 1, EFFECT_ALPHABLEND);
	pEffect->SetTexture("Effect/D_CircleDecal001_Emis.tga", E_TEXTURE1);
	pEffect->SetTexture("Effect/K_BlueCaustic001_emis.tga", E_TEXTURE2);
	//m_pEffect2->SetTexture("Effect/B_NormalMap005_Mask.tga", E_BUMPMAP);
	pEffect->SetPosition(D3DXVECTOR3(22, 2, 10));
	pEffect->AddTechList(E_TECH_GLOBEATK);
	//	pEffect->SetTechnique(E_TECH_ORCA2);

	//m_pEffect2->SetAngle(D3DX_PI / 2);
	D3DXMatrixRotationX(&m, D3DX_PI / 2);
	pEffect->SetMatRotation(m);

	pEffect->SetLoop(false);
	pEffect->SetRemoveTime(2);
	pEffect->SetName("GlobeAtk");

	GETSINGLE(cEffectMgr)->AddEffect(pEffect->GetName(), pEffect);


	//	//구체 공격2
	//	pEffect = new cEffect;
	//	pEffect->Setup(5, 5, 1, EFFECT_ALPHABLEND | EFFECT_CUTTEDFRAME /*| EFFECT_LOOPEDFRAME*/);
	//	pEffect->SetTexture("Effect/D_MOVArchaLightBig001_Emis.tga", E_TEXTURE1);
	//	pEffect->SetTotalFrame(8, 4, 32);
	//	pEffect->SetPosition(D3DXVECTOR3(20, 5, 10));
	//	pEffect->AddTechList(E_TECH_GLOBEATK2);
	//	pEffect->SetNextTime(0.03);
	//	pEffect->SetLoop(false);
	//	pEffect->SetRemoveTime(3.0f);
	////	pEffect->SetLoopTimes(20);
	//	pEffect->SetName("GlobeAtk2");
	//
	//	GETSINGLE(cEffectMgr)->AddEffect(pEffect->GetName(), pEffect);

	//바닥 깨지는 이펙트
	pEffect = new cEffect;
	pEffect->Setup(5, 5, 1, EFFECT_ALPHABLEND);
	pEffect->SetTexture("Effect/D_BaPho_CrackMake002_Emis.tga", E_TEXTURE1);
	pEffect->SetPosition(D3DXVECTOR3(0, 0, 0));
	pEffect->AddTechList(E_TECH_NORMAL);
	D3DXMatrixRotationX(&m, 0.0f);
	pEffect->SetMatRotation(m);
	pEffect->SetRemoveTime(1);
	pEffect->SetName("badak");
	GETSINGLE(cEffectMgr)->AddEffect(pEffect->GetName(), pEffect);

	//2번스킬 이펙트
	pEffect = new cEffect;
	pEffect->Setup(3, 3, 1, EFFECT_BILLBOARING | EFFECT_ALPHABLEND);
	pEffect->SetTexture("Effect/attack.tga", E_TEXTURE1);
	pEffect->SetPosition(D3DXVECTOR3(0, 1, 0));
	pEffect->AddTechList(E_TECH_NORMAL);
	pEffect->SetRemoveTime(0.04f);
	pEffect->SetName("skill2");
	GETSINGLE(cEffectMgr)->AddEffect(pEffect->GetName(), pEffect);


}
void cMainGame::MonsterPositionSetting()
{
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DX_PI / 2);
	// =========그리드 근처
	cDynamicObj* pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(120, 0, 150));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(125, 0, 145));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(110, 0, 145));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(105, 0, 115));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(105, 0, 105));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	
	//=========== 장작 있는근처
	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetPosition(D3DXVECTOR3(110, 0, 150));
	pMonster->SetAngle(GetFloat(D3DX_PI));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(3, 0, 170));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(20, 0, 160));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(5, 0, 120));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(13, 0, 125));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	//============ 중간 큰 공터
	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(70, 0, 200));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(75, 0, 205));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(70, 0, 208));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	// ==============보스 전면
	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(-D3DX_PI / 4);
	pMonster->SetPosition(D3DXVECTOR3(200, 0, 70));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(-D3DX_PI / 4);
	pMonster->SetPosition(D3DXVECTOR3(190, 0, 75));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(-D3DX_PI / 4);
	pMonster->SetPosition(D3DXVECTOR3(180, 0, 70));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(-D3DX_PI / 4);
	pMonster->SetPosition(D3DXVECTOR3(200, 0, 80));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	///================언덕
	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(80, 0, 65));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(70, 0, 50));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(80, 0, 50 ));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(90, 0, 50));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);


	//==============텐트 근처
	pMonster = new cGuardian("Monster", "Guardian.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetAngle(GetFromFloatTo(0,1.0f));
	pMonster->SetPosition(D3DXVECTOR3(130, 0, 280));
	GETSINGLE(cObjMgr)->AddMonster(((cGuardian*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(135, 0, 284));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(120, 0, 275));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(138, 0, 280));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

	pMonster = new cGardener("Monster", "Gardener.X");
	pMonster->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pMonster->SetRevision(matR);
	pMonster->SetRevisionAngle(D3DX_PI / 2);
	pMonster->SetAngle(GetFloat(D3DX_PI));
	pMonster->SetPosition(D3DXVECTOR3(120, 0, 288));
	GETSINGLE(cObjMgr)->AddMonster(((cGardener*)pMonster)->GetInfo().sName, pMonster);

}

