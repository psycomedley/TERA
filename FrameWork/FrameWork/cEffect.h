#pragma once
class cPlayer;
class cEffect
{
private:
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

	int							m_nOffsetX;
	int							m_nOffsetY;
	float						m_fRatioX;
	float						m_fRatioY;

	int							m_nOption;

	int							m_nCurrentFrame;
	float						m_fPassedTime;
	SYNTHESIZE(float, m_fNextTime, NextTime);
	SYNTHESIZE(float, m_fRemoveTime, RemoveTime);
	float						m_fRemovePassedTime;

	SYNTHESIZE(E_EFFECT_TECHNIQUE, m_eTechnique, Technique);

	SYNTHESIZE(float, m_fAngle, Angle);
	SYNTHESIZE(float, m_fAlpha, Alpha);

	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matRotation, MatRotation);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matScale, MatScale);

	SYNTHESIZE(bool, m_bLoop, Loop);
	SYNTHESIZE(bool, m_bEnd, End);
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

	void	SetTexture(string sKey, E_EFFECT_TEXTURE eTex);
	void	SetTotalFrame(int nFrameX, int nFrameY, int nTotalFrame);

public:
	HRESULT	Setup(float fWidth, float fHeight, float fAlpha = 1.0f,
		int nOption = EFFECT_BILLBOARING | EFFECT_ALPHABLEND);
	HRESULT	Setup(string sPath, float fWidth, float fHeight,
		int nMaxFrameX = 1, int nMaxFrameY = 1, float fNextTime = 0.1f,
		bool bLoop = false, float fAlpha = 1.0f, int nMaxFrame = 0);
	void	Update();
	void	Render();

	void	UpdateUV();

public:
	cEffect();
	~cEffect();

protected:
	void Setting();
	void SetTech(E_EFFECT_TECHNIQUE eTech);
	//	void setFireFrame(int fn);
//	void attackEffectFrame();
//	void fireEffectSetup();
//	void attackEffectSetup();
};