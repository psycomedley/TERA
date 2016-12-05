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
	fireFrameTimer = 0;
	fireFrameNumber = 0;

	startAttackEffect = false;
	attackFrameTimer = 0;

	fireEffectSetup();
	attackEffectSetup();
}

void cEffect::Update()
{
	fireFrameTimer++;
	if (fireFrameTimer > 5)
	{
		fireFrameNumber++;
		if (fireFrameNumber > 15)
		{
			fireFrameNumber = 0;
		}
		setFireFrame(fireFrameNumber);
		fireFrameTimer = 0;
	}
	if(KEYBOARD->IsOnceKeyDown(VK_SPACE))
	{
		startAttackEffect = true;
	}
	if (startAttackEffect)
	{
		attackEffectFrame();
	}
	attackFrameTimer++;
	if (attackFrameTimer > 5)
	{
		attackFrameTimer = 0;

	}
}

void cEffect::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);


	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);



/*
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000003);*/

	D3DXMATRIXA16 matFireWorld, matFireView;
	D3DXMatrixIdentity(&matFireWorld);

	g_pD3DDevice->SetTexture(0, GETSINGLE(cTextureMgr)->GetTexture("effect/fire.tga"));
	g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);
	g_pD3DDevice->GetTransform(D3DTS_VIEW, &matFireView);
	D3DXMatrixInverse(&matFireWorld, 0, &matFireView);
	matFireWorld._41 = 0;
	matFireWorld._42 = 0;
	matFireWorld._43 = 0;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matFireWorld);
	g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecVertex1[0], sizeof(ST_PCT_VERTEX));


	if (startAttackEffect)
	{

	}




	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);



}

void cEffect::setFireFrame(int fn)
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

void cEffect::attackEffectFrame()
{
	
}

void cEffect::fireEffectSetup()
{
	m_vecVertex1.resize(6);

	m_vecVertex1[0].p = D3DXVECTOR3(-10, -10, 0);
	m_vecVertex1[0].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex1[0].c = D3DCOLOR_ARGB(192, 255, 255, 255);

	m_vecVertex1[1].p = D3DXVECTOR3(-10, 10, 0);
	m_vecVertex1[1].t = D3DXVECTOR2(0, 0);
	m_vecVertex1[1].c = D3DCOLOR_ARGB(192, 255, 255, 255);

	m_vecVertex1[2].p = D3DXVECTOR3(10, 10, 0);
	m_vecVertex1[2].t = D3DXVECTOR2(0.25, 0);
	m_vecVertex1[2].c = D3DCOLOR_ARGB(192, 255, 255, 255);

	m_vecVertex1[3].p = D3DXVECTOR3(-10, -10, 0);
	m_vecVertex1[3].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex1[3].c = D3DCOLOR_ARGB(192, 255, 255, 255);

	m_vecVertex1[4].p = D3DXVECTOR3(10, 10, 0);
	m_vecVertex1[4].t = D3DXVECTOR2(0.25, 0);
	m_vecVertex1[4].c = D3DCOLOR_ARGB(192, 255, 255, 255);

	m_vecVertex1[5].p = D3DXVECTOR3(10, -10, 0);
	m_vecVertex1[5].t = D3DXVECTOR2(0.25, 0.25);
	m_vecVertex1[5].c = D3DCOLOR_ARGB(192, 255, 255, 255);
}

void cEffect::attackEffectSetup()
{
	m_vecVertex2.resize(6);

	m_vecVertex2[0].p = D3DXVECTOR3(-1, -1 , 0);
	m_vecVertex2[0].t = D3DXVECTOR2(0, 1);
	m_vecVertex2[0].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex2[1].p = D3DXVECTOR3(-1, 1, 0);
	m_vecVertex2[1].t = D3DXVECTOR2(0, 0);
	m_vecVertex2[1].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex2[2].p = D3DXVECTOR3(1, 1, 0);
	m_vecVertex2[2].t = D3DXVECTOR2(1, 0);
	m_vecVertex2[2].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex2[3].p = D3DXVECTOR3(-1, -1, 0);
	m_vecVertex2[3].t = D3DXVECTOR2(0, 1);
	m_vecVertex2[3].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex2[4].p = D3DXVECTOR3(1, 1, 0);
	m_vecVertex2[4].t = D3DXVECTOR2(1, 0);
	m_vecVertex2[4].c = D3DCOLOR_ARGB(255, 255, 255, 255);

	m_vecVertex2[5].p = D3DXVECTOR3(1, -1, 0);
	m_vecVertex2[5].t = D3DXVECTOR2(1, 1);
	m_vecVertex2[5].c = D3DCOLOR_ARGB(255, 255, 255, 255);
}
