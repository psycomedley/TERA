#include "stdafx.h"
#include "cCameraMgr.h"
#include "cCamera.h"

cCameraMgr::cCameraMgr()
	: m_pCamera(NULL)
{
}


cCameraMgr::~cCameraMgr()
{
}


HRESULT cCameraMgr::Setup()
{
	m_pCamera = new cCamera;
	m_pCamera->Setup();

	return S_OK;
}


void cCameraMgr::Update()
{
	if (m_pCamera)
		m_pCamera->Update();
}


void cCameraMgr::Release()
{
	SAFE_DELETE(m_pCamera);

	cSingleton::Release();
}