#pragma once

class cShaderMgr : public cSingleton<cShaderMgr>
{
private:
	map<E_EFFECT_TYPE, LPD3DXEFFECT>	m_mapEffect;

public:
	HRESULT AddEffect(E_EFFECT_TYPE eType, string sFilename);

public:
	LPD3DXEFFECT GetEffect(E_EFFECT_TYPE eType);

public:
	void Release();

public:
	cShaderMgr();
	~cShaderMgr();
};

