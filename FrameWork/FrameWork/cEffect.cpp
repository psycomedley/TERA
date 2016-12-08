#include "stdafx.h"
#include "cEffect.h"
#include "cPlayer.h"


cEffect::cEffect()
	: m_nFrame(0)
	, m_fPassedTime(0.0f)
	, m_fNextTime(0.1f)
	, m_nMaxFrameX(0)
	, m_nMaxFrameY(0)
	, m_nMaxFrame(0)
	, m_bLoop(false)
	, m_bProcess(false)
{
}


cEffect::~cEffect()
{
}


HRESULT cEffect::Setup(string sPath, float fWidth, float fHeight,
	int nMaxFrameX, int nMaxFrameY, float fNextTime /*= 0.1f*/,
	bool bLoop /*= false*/, int nAlpha /*= 255*/, int nMaxFrame /*= 0*/)
{
	m_vecVertex.resize(6);
	m_fNextTime = fNextTime;

	m_pTexture = GETSINGLE(cTextureMgr)->GetTexture(sPath);
	m_bLoop = bLoop;

	float fHalfWidth = fWidth / 2;
	float fHalfHeight = fHeight / 2;

	m_nMaxFrameX = nMaxFrameX;
	m_nMaxFrameY = nMaxFrameY;
	if (nMaxFrame == 0)
		m_nMaxFrame = m_nMaxFrameX * m_nMaxFrameY;
	else
		m_nMaxFrame = nMaxFrame;

	m_vecVertex[0].p = D3DXVECTOR3(-fHalfWidth, -fHalfHeight, 0);
	m_vecVertex[0].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex[0].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[1].p = D3DXVECTOR3(-fHalfWidth, fHalfHeight, 0);
	m_vecVertex[1].t = D3DXVECTOR2(0, 0);
	m_vecVertex[1].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[2].p = D3DXVECTOR3(fHalfWidth, fHalfHeight, 0);
	m_vecVertex[2].t = D3DXVECTOR2(0.25, 0);
	m_vecVertex[2].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[3].p = D3DXVECTOR3(-fHalfWidth, -fHalfHeight, 0);
	m_vecVertex[3].t = D3DXVECTOR2(0, 0.25);
	m_vecVertex[3].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[4].p = D3DXVECTOR3(fHalfWidth, fHalfHeight, 0);
	m_vecVertex[4].t = D3DXVECTOR2(0.25, 0);
	m_vecVertex[4].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[5].p = D3DXVECTOR3(fHalfWidth, -fHalfHeight, 0);
	m_vecVertex[5].t = D3DXVECTOR2(0.25, 0.25);
	m_vecVertex[5].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	return S_OK;




	/*fireFrameTimer = 0;
	fireFrameNumber = 0;

	startAttackEffect = false;
	attackFrameTimer = 0;
	attackFrameNumber = 0;*/

//	fireEffectSetup();
//	attackEffectSetup();
}


void cEffect::Update()
{
	if (m_bProcess)
	{
		m_fPassedTime += GETSINGLE(cTimeMgr)->getElapsedTime();

		if (m_fPassedTime >= m_fNextTime)
		{
			m_fPassedTime -= m_fNextTime;
			(++m_nFrame) % m_nFrame;
			UpdateUV();
			if (m_nFrame > m_nMaxFrame && !m_bLoop)
				Stop();
		}
	}
	/*fireFrameTimer++;
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
	if (KEYBOARD->IsOnceKeyDown(DIK_E))
	{
		startAttackEffect = true;
	}
	if (startAttackEffect)
	{
		attackEffectFrame();
	}*/
}


