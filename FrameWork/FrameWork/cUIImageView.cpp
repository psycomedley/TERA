#include "stdafx.h"
#include "cUIImageView.h"


cUIImageView::cUIImageView()
	: m_pTexture(NULL)
	, m_nFrameX(1)
	, m_nFrameY(1)
	, m_nCurrentFrame(0)
{
}


cUIImageView::~cUIImageView()
{
	SAFE_RELEASE(m_pTexture);
}


void cUIImageView::SetTexture(string sKey, int nFrameX, int nFrameY)
{
	D3DXIMAGE_INFO info;
	m_pTexture = GETSINGLE(cTextureMgr)->GetTexture(sKey, &info);
	m_stSize.fWidth = info.Width;
	m_stSize.fHeight = info.Height;

	m_nFrameX = nFrameX;
	m_nFrameY = nFrameY;

	m_nFrameWidth = m_stSize.fWidth / nFrameX;
	m_nFrameHeight = m_stSize.fHeight / nFrameY;

	m_rect = RectMake(0, 0, m_nFrameWidth, m_nFrameHeight);
}


void cUIImageView::Render()
{
//	RECT rc;
//	SetRect(&rc, 0, 0, m_stSize.fWidth, m_stSize.fHeight); //이미지의 크기만한 박스를 만듬

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&m_matWorld);
	m_pSprite->Draw(
		m_pTexture,
		&m_rect,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255));
	m_pSprite->End();

	cUIObject::Render();
}


void cUIImageView::SetCenterPosition(D3DXVECTOR3 vPosition)
{
	m_vPosition = vPosition;
	m_vPosition.x -= m_nFrameWidth / 2;
	m_vPosition.y -= m_nFrameHeight / 2;
}


void cUIImageView::SetCurrentFrame(int nFrame)
{
	m_nCurrentFrame = nFrame;
	m_nFramePosX = m_nFrameWidth * (m_nCurrentFrame % m_nFrameX);
	m_nFramePosY = m_nFrameHeight * (m_nCurrentFrame / m_nFrameX);

	m_rect = RectMake(m_nFramePosX, m_nFramePosY, m_nFrameWidth, m_nFrameHeight);
}