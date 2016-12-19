#include "stdafx.h"
#include "cAlphaText.h"


cAlphaText::cAlphaText()
	: m_nAlpha(255)
	, m_nCurrentAlpha(255)
	, m_fAlphaTime(0.0f)
	, m_fPassedAlphaTime(0.0f)
	, m_fDecreasePerSecond(0.0f)
	, m_fElapse(0.0f)
{
}


cAlphaText::~cAlphaText()
{
}


HRESULT cAlphaText::Setup(E_FONT_TYPE eType, string sKey, string sText, float fShowTime,
	D3DXVECTOR2 vPosition, ST_SIZE stSize,
	D3DCOLOR dwColor /*= XWHITE*/,
	int nOption /*= TEXT_NONE*/, int nAlpha /*= 255*/, float fAlphaTime /*= 0.0f*/,
	DWORD dwFormat /*= DT_VCENTER | DT_CENTER | DT_WORDBREAK*/)
{
//	cText::Setup(eType, sKey, sText, fShowTime, vPosition, stSize, dwColor, nOption, dwFormat);

	m_nAlpha = nAlpha;
	m_nCurrentAlpha = m_nAlpha;
	m_dwAlphaColor = ((nAlpha)& 0xff << 24) | dwColor;

	m_fAlphaTime = fAlphaTime;
	m_fPassedAlphaTime = 0.0f;

	if (m_fAlphaTime != 0)
		m_fDecreasePerSecond = 1 / m_fAlphaTime;
	else
		m_fDecreasePerSecond = 0.0f;

	m_fElapse = 0.0f;

	return S_OK;
}


void cAlphaText::Update(float fPassedTime)
{
	m_fPassedTime += fPassedTime;
	if (m_fPassedTime >= m_fShowTime)
	{
		if (m_fPassedAlphaTime >= m_fAlphaTime)
			m_bProcess = false;
		else
		{
//			m_dwAlphaColor = ((m_nAlpha)& 0xff << 24) | m_dwColor;
			m_fPassedAlphaTime += fPassedTime;
			m_dwAlphaColor.a -= m_fDecreasePerSecond * fPassedTime;
		}
	}
}


void cAlphaText::Render()
{
	m_pFont->DrawText(NULL,
		m_sText.c_str(),
		m_sText.size(),
		&m_rect,
		m_dwFormat,
		m_dwAlphaColor);
}


void cAlphaText::ResetTime()
{
	m_nCurrentAlpha = m_nAlpha;
	m_fPassedTime = 0.0f;
	m_fPassedAlphaTime = 0.0f;
	m_dwAlphaColor.a = (float)m_nAlpha / 255;
	m_bProcess = false;
}
