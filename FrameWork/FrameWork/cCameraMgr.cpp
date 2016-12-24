#include "stdafx.h"
#include "cCameraMgr.h"
#include "cCamera.h"

cCameraMgr::cCameraMgr()
//	: m_pCamera(NULL)
{
}


cCameraMgr::~cCameraMgr()
{
}


HRESULT cCameraMgr::Setup()
{
//	m_pCurrentCamera = new cCamera;
//	m_pCurrentCamera->Setup();

	return S_OK;
}


void cCameraMgr::Update()
{
	if (m_pCurrentCamera)
		m_pCurrentCamera->Update();
}


void cCameraMgr::Release()
{
	for (auto iter = m_mapCamera.begin(); iter != m_mapCamera.end(); iter++)
		SAFE_DELETE(iter->second);
//	SAFE_DELETE(m_pCurrentCamera);

	cSingleton::Release();
}


void cCameraMgr::AddCamera(string sKey, cCamera* pCamera)
{
	auto iter = m_mapCamera.find(sKey);

	if (iter == m_mapCamera.end())
		m_mapCamera[sKey] = pCamera;
}


cCamera* cCameraMgr::GetCamera(string sKey)
{
	auto iter = m_mapCamera.find(sKey);

	if (iter == m_mapCamera.end())
		return NULL;

	return m_mapCamera[sKey];
}