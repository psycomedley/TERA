#pragma once
class cText
{
protected:
	LPD3DXFONT		m_pFont;
	E_FONT_TYPE		m_eFontType;
	SYNTHESIZE(string, m_sText, Text);
	float			m_fShowTime;
	float			m_fPassedTime;
	RECT			m_rect;
	bool			m_bRender;
	DWORD			m_dwFormat;
	ST_SIZE			m_stSize;
	D3DXVECTOR2		m_vPosition;
	D3DCOLOR		m_dwColor;

public:
	virtual void ResetTime();

public:
	virtual HRESULT Setup(E_FONT_TYPE eType, string sText, float fShowTime,
		D3DXVECTOR2 vPosition, ST_SIZE stSize,
		D3DCOLOR dwColor = XWHITE,
		DWORD dwFormat = DT_VCENTER | DT_CENTER | DT_WORDBREAK);

	virtual bool Update(float fPassedTime);
	virtual void Render();

public:
	cText();
	~cText();
};

