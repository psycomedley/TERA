#include "stdafx.h"
#include "cShaderMgr.h"


cShaderMgr::cShaderMgr()
{
}


cShaderMgr::~cShaderMgr()
{
}


LPD3DXEFFECT cShaderMgr::GetEffect(string sKey)
{
	if (m_mapEffect.find(sKey) == m_mapEffect.end())
	{
		LPD3DXBUFFER pErrBuf = NULL;
		if (FAILED(D3DXCreateEffectFromFile(g_pD3DDevice, sKey.c_str(), NULL, NULL, D3DXSHADER_DEBUG
			, NULL, &m_mapEffect[sKey], &pErrBuf)))
		{
			MSGBOX((char*)pErrBuf->GetBufferPointer());
			SAFE_RELEASE(pErrBuf);
			return NULL;
		}
	}
	return m_mapEffect[sKey];
}


void cShaderMgr::Release()
{
	for (auto iter = m_mapEffect.begin();
		iter != m_mapEffect.end(); iter++)
	{
		if (iter->second)
		{
			SAFE_RELEASE(iter->second);
		}
	}
	m_mapEffect.clear();

	cSingleton::Release();
}