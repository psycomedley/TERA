#pragma once

class cShaderMgr : public cSingleton<cShaderMgr>
{
private:
	map<E_SHADER_TYPE, LPD3DXEFFECT>	m_mapEffect;

public:
	HRESULT AddEffect(E_SHADER_TYPE eType, string sFilename, D3DXMACRO* pDefine = NULL);

public:
	LPD3DXEFFECT GetEffect(E_SHADER_TYPE eType);

public:
	void Release();

public:
	cShaderMgr();
	~cShaderMgr();
};

