#pragma once
class cPlayer;
class cEffect
{
protected:
	SYNTHESIZE(string, m_sName, Name);
	vector<ST_PCT_VERTEX>		m_vecVertex;
	LPDIRECT3DTEXTURE9			m_pTexture;
	LPDIRECT3DTEXTURE9			m_pTexture2;
	LPDIRECT3DTEXTURE9			m_pTexture3;
	LPDIRECT3DTEXTURE9			m_pBumpMap;

	LPD3DXEFFECT				m_pEffect;
	LPDIRECT3DVERTEXBUFFER9		m_pVB;

	int							m_nMaxFrameX;
	int							m_nMaxFrameY;
	int							m_nMaxFrame;
	int							m_nCurrentFrame;

	int							m_nOffsetX;
	int							m_nOffsetY;
	float						m_fRatioX;
	float						m_fRatioY;

	int							m_nOption;

	float						m_fPassedTime;
	SYNTHESIZE(float, m_fNextTime, NextTime);
	SYNTHESIZE(float, m_fRemoveTime, RemoveTime);
	float						m_fRemovePassedTime;

	SYNTHESIZE(E_EFFECT_TECHNIQUE, m_eTechnique, Technique);
	SYNTHESIZE(E_EFFECT_TECHNIQUE, m_eNextTechnique, NextTechnique);

	SYNTHESIZE(float, m_fAngle, Angle);
	SYNTHESIZE(float, m_fAlpha, Alpha);

	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matRotation, MatRotation);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matScale, MatScale);

	SYNTHESIZE(bool, m_bLoop, Loop);
	SYNTHESIZE(int, m_nLoopTimes, LoopTimes);
	SYNTHESIZE(int, m_nLeftLoopTimes, LeftLoopTimes);
	SYNTHESIZE(bool, m_bEnd, End);
	SYNTHESIZE(bool, m_bProcess, Process);

protected:
	float m_fWidth;
	float m_fHeight;

	//std::vector<ST_PCT_VERTEX> m_vecVertex1;	//fire
	//std::vector<ST_PCT_VERTEX> m_vecVertex2;	//attack


	//int fireFrameTimer;
	//int fireFrameNumber;
	//bool startAttackEffect;
	//int attackFrameTimer;
	//int attackFrameNumber;

public:
	int GetMaxFrame() { return m_nMaxFrame; }
	int GetCurrentFrame() { return m_nCurrentFrame; }

	void SetCurrentFrame(int nFrame);

public:
	virtual void Start();
	virtual void Stop();
	void	Pause();

	void	SetTexture(string sKey, E_EFFECT_TEXTURE eTex);
	void	SetTotalFrame(int nFrameX, int nFrameY, int nTotalFrame);

public:
	HRESULT	Setup(float fWidth, float fHeight, float fAlpha = 1.0f,
		int nOption = EFFECT_BILLBOARING | EFFECT_ALPHABLEND);
	HRESULT	Setup(string sPath, float fWidth, float fHeight,
		int nMaxFrameX = 1, int nMaxFrameY = 1, float fNextTime = 0.1f,
		bool bLoop = false, float fAlpha = 1.0f, int nMaxFrame = 0);
	virtual void Update();
	virtual void Render();
	virtual void Release();

	void	UpdateUV();

public:
	cEffect();
	cEffect(cEffect* pEffect);
	~cEffect();

protected:
	void Setting();
	void SetTech(E_EFFECT_TECHNIQUE eTech);
	//	void setFireFrame(int fn);
//	void attackEffectFrame();
//	void fireEffectSetup();
//	void attackEffectSetup();
};