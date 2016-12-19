#include "stdafx.h"
#include "cText.h"


cText::cText()
	: m_pFont(NULL)
	, m_fShowTime(0.0f)
	, m_fPassedTime(0.0f)
	, m_dwFormat(DT_VCENTER | DT_CENTER | DT_WORDBREAK)
	, m_stSize(0, 0)
	, m_nOption(TEXT_NONE)
	, m_fElapseX(0.0f)
	, m_fElapseY(0.0f)
	, m_nAlpha(255)
	, m_nCurrentAlpha(255)
	, m_fPassedAlphaTime(0.0f)
	, m_fDecreasePerSecond(0.0f)
	, m_fAlphaTime(0.0f)
	, m_dwColor(XWHITE)
	, m_vPosition(0, 0)
	, m_sText("")
	, m_sKey("")
	, m_bProcess(false)
	, m_fMoveSpeed(0.0f)
{
}


cText::cText(cText* pText)
{
	m_pFont = pText->m_pFont;
	m_eFontType = pText->m_eFontType;
	m_fShowTime = pText->m_fShowTime;
	m_fPassedTime = 0.0f;
	m_rect = pText->m_rect;
	m_dwFormat = pText->m_dwFormat;
	m_stSize = pText->m_stSize;
	m_nOption = pText->m_nOption;
	m_fElapseX = 0.0f;
	m_fElapseY = 0.0f;
	m_nAlpha = pText->m_nAlpha;
	m_nCurrentAlpha = m_nAlpha;
	m_fPassedAlphaTime = 0.0f;
	m_fDecreasePerSecond = pText->m_fDecreasePerSecond;
	m_fPassedMoveTime = 0.0f;

	m_fAlphaTime = pText->m_fAlphaTime;
	m_dwColor = pText->m_dwColor;
	m_vPosition = pText->m_vPosition;
	m_sText = pText->m_sText;
	m_sKey = pText->m_sKey;
	m_bProcess = false;
	m_fMoveSpeed = pText->m_fMoveSpeed;
	m_fMoveTime = pText->m_fMoveTime;
}


cText::~cText()
{
}


//HRESULT cText::Setup(E_FONT_TYPE eType, string sKey, string sText, float fShowTime,
//	D3DXVECTOR2 vPosition, ST_SIZE stSize,
//	D3DCOLOR dwColor /*= XWHITE*/,
//	int nOption /*= TEXT_NONE*/,
//	DWORD dwFormat /*= DT_VCENTER | DT_CENTER | DT_WORDBREAK*/)
//{
//	m_pFont = GETSINGLE(cFontMgr)->GetFont(eType);
//	m_eFontType = eType;
//	m_sKey = sKey;
//	m_sText = sText;
//	m_fShowTime = fShowTime;
//	m_vPosition = vPosition;
//	m_stSize = stSize;
//	m_dwColor = dwColor;
//	m_nOption = nOption;
//	m_dwFormat = dwFormat;
//	m_fPassedTime = 0.0f;
//
//	m_rect = RectMakeCenter(vPosition.x, vPosition.y, stSize.fWidth, stSize.fHeight);
//	m_renderRect = m_rect;
//
//	return S_OK;
//}


HRESULT cText::Setup(E_FONT_TYPE eType, string sKey, string sText,
	D3DXVECTOR2 vPosition, ST_SIZE stSize,
	D3DCOLOR dwColor /*= XWHITE*/, int nOption /*= TEXT_NONE*/,
	DWORD dwFormat /*= DT_VCENTER | DT_CENTER | DT_WORDBREAK*/)
{
	m_pFont = GETSINGLE(cFontMgr)->GetFont(eType);
	m_eFontType = eType;
	m_sKey = sKey;
	m_sText = sText;
	m_vPosition = vPosition;
	m_stSize = stSize;
	m_dwColor = dwColor;
	m_nOption = nOption;
	m_dwFormat = dwFormat;

	m_rect = RectMakeCenter(vPosition.x, vPosition.y, stSize.fWidth, stSize.fHeight);

	return S_OK;
}


void cText::Update(float fPassedTime)
{
	if (m_bProcess)
	{
		if (m_nOption & TEXT_SHOWTIME)
		{
			m_fPassedTime += fPassedTime;

			if ((m_nOption & TEXT_ALPHA))
			{
				if (m_fPassedTime >= m_fShowTime)
				{
					if (m_fPassedAlphaTime >= m_fAlphaTime)
						m_bProcess = false;
					else
					{
						m_fPassedAlphaTime += fPassedTime;
						m_dwColor.a -= m_fDecreasePerSecond * fPassedTime;
					}
				}
			}
			else
			{
				if (m_fPassedTime >= m_fShowTime)
					m_bProcess = false;
			}
		}
		else
		{
			if (m_nOption & TEXT_ALPHA)
			{
				m_fPassedAlphaTime += fPassedTime;
				if (m_fPassedAlphaTime >= m_fAlphaTime)
					m_bProcess = false;
				else
				{
					m_fPassedAlphaTime += fPassedTime;
					m_dwColor.a -= m_fDecreasePerSecond * fPassedTime;
				}
			}
		}
		if (m_nOption & TEXT_MOVE)
		{
			if (m_nOption & TEXT_MOVEAFTERTIME)
			{
				m_fPassedMoveTime += fPassedTime;
				if (m_fPassedMoveTime >= m_fMoveTime)
					Move();
			}
			else
				Move();
		}
	}
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
	m_fElapseX = 0.0f;
	m_fElapseY = 0.0f;
	m_bProcess = false;
	m_rect = RectMakeCenter(m_vPosition.x, m_vPosition.y, m_stSize.fWidth, m_stSize.fHeight);
}


void cText::Move()
{
	if (m_nDirection & DIRECTION_LEFT)
		m_fElapseX -= m_fMoveSpeed;
	if (m_nDirection & DIRECTION_RIGHT)
		m_fElapseX += m_fMoveSpeed;
	if (m_nDirection & DIRECTION_UP)
		m_fElapseY -= m_fMoveSpeed;
	if (m_nDirection & DIRECTION_DOWN)
		m_fElapseY += m_fMoveSpeed;

	m_rect.left += (int)m_fElapseX;
	m_rect.right += (int)m_fElapseX;
	m_rect.bottom += (int)m_fElapseY;
	m_rect.top += (int)m_fElapseY;
	m_fElapseX -= (int)m_fElapseX;
	m_fElapseY -= (int)m_fElapseY;
}


void cText::SetAlphaTime(float fAlphaTime)
{
	m_fAlphaTime = fAlphaTime;

	if (m_fAlphaTime != 0)
		m_fDecreasePerSecond = 1 / m_fAlphaTime;
	else
		m_fDecreasePerSecond = 0.0f;
}