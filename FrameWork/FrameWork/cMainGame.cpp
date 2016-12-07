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

//임시


cMainGame::cMainGame()
	: m_bLockMouse(true)
{
}


cMainGame::~cMainGame()
{
	///////////////임시////////////////
	SAFE_DELETE(m_pGrid);

	SAFE_DELETE(m_pEffect);
	SAFE_DELETE(m_pEffect2);
	SAFE_RELEASE(m_pDynamicMeshEffect);


	SAFE_RELEASE(m_pBoss2);
	///////////////////////////////////

	SAFE_RELEASE(m_pMap);

	SAFE_RELEASE(m_pStaticMeshEffect);

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

	cDynamicObj* pPlayer = new cPlayer("Popori", "Popori.X");
	pPlayer->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DX_PI / 2);
	pPlayer->SetRevision(matR);
	pPlayer->SetPosition(D3DXVECTOR3(20, 0, 0));
	GETSINGLE(cObjMgr)->SetPlayer(pPlayer);

	cDynamicObj* pBoss = new cOrca("Monster", "Orca.X");
	pBoss->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	pBoss->SetRevision(matR);
	GETSINGLE(cObjMgr)->AddMonster(((cOrca*)pBoss)->GetInfo().sName, pBoss);

	/*cDynamicObj* m_pBoss2 = new cOrca("Monster", "Orca.X");
	m_pBoss2->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	m_pBoss2->SetRevision(matR);
	m_pBoss2->SetPosition(D3DXVECTOR3(10, 0, 0));
	GETSINGLE(cObjMgr)->AddMonster(((cOrca*)m_pBoss2)->GetInfo().sName, m_pBoss2);*/

	GETSINGLE(cCameraMgr)->Setup();
	GETSINGLE(cCameraMgr)->GetCamera()->SetVecTarget(&GETSINGLE(cObjMgr)->GetPlayer()->GetCameraFocus());

	m_pMap = new cMap("Map","Map.x");

	///////////////임시////////////////

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	/*m_pBoss2 = new cMonster("Monster", "Orca.X");
	m_pBoss2->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	m_pBoss2->SetRevision(matR);
	m_pBoss2->SetPosition(D3DXVECTOR3(10, 0, 0));*/

	m_pEffect = new cEffect;
	m_pEffect->Setup("Effect/fire.tga", 20, 20, 4, 4, 0.01f, true);
	m_pEffect2 = new cEffect;
	m_pEffect2->Setup("Effect/fire.tga", 10, 10, 4, 4, 0.01f , false, 128);

	m_pStaticMeshEffect = new cStaticMeshEffect("Effect","Crosshair1.X");
	m_pStaticMeshEffect->Setup();
	
	//임시 세팅 (비정상 동작중)
	/*m_pDynamicMeshEffect = new cDynamicMeshEffect("Effect", "Circle.X");
	m_pDynamicMeshEffect->SetPosition(D3DXVECTOR3(20, 0, 0));
	m_pDynamicMeshEffect->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));*/

	SetLighting();


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
	}

	//지형 충돌 
	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPosition();
	
	if (m_pMap->GetHeight(playerPos.x, playerPos.y, playerPos.z))
	{
		float y = playerPos.y;
		pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
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
			m_pEffect2->Start();
	}
	//	m_pMap->Update();


	/*if (KEYBOARD->IsStayKeyDown(DIK_I))
	{
		m_pBoss->SetPosition(m_pBoss->GetPosition() - m_pBoss->GetDirection() * 0.1);
	}*/

	/*if (m_pBoss)
		m_pBoss->Update();*/

	if (m_pEffect)
		m_pEffect->Update();
	if (m_pEffect2)
		m_pEffect2->Update();


	///////////////////////////////////
}


void cMainGame::Render()
{
	GETSINGLE(cDevice)->BeginRender();

	POINT pos = MOUSE->GetWindowPos();
//	POINT pos;
//	GetCursorPos(&pos);
	char msg[128];

	
	OutputInteger(msg, "x", pos.x);
	OutputInteger(msg, "y", pos.y);

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


	if (m_pMap)
		m_pMap->Render();

	///////////////임시////////////////
	
	m_pGrid->Render();


	if (m_pBoss2)
	{	
		/*m_pBoss2->UpdateAndRender();
		m_pBoss2->Bounding_Render();*/
	}

	/*if (m_pPlayer)
	m_pPlayer->UpdateAndRender();*/
	//	m_pPlayer->Bounding_Render();

	//if (m_pBoss)
	//{
	//	m_pBoss->UpdateAndRender();
//	//	m_pBoss->Bounding_Render();
	//}

	if (m_pStaticMeshEffect)
		m_pStaticMeshEffect->Render();

	if (m_pDynamicMeshEffect)
		m_pDynamicMeshEffect->Render();

	if (m_pEffect)
		m_pEffect->Render();
	if (m_pEffect2)
		m_pEffect2->Render();



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