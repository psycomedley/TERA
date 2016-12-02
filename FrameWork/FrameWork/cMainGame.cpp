#include "stdafx.h"
#include "cMainGame.h"
#include "cCamera.h"
#include "cStaticMesh.h"
#include "cDynamicMesh.h"
#include "cCube.h"
#include "cRay.h"
#include "cPlayer.h"

//임시
#include "cStateIdle.h"
#include "cStateRun.h"
#include "cStateDefence.h"
#include "cGrid.h"

cMainGame::cMainGame()
	: m_pCamera(NULL)
{
}


cMainGame::~cMainGame()
{
	///////////////임시////////////////
	SAFE_DELETE(m_pGrid);
	///////////////////////////////////

	SAFE_DELETE(m_pCamera);
	Release();

	SAFE_RELEASE(m_pPlayer);
	SAFE_RELEASE(m_pObj);
	SAFE_RELEASE(m_pObj2);
}


HRESULT cMainGame::Setup()
{
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


//	m_pMesh2 = new cDynamicMesh("Zealot", "zealot.X");
//	m_pMesh2->SetAnimationIdxBlend(4);
//	m_pMesh2->SetPosition(D3DXVECTOR3(4, 0, 0));

	m_pPlayer = new cPlayer("Popori", "Popori.X");
	m_pPlayer->SetScale(D3DXVECTOR3(0.05f, 0.05f, 0.05f));
	D3DXMATRIXA16 matR;
	D3DXMatrixRotationY(&matR, D3DX_PI / 2);
	m_pPlayer->SetRevision(matR);

	m_pCamera = new cCamera;
	m_pCamera->Setup();

	///////////////임시////////////////

	m_pGrid = new cGrid;
	m_pGrid->Setup(30);

	SetLighting();


	m_pObj = new cDynamicObj("Popori", "Popori.X");
	m_pObj->SetPosition(D3DXVECTOR3(5, 0, 0));

	m_pObj2 = new cDynamicObj("Zealot", "zealot.X");
	m_pObj2->SetPosition(D3DXVECTOR3(-5, 0, 0));


	///////////////////////////////////

	


//	m_pMap = new cStaticObj("Fire", "as.X");
//	m_pMap->SetScale(D3DXVECTOR3(0.003f, 0.003f, 0.003f));

	return S_OK;
}


void cMainGame::Update()
{
	GETSINGLE(cInput)->Update();

	if (m_pCamera)
		m_pCamera->Update(&m_pPlayer->GetPosition());
	
	///////////////임시////////////////
	
	//	m_pMap->Update();

	///////////////////////////////////
}


void cMainGame::Render()
{
	GETSINGLE(cDevice)->BeginRender();

	POINT pos = MOUSE->GetWindowPos();
	char msg[128];

	
//	OutputInteger(msg, "x", pos.x);
//	OutputInteger(msg, "y", pos.y);

//	if (MOUSE->IsOnceKeyDown(MOUSEBTN_LEFT))
//	{
//		POINT p = MOUSE->GetWindowPos();
//
//		cRay r;
//		r = cRay::CalcWorldSpace(p);
//
//		cBoundingSphere* sphere = m_pMesh->GetSphere();
//		r = r.WorldToLocal(sphere->GetCenter());
//
//
//		//	bool pick = r.IsPick(sphere);
//		if (GETSINGLE(cCollision)->Collision(sphere, &r))
//		{
//			static int c = 2;
//			m_pMesh->SetAnimationIdxBlend(++c % 5);
//		}
//
////		if (GETSINGLE())
//	}


	if (m_pPlayer)
	{
		m_pPlayer->UpdateAndRender();
	}
	///////////////임시////////////////
	
	m_pGrid->Render();
	
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