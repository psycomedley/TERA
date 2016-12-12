#pragma once
class cPlayer;
class cEffect
{
private:
	vector<ST_PCT_VERTEX>		m_vecVertex;
	LPDIRECT3DTEXTURE9			m_pTexture;

	LPD3DXEFFECT				m_pEffect;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;

	int							m_nFrame;
	float						m_fPassedTime;
	float						m_fNextTime;

	int							m_nMaxFrameX;
	int							m_nMaxFrameY;
	int							m_nMaxFrame;

	bool						m_bLoop;
	SYNTHESIZE(bool, m_bProcess, Process);

	//std::vector<ST_PCT_VERTEX> m_vecVertex1;	//fire
	//std::vector<ST_PCT_VERTEX> m_vecVertex2;	//attack


	//int fireFrameTimer;
	//int fireFrameNumber;
	//bool startAttackEffect;
	//int attackFrameTimer;
	//int attackFrameNumber;

public:
	void	Start();
	void	Stop();
	void	Pause();

public:
	HRESULT	Setup(string sPath, float fWidth, float fHeight,
		int nMaxFrameX, int nMaxFrameY, float fNextTime = 0.1f,
		bool bLoop = false, int nAlpha = 255, int nMaxFrame = 0);
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