void cEffect::Render()
{
	if (m_bProcess)
	{
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

		g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
		g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);

		D3DXMATRIXA16 matWorld, matView;
		D3DXMatrixIdentity(&matWorld);

		g_pD3DDevice->SetTexture(0, m_pTexture);
		g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		D3DXMatrixInverse(&matWorld, 0, &matView);
		matWorld._41 = 0;
		matWorld._42 = 0;
		matWorld._43 = 0;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecVertex[0], sizeof(ST_PCT_VERTEX));

		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	}

	/*
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000003);*/

	//D3DXMATRIXA16 matFireWorld, matFireView;
	//D3DXMatrixIdentity(&matFireWorld);

	//g_pD3DDevice->SetTexture(0, GETSINGLE(cTextureMgr)->GetTexture("effect/fire.tga"));
	//g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);
	//g_pD3DDevice->GetTransform(D3DTS_VIEW, &matFireView);
	//D3DXMatrixInverse(&matFireWorld, 0, &matFireView);
	//matFireWorld._41 = 0;
	//matFireWorld._42 = 0;
	//matFireWorld._43 = 0;
	//g_pD3DDevice->SetTransform(D3DTS_WORLD, &matFireWorld);
	//g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecVertex1[0], sizeof(ST_PCT_VERTEX));


	/*if (startAttackEffect)
	{
		D3DXMATRIXA16 matAttackWorld, matAttackView;
		D3DXMatrixIdentity(&matAttackWorld);

		g_pD3DDevice->SetTexture(0, GETSINGLE(cTextureMgr)->GetTexture("effect/attack2.tga"));
		g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matAttackView);
		D3DXMatrixInverse(&matAttackWorld, 0, &matAttackView);
		matAttackWorld._41 = 0;
		matAttackWorld._42 = 0;
		matAttackWorld._43 = 0;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matAttackWorld);
		g_pD3DDevice->DrawPrimitiveUP(D3DPT_TRIANGLELIST, 2, &m_vecVertex2[0], sizeof(ST_PCT_VERTEX));
	}

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);*/
}


void cEffect::UpdateUV()
{
	int nX = m_nFrame % m_nMaxFrameX;
	int nY = m_nFrame / m_nMaxFrameY;
	float fRatioX = 1 / (float)m_nMaxFrameX;
	float fRatioY = 1 / (float)m_nMaxFrameY;

	// 1��2  4
	// | / / |
	// 0  3��5
	
	m_vecVertex[0].t = D3DXVECTOR2(fRatioX * nX, fRatioY * (nY + 1));
	m_vecVertex[1].t = D3DXVECTOR2(fRatioX * nX, fRatioY * nY);
	m_vecVertex[2].t = D3DXVECTOR2(fRatioX * (nX + 1), fRatioY * nY);
	m_vecVertex[3].t = D3DXVECTOR2(fRatioX * nX, fRatioY * (nY + 1));
	m_vecVertex[4].t = D3DXVECTOR2(fRatioX * (nX + 1), fRatioY * nY);
	m_vecVertex[5].t = D3DXVECTOR2(fRatioX * (nX + 1), fRatioY * (nY + 1));
}


void cEffect::Start()
{
	m_bProcess = true;
}


void cEffect::Stop()
{
	m_bProcess = false;
	m_fPassedTime = 0.0f;
	m_nFrame = 0;
}


void cEffect::Pause()
{
	m_bProcess = false;
}

