#pragma once
#include "cText.h"

class cAlphaText : public cText
{
protected:
	int			m_nAlpha;
	int			m_nCurrentAlpha;
	float		m_fAlphaTime;
	float		m_fPassedAlphaTime;

	float		m_fDecreasePerSecond;
	float		m_fElapse;

	D3DXCOLOR	m_dwAlphaColor;

public:
	virtual void ResetTime();

public:
	virtual HRESULT Setup(E_FONT_TYPE eType, string sText, float fShowTime,
		D3DXVECTOR2 vPosition, ST_SIZE stSize,
		D3DCOLOR dwColor = XWHITE, int nAlpha = 255, float fAlphaTime = 0.0f,
		DWORD dwFormat = DT_VCENTER | DT_CENTER | DT_WORDBREAK);

	virtual bool Update(float fPassedTime);
	virtual void Render();

public:
	cAlphaText();
	~cAlphaText();
};

