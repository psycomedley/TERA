#include "stdafx.h"
#include "cUIButton.h"


cUIButton::cUIButton()
	: m_eBtnState(BTN_NORMAL)
{
}


cUIButton::~cUIButton()
{
	/*for (int i = 0; i < 3; ++i)
		SAFE_RELEASE(m_aTexture[i]);*/
}


void cUIButton::SetTexture(string sNormal, string sMouseOver, string sDown)
{
	D3DXIMAGE_INFO info;
	m_aTexture[BTN_NORMAL] = GETSINGLE(cTextureMgr)->GetTexture(sNormal, &info);
	m_stSize.fWidth = info.Width;
	m_stSize.fHeight = info.Height;

	m_aTexture[BTN_MOUSEOVER] = GETSINGLE(cTextureMgr)->GetTexture(sMouseOver, &info);
	m_aTexture[BTN_DOWN] = GETSINGLE(cTextureMgr)->GetTexture(sDown, &info);
}


void cUIButton::Update(D3DXMATRIXA16* pParent)
{
	POINT ptPosition;
	GetCursorPos(&ptPosition);
	ScreenToClient(g_hWnd, &ptPosition);

	RECT rc;
	SetRect(&rc,
		m_matWorld._41,
		m_matWorld._42,
		m_matWorld._41 + m_stSize.fWidth,
		m_matWorld._42 + m_stSize.fHeight);

	if (PtInRect(&rc, ptPosition))
	{
		if (GetKeyState(VK_LBUTTON) & 0x8000)
		{
			if (m_eBtnState == BTN_MOUSEOVER)
			{
				m_eBtnState = BTN_DOWN;
			}
		}
		else
		{
			if (m_eBtnState == BTN_DOWN)
			{
				// 클릭
				if (m_pDelegate)
				{
					m_pDelegate->OnClick(this);
				}
			}
			m_eBtnState = BTN_MOUSEOVER;
		}
	}
	else
	{
		m_eBtnState = BTN_NORMAL;
	}

	cUIObject::Update(pParent);
}


void cUIButton::Render()
{
	RECT rc;
	SetRect(&rc, 0, 0, m_stSize.fWidth, m_stSize.fHeight); //이미지 크기만큼 그려 줌

	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND | D3DXSPRITE_SORT_TEXTURE);
	m_pSprite->SetTransform(&m_matWorld);
	m_pSprite->Draw(
		m_aTexture[m_eBtnState],
		&rc,
		&D3DXVECTOR3(0, 0, 0),
		&D3DXVECTOR3(0, 0, 0),
		D3DCOLOR_XRGB(255, 255, 255)
		);
	m_pSprite->End();

	cUIObject::Render();
}