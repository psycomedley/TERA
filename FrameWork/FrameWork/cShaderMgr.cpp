#include "stdafx.h"
#include "cShaderMgr.h"


cShaderMgr::cShaderMgr()
{
}


cShaderMgr::~cShaderMgr()
{
}


HRESULT cShaderMgr::AddEffect(E_EFFECT_TYPE eType, string sFilename)
{
	if (m_mapEffect.find(eType) == m_mapEffect.end())
		return E_FAIL;

	string sFullPath = "Shader/";
	sFullPath += sFilename;

	LPD3DXBUFFER pErrBuf = NULL;
	if (FAILED(D3DXCreateEffectFromFile(g_pD3DDevice, sFullPath.c_str(), NULL, NULL, D3DXSHADER_DEBUG
		, NULL, &m_mapEffect[eType], &pErrBuf)))
	{
		MSGBOX((char*)pErrBuf->GetBufferPointer());
		SAFE_RELEASE(pErrBuf);
		return E_FAIL;
	}
	return S_OK;
}



LPD3DXEFFECT cShaderMgr::GetEffect(E_EFFECT_TYPE eType)
{
	auto iter = m_mapEffect.find(eType);
	if (iter == m_mapEffect.end())
		return NULL;

	return m_mapEffect[eType];
}


void cShaderMgr::Release()
{
	for each(auto it in m_mapEffect)
		SAFE_RELEASE(it.second);
//	m_mapEffect.clear();

	cSingleton::Release();
}