//
//void cEffect::attackEffectFrame()
//{
//	attackFrameTimer++;
//	if (attackFrameTimer > 3)
//	{
//		attackFrameTimer = 0;
//		attackFrameNumber++;
//		if (attackFrameNumber > 3)
//		{
//			attackFrameNumber = 0;
//			//m_vecVertex2[0].p.x = -1;
//			//m_vecVertex2[1].p.x = -1;
//			//m_vecVertex2[2].p.x = 1;
//			//m_vecVertex2[3].p.x = -1;
//			//m_vecVertex2[4].p.x = 1;
//			//m_vecVertex2[5].p.x = 1;
//			//m_vecVertex2[0].p.y = -1;
//			//m_vecVertex2[1].p.y = 1;
//			//m_vecVertex2[2].p.y = 1;
//			//m_vecVertex2[3].p.y = -1;
//			//m_vecVertex2[4].p.y = 1;
//			//m_vecVertex2[5].p.y = -1;
//
//			m_vecVertex2[0].p.x = 0;
//			m_vecVertex2[1].p.x = 0;
//			m_vecVertex2[2].p.x = 0;
//			m_vecVertex2[3].p.x = 0;
//			m_vecVertex2[4].p.x = 0;
//			m_vecVertex2[5].p.x = 0;
//			m_vecVertex2[0].p.y = 0;
//			m_vecVertex2[1].p.y = 0;
//			m_vecVertex2[2].p.y = 0;
//			m_vecVertex2[3].p.y = 0;
//			m_vecVertex2[4].p.y = 0;
//			m_vecVertex2[5].p.y = 0;
//			startAttackEffect = false;
//		}
//		m_vecVertex2[0].p.x -= 1;
//		m_vecVertex2[1].p.x -= 1;
//		m_vecVertex2[2].p.x += 1;
//		m_vecVertex2[3].p.x -= 1;
//		m_vecVertex2[4].p.x += 1;
//		m_vecVertex2[5].p.x += 1;
//		m_vecVertex2[0].p.y -= 1;
//		m_vecVertex2[1].p.y += 1;
//		m_vecVertex2[2].p.y += 1;
//		m_vecVertex2[3].p.y -= 1;
//		m_vecVertex2[4].p.y += 1;
//		m_vecVertex2[5].p.y -= 1;
//	}
//
//
//
//}
//
//
//void cEffect::fireEffectSetup()
//{
//	m_vecVertex1.resize(6);
//
//	m_vecVertex1[0].p = D3DXVECTOR3(-10, -10, 0);
//	m_vecVertex1[0].t = D3DXVECTOR2(0, 0.25);
//	m_vecVertex1[0].c = D3DCOLOR_ARGB(192, 255, 255, 255);
//
//	m_vecVertex1[1].p = D3DXVECTOR3(-10, 10, 0);
//	m_vecVertex1[1].t = D3DXVECTOR2(0, 0);
//	m_vecVertex1[1].c = D3DCOLOR_ARGB(192, 255, 255, 255);
//
//	m_vecVertex1[2].p = D3DXVECTOR3(10, 10, 0);
//	m_vecVertex1[2].t = D3DXVECTOR2(0.25, 0);
//	m_vecVertex1[2].c = D3DCOLOR_ARGB(192, 255, 255, 255);
//
//	m_vecVertex1[3].p = D3DXVECTOR3(-10, -10, 0);
//	m_vecVertex1[3].t = D3DXVECTOR2(0, 0.25);
//	m_vecVertex1[3].c = D3DCOLOR_ARGB(192, 255, 255, 255);
//
//	m_vecVertex1[4].p = D3DXVECTOR3(10, 10, 0);
//	m_vecVertex1[4].t = D3DXVECTOR2(0.25, 0);
//	m_vecVertex1[4].c = D3DCOLOR_ARGB(192, 255, 255, 255);
//
//	m_vecVertex1[5].p = D3DXVECTOR3(10, -10, 0);
//	m_vecVertex1[5].t = D3DXVECTOR2(0.25, 0.25);
//	m_vecVertex1[5].c = D3DCOLOR_ARGB(192, 255, 255, 255);
//}
//
//
//void cEffect::attackEffectSetup()
//{
//	m_vecVertex2.resize(6);
//
//	m_vecVertex2[0].p = D3DXVECTOR3(0, 0, 0);
//	m_vecVertex2[0].t = D3DXVECTOR2(0, 1);
//	m_vecVertex2[0].c = D3DCOLOR_ARGB(255, 255, 255, 255);
//
//	m_vecVertex2[1].p = D3DXVECTOR3(0, 0, 0);
//	m_vecVertex2[1].t = D3DXVECTOR2(0, 0);
//	m_vecVertex2[1].c = D3DCOLOR_ARGB(255, 255, 255, 255);
//
//	m_vecVertex2[2].p = D3DXVECTOR3(0, 0, 0);
//	m_vecVertex2[2].t = D3DXVECTOR2(1, 0);
//	m_vecVertex2[2].c = D3DCOLOR_ARGB(255, 255, 255, 255);
//
//	m_vecVertex2[3].p = D3DXVECTOR3(0, 0, 0);
//	m_vecVertex2[3].t = D3DXVECTOR2(0, 1);
//	m_vecVertex2[3].c = D3DCOLOR_ARGB(255, 255, 255, 255);
//
//	m_vecVertex2[4].p = D3DXVECTOR3(0, 0, 0);
//	m_vecVertex2[4].t = D3DXVECTOR2(1, 0);
//	m_vecVertex2[4].c = D3DCOLOR_ARGB(255, 255, 255, 255);
//
//	m_vecVertex2[5].p = D3DXVECTOR3(0, 0, 0);
//	m_vecVertex2[5].t = D3DXVECTOR2(1, 1);
//	m_vecVertex2[5].c = D3DCOLOR_ARGB(255, 255, 255, 255);
//}
