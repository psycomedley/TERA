#include "stdafx.h"
#include "cUITextView.h"


cUITextView::cUITextView()
	: pFont(NULL)
	, m_dwFormat(DT_VCENTER | DT_CENTER | DT_WORDBREAK)
	, m_dwColor(D3DCOLOR_XRGB(255, 255, 255))
{
}


cUITextView::~cUITextView()
{
}


void cUITextView::Render()
{
	RECT rc;
	SetRect(&rc,
		m_matWorld._41,
		m_matWorld._42,
		m_matWorld._41 + m_stSize.fWidth,
		m_matWorld._42 + m_stSize.fHeight);

	pFont->DrawText(NULL,
		m_sText.c_str(),
		m_sText.length(),
		&rc,
		m_dwFormat,
		m_dwColor);

	cUIObject::Render();
}


void cUITextView::Release()
{
	SAFE_RELEASE(pFont);
}