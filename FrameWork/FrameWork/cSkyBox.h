#pragma once
class cSkyBox
{
private:
	vector<ST_PT_VERTEX>		m_vecVertax;
	vector<DWORD>				m_vecIndex;

	LPDIRECT3DTEXTURE9			m_pTexture[6];
	LPDIRECT3DVERTEXBUFFER9		m_pVB[6];
	LPDIRECT3DINDEXBUFFER9		m_pIB[6];

	LPDIRECT3DVERTEXBUFFER9		m_VB;
	LPDIRECT3DINDEXBUFFER9		m_IB;
public:
	cSkyBox();
	~cSkyBox();
	void SetUp();
	void Render();
	void Release();
};

