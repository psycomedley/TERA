#pragma once
class cSkyBox
{
private:
	vector<ST_PT_VERTEX>		m_vecVertax;

	LPDIRECT3DTEXTURE9			m_pTexture[6];
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
public:
	cSkyBox();
	~cSkyBox();
	void SetUp();
	void Render();
	void Release();
};

