#include "stdafx.h"
#include "cEffect.h"


cEffect::cEffect()
{
}


cEffect::~cEffect()
{
}

void cEffect::Setup()
{
	frameTimer = 0;
	frameNumber = 0;

	m_vecVertex1.resize(6);

	m_vecVertex1[0].p = D3DXVECTOR3(-10, -10, 0);
	m_vecVertex1[0].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex1[0].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex1[1].p = D3DXVECTOR3(-10, 10, 0);
	m_vecVertex1[1].t = D3DXVECTOR2(0, 0);
	m_vecVertex1[1].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex1[2].p = D3DXVECTOR3(10, 10, 0);
	m_vecVertex1[2].t = D3DXVECTOR2(0.25, 0);
	m_vecVertex1[2].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex1[3].p = D3DXVECTOR3(-10, -10, 0);
	m_vecVertex1[3].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex1[3].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex1[4].p = D3DXVECTOR3(10, 10, 0);
	m_vecVertex1[4].t = D3DXVECTOR2(0.25, 0);
	m_vecVertex1[4].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex1[5].p = D3DXVECTOR3(10, -10, 0);
	m_vecVertex1[5].t = D3DXVECTOR2(0.25, 0.25);
	m_vecVertex1[5].c = D3DCOLOR_ARGB(255, 255, 255, 255);


}

void cEffect::Update()
{
	frameTimer++;
	if (frameTimer > 5)
	{
		frameNumber++;
		if (frameNumber > 15)
		{
			frameNumber = 0;
		}
		setFrame(frameNumber);
		frameTimer = 0;
		frameNumber++;
	}
}

void cEffect::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000003);

	D3DXMATRIXA16 matWorld, matView;
	D3DXMatrixIdentity(&matWorld);

	g_pD3DDevice->SetTexture(0, GETSINGLE(cTextureMgr)->GetTexture("effect/fire.tga"));
	g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matWorld, 0, &matView);
	matWorld._41 = 0;
	matWorld._42 = 0;
	matWorld._43 = 0;

	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecVertex1[0], sizeof(ST_PCT_VERTEX));
}

