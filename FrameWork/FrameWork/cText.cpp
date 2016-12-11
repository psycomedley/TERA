#include "stdafx.h"
#include "cText.h"


cText::cText()
	: m_pFont(NULL)
	, m_sText("")
	, m_fShowTime(0.0f)
	, m_fPassedTime(0.0f)
	, m_bRender(false)
	, m_dwFormat(DT_VCENTER | DT_CENTER | DT_WORDBREAK)
	, m_stSize(0, 0)
	, m_vPosition(0, 0)
	, m_dwColor(XWHITE)
{
}


cText::~cText()
{
}


HRESULT cText::Setup(E_FONT_TYPE eType, string sText, float fShowTime,
	D3DXVECTOR2 vPosition, ST_SIZE stSize,
	D3DCOLOR dwColor /*= XWHITE*/,
	DWORD dwFormat /*= DT_VCENTER | DT_CENTER | DT_WORDBREAK*/)
{
	m_pFont = GETSINGLE(cFontMgr)->GetFont(eType);
	m_eFontType = eType;
	m_sText = sText;
	m_fShowTime = fShowTime;
	m_vPosition = vPosition;
	m_stSize = stSize;
	m_dwFormat = dwFormat;
	m_fPassedTime = 0.0f;

	m_rect = RectMakeCenter(vPosition.x, vPosition.y, stSize.fWidth, stSize.fHeight);

	return S_OK;
}


bool cText::Update(float fPassedTime)
{
	m_fPassedTime += fPassedTime;
	if (m_fPassedTime >= m_fShowTime)
		return true;
	return false;
}


void cText::Render()
{
	m_pFont->DrawTextA(NULL,
		m_sText.c_str(),
		m_sText.size(),
		&m_rect,
		m_dwFormat,
		m_dwColor);
}


void cText::ResetTime()
{
	m_fPassedTime = 0.0f;
}