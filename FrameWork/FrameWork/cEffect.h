#pragma once
class cPlayer;
class cEffect
{
private:
	vector<ST_PCT_VERTEX>	m_vecVertex;
	LPDIRECT3DTEXTURE9		m_pTexture;

	int						m_nFrame;
	float					m_fPassedTime;
	float					m_fNextTime;

	int						m_nMaxFrameX;
	int						m_nMaxFrameY;

	//std::vector<ST_PCT_VERTEX> m_vecVertex1;	//fire
	//std::vector<ST_PCT_VERTEX> m_vecVertex2;	//attack


	//int fireFrameTimer;
	//int fireFrameNumber;
	//bool startAttackEffect;
	//int attackFrameTimer;
	//int attackFrameNumber;

public:
//	void	Start();

public:
	HRESULT	Setup(string sPath, float fWidth, float fHeight, int nAlpha, int nMaxFrameX, int nMaxFrameY);
	void	Update();
	void	Render();

	void	UpdateUV();

public:
	cEffect();
	~cEffect();
//	void setFireFrame(int fn);
//	void attackEffectFrame();
//	void fireEffectSetup();
//	void attackEffectSetup();
};