void cEffect::setFrame(int fn)
{
	switch (fn)
	{
	case 0:
		m_vecVertex1[0].t = D3DXVECTOR2(0, 0.25);
		m_vecVertex1[1].t = D3DXVECTOR2(0, 0);
		m_vecVertex1[2].t = D3DXVECTOR2(0.25, 0);
		m_vecVertex1[3].t = D3DXVECTOR2(0, 0.25);
		m_vecVertex1[4].t = D3DXVECTOR2(0.25, 0);
		m_vecVertex1[5].t = D3DXVECTOR2(0.25, 0.25);
		break;
	case 1:
		m_vecVertex1[0].t = D3DXVECTOR2(0.25, 0.25);
		m_vecVertex1[1].t = D3DXVECTOR2(0.25, 0);
		m_vecVertex1[2].t = D3DXVECTOR2(0.5, 0);
		m_vecVertex1[3].t = D3DXVECTOR2(0.25, 0.25);
		m_vecVertex1[4].t = D3DXVECTOR2(0.5, 0);
		m_vecVertex1[5].t = D3DXVECTOR2(0.5, 0.25);
		break;
	case 2:
		m_vecVertex1[0].t = D3DXVECTOR2(0.5, 0.25);
		m_vecVertex1[1].t = D3DXVECTOR2(0.5, 0);
		m_vecVertex1[2].t = D3DXVECTOR2(0.75, 0);
		m_vecVertex1[3].t = D3DXVECTOR2(0.5, 0.25);
		m_vecVertex1[4].t = D3DXVECTOR2(0.75, 0);
		m_vecVertex1[5].t = D3DXVECTOR2(0.75, 0.25);
		break;
	case 3:
		m_vecVertex1[0].t = D3DXVECTOR2(0.75, 0.25);
		m_vecVertex1[1].t = D3DXVECTOR2(0.75, 0);
		m_vecVertex1[2].t = D3DXVECTOR2(1, 0);
		m_vecVertex1[3].t = D3DXVECTOR2(0.75, 0.25);
		m_vecVertex1[4].t = D3DXVECTOR2(1, 0);
		m_vecVertex1[5].t = D3DXVECTOR2(1, 0.25);
		break;

	case 4:
		m_vecVertex1[0].t = D3DXVECTOR2(0, 0.5);
		m_vecVertex1[1].t = D3DXVECTOR2(0, 0.25);
		m_vecVertex1[2].t = D3DXVECTOR2(0.25, 0.25);
		m_vecVertex1[3].t = D3DXVECTOR2(0, 0.5);
		m_vecVertex1[4].t = D3DXVECTOR2(0.25, 0.25);
		m_vecVertex1[5].t = D3DXVECTOR2(0.25, 0.5);
		break;
	case 5:
		m_vecVertex1[0].t = D3DXVECTOR2(0.25, 0.5);
		m_vecVertex1[1].t = D3DXVECTOR2(0.25, 0.25);
		m_vecVertex1[2].t = D3DXVECTOR2(0.5, 0.25);
		m_vecVertex1[3].t = D3DXVECTOR2(0.25, 0.5);
		m_vecVertex1[4].t = D3DXVECTOR2(0.5, 0.25);
		m_vecVertex1[5].t = D3DXVECTOR2(0.5, 0.5);
		break;
	case 6:
		m_vecVertex1[0].t = D3DXVECTOR2(0.5, 0.5);
		m_vecVertex1[1].t = D3DXVECTOR2(0.5, 0.25);
		m_vecVertex1[2].t = D3DXVECTOR2(0.75, 0.25);
		m_vecVertex1[3].t = D3DXVECTOR2(0.5, 0.5);
		m_vecVertex1[4].t = D3DXVECTOR2(0.75, 0.25);
		m_vecVertex1[5].t = D3DXVECTOR2(0.75, 0.5);
		break;
	case 7:
		m_vecVertex1[0].t = D3DXVECTOR2(0.75, 0.5);
		m_vecVertex1[1].t = D3DXVECTOR2(0.75, 0.25);
		m_vecVertex1[2].t = D3DXVECTOR2(1, 0.25);
		m_vecVertex1[3].t = D3DXVECTOR2(0.75, 0.5);
		m_vecVertex1[4].t = D3DXVECTOR2(1, 0.25);
		m_vecVertex1[5].t = D3DXVECTOR2(1, 0.5);
		break;

	case 8:
		m_vecVertex1[0].t = D3DXVECTOR2(0, 0.75);
		m_vecVertex1[1].t = D3DXVECTOR2(0, 0.5);
		m_vecVertex1[2].t = D3DXVECTOR2(0.25, 0.5);
		m_vecVertex1[3].t = D3DXVECTOR2(0, 0.75);
		m_vecVertex1[4].t = D3DXVECTOR2(0.25, 0.5);
		m_vecVertex1[5].t = D3DXVECTOR2(0.25, 0.75);
		break;
	case 9:
		m_vecVertex1[0].t = D3DXVECTOR2(0.25, 0.75);
		m_vecVertex1[1].t = D3DXVECTOR2(0.25, 0.5);
		m_vecVertex1[2].t = D3DXVECTOR2(0.5, 0.5);
		m_vecVertex1[3].t = D3DXVECTOR2(0.25, 0.75);
		m_vecVertex1[4].t = D3DXVECTOR2(0.5, 0.5);
		m_vecVertex1[5].t = D3DXVECTOR2(0.5, 0.75);
		break;
	case 10:
		m_vecVertex1[0].t = D3DXVECTOR2(0.5, 0.75);
		m_vecVertex1[1].t = D3DXVECTOR2(0.5, 0.5);
		m_vecVertex1[2].t = D3DXVECTOR2(0.75, 0.5);
		m_vecVertex1[3].t = D3DXVECTOR2(0.5, 0.75);
		m_vecVertex1[4].t = D3DXVECTOR2(0.75, 0.5);
		m_vecVertex1[5].t = D3DXVECTOR2(0.75, 0.75);
		break;
	case 11:
		m_vecVertex1[0].t = D3DXVECTOR2(0.75, 0.75);
		m_vecVertex1[1].t = D3DXVECTOR2(0.75, 0.5);
		m_vecVertex1[2].t = D3DXVECTOR2(1, 0.5);
		m_vecVertex1[3].t = D3DXVECTOR2(0.75, 0.75);
		m_vecVertex1[4].t = D3DXVECTOR2(1, 0.5);
		m_vecVertex1[5].t = D3DXVECTOR2(1, 0.75);
		break;

	case 12:
		m_vecVertex1[0].t = D3DXVECTOR2(0, 1);
		m_vecVertex1[1].t = D3DXVECTOR2(0, 0.75);
		m_vecVertex1[2].t = D3DXVECTOR2(0.25, 0.75);
		m_vecVertex1[3].t = D3DXVECTOR2(0, 1);
		m_vecVertex1[4].t = D3DXVECTOR2(0.25, 0.75);
		m_vecVertex1[5].t = D3DXVECTOR2(0.25, 1);
		break;
	case 13:
		m_vecVertex1[0].t = D3DXVECTOR2(0.25, 1);
		m_vecVertex1[1].t = D3DXVECTOR2(0.25, 0.75);
		m_vecVertex1[2].t = D3DXVECTOR2(0.5, 0.75);
		m_vecVertex1[3].t = D3DXVECTOR2(0.25, 1);
		m_vecVertex1[4].t = D3DXVECTOR2(0.5, 0.75);
		m_vecVertex1[5].t = D3DXVECTOR2(0.5, 1);
		break;
	case 14:
		m_vecVertex1[0].t = D3DXVECTOR2(0.5, 1);
		m_vecVertex1[1].t = D3DXVECTOR2(0.5, 0.75);
		m_vecVertex1[2].t = D3DXVECTOR2(0.75, 0.75);
		m_vecVertex1[3].t = D3DXVECTOR2(0.5, 1);
		m_vecVertex1[4].t = D3DXVECTOR2(0.75, 0.75);
		m_vecVertex1[5].t = D3DXVECTOR2(0.75, 1);
		break;
	case 15:
		m_vecVertex1[0].t = D3DXVECTOR2(0.75, 1);
		m_vecVertex1[1].t = D3DXVECTOR2(0.75, 0.75);
		m_vecVertex1[2].t = D3DXVECTOR2(1, 0.75);
		m_vecVertex1[3].t = D3DXVECTOR2(0.75, 1);
		m_vecVertex1[4].t = D3DXVECTOR2(1, 0.75);
		m_vecVertex1[5].t = D3DXVECTOR2(1, 1);
		break;





	}
}
