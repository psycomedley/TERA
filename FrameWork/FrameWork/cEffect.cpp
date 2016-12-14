#include "stdafx.h"
#include "cEffect.h"
#include "cPlayer.h"


cEffect::cEffect()
	: m_pTexture(NULL)
	, m_pEffect(NULL)
	, m_pVB(NULL)
	, m_nCurrentFrame(0)
	, m_fPassedTime(0.0f)
	, m_fNextTime(0.1f)
	, m_nMaxFrameX(0)
	, m_nMaxFrameY(0)
	, m_nMaxFrame(0)
	, m_bLoop(false)
	, m_bProcess(false)
	, m_vPosition(0.0f, 0.0f, 0.0f)
	, m_fAngle(0.0f)
	, m_nOffsetX(1)
	, m_nOffsetY(1)
{
	D3DXMatrixIdentity(&m_matScale);
}


cEffect::~cEffect()
{
	SAFE_RELEASE(m_pVB);
}


HRESULT cEffect::Setup(float fWidth, float fHeight, float fAlpha /*= 1.0f*/,
	int nOption /*= EFFECT_BILLBOARING | EFFECT_ALPHABLEND*/)
{
	m_pEffect = GETSINGLE(cShaderMgr)->GetEffect(E_SHADER_EFFECT);

	m_vecVertex.resize(6);

	float fHalfWidth = fWidth / 2;
	float fHalfHeight = fHeight / 2;
	m_fAlpha = fAlpha;

	m_vecVertex[0].p = D3DXVECTOR3(-fHalfWidth, -fHalfHeight, 0);
	m_vecVertex[0].t = D3DXVECTOR2(0, 1);
	m_vecVertex[0].c = XWHITE;

	m_vecVertex[1].p = D3DXVECTOR3(-fHalfWidth, fHalfHeight, 0);
	m_vecVertex[1].t = D3DXVECTOR2(0, 0);
	m_vecVertex[1].c = XWHITE;

	m_vecVertex[2].p = D3DXVECTOR3(fHalfWidth, fHalfHeight, 0);
	m_vecVertex[2].t = D3DXVECTOR2(1, 0);
	m_vecVertex[2].c = XWHITE;

	m_vecVertex[3].p = D3DXVECTOR3(-fHalfWidth, -fHalfHeight, 0);
	m_vecVertex[3].t = D3DXVECTOR2(0, 1);
	m_vecVertex[3].c = XWHITE;

	m_vecVertex[4].p = D3DXVECTOR3(fHalfWidth, fHalfHeight, 0);
	m_vecVertex[4].t = D3DXVECTOR2(1, 0);
	m_vecVertex[4].c = XWHITE;

	m_vecVertex[5].p = D3DXVECTOR3(fHalfWidth, -fHalfHeight, 0);
	m_vecVertex[5].t = D3DXVECTOR2(1, 1);
	m_vecVertex[5].c = XWHITE;

	if (FAILED(g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PCT_VERTEX),
		0,
		ST_PCT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0)))
	{
		MSGBOX("Effect VertexBuffer Make Fail");
		return E_FAIL;
	}

	LPVOID pV;
	m_pVB->Lock(0, 0, &pV, 0);
	memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PCT_VERTEX));
	m_pVB->Unlock();

	m_nOption = nOption;

	return S_OK;
}


HRESULT cEffect::Setup(string sPath, float fWidth, float fHeight,
	int nMaxFrameX /*= 1*/, int nMaxFrameY /*= 1*/, float fNextTime /*= 0.1f*/,
	bool bLoop /*= false*/, float fAlpha /*= 1.0f*/, int nMaxFrame /*= 0*/)
{
	m_vecVertex.resize(6);
	m_fNextTime = fNextTime;

	m_pTexture = GETSINGLE(cTextureMgr)->GetTexture(sPath);
	m_pTexture2 = GETSINGLE(cTextureMgr)->GetTexture("Effect/G_MagicArray002_Alpha_Tex.tga");
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
	m_vecVertex[0].t = D3DXVECTOR2(0, 1);
	m_vecVertex[0].c = XWHITE;
//	m_vecVertex[0].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[1].p = D3DXVECTOR3(-fHalfWidth, fHalfHeight, 0);
	m_vecVertex[1].t = D3DXVECTOR2(0, 0);
	m_vecVertex[1].c = XWHITE;
//	m_vecVertex[1].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[2].p = D3DXVECTOR3(fHalfWidth, fHalfHeight, 0);
	m_vecVertex[2].t = D3DXVECTOR2(1, 0);
	m_vecVertex[2].c = XWHITE;
//	m_vecVertex[2].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[3].p = D3DXVECTOR3(-fHalfWidth, -fHalfHeight, 0);
	m_vecVertex[3].t = D3DXVECTOR2(0, 1);
	m_vecVertex[3].c = XWHITE;
//	m_vecVertex[3].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[4].p = D3DXVECTOR3(fHalfWidth, fHalfHeight, 0);
	m_vecVertex[4].t = D3DXVECTOR2(1, 0);
	m_vecVertex[4].c = XWHITE;
//	m_vecVertex[4].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	m_vecVertex[5].p = D3DXVECTOR3(fHalfWidth, -fHalfHeight, 0);
	m_vecVertex[5].t = D3DXVECTOR2(1, 1);
	m_vecVertex[5].c = XWHITE;
//	m_vecVertex[5].c = D3DCOLOR_ARGB(nAlpha, 255, 255, 255);

	if (FAILED(g_pD3DDevice->CreateVertexBuffer(
		m_vecVertex.size() * sizeof(ST_PCT_VERTEX),
		0,
		ST_PCT_VERTEX::FVF,
		D3DPOOL_MANAGED,
		&m_pVB,
		0)))
	{
		MSGBOX("Effect VertexBuffer Make Fail");
		return E_FAIL;
	}

	LPVOID pV;
	m_pVB->Lock(0, 0, &pV, 0);
	memcpy(pV, &m_vecVertex[0], m_vecVertex.size() * sizeof(ST_PCT_VERTEX));
	m_pVB->Unlock();

	m_pEffect = GETSINGLE(cShaderMgr)->GetEffect(E_SHADER_EFFECT);

	m_nOption = EFFECT_BILLBOARING | EFFECT_ALPHABLEND;

	return S_OK;
}


void cEffect::Update()
{
	if (m_bProcess)
	{
		m_fPassedTime += GETSINGLE(cTimeMgr)->getElapsedTime();

		
	}
}


void cEffect::Render()
{
	if (m_bProcess)
	{
		D3DXMATRIXA16 matWorld, matView, matProj, mat;
		D3DXMatrixIdentity(&matWorld);
		g_pD3DDevice->GetTransform(D3DTS_VIEW, &matView);
		g_pD3DDevice->GetTransform(D3DTS_PROJECTION, &matProj);

		if (m_nOption & EFFECT_ALPHABLEND)
		{
			g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

			//설정하도록
			g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
			g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
			g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		}
		if (m_nOption & EFFECT_CUTTEDFRAME)
		{
			if (m_fPassedTime >= m_fNextTime)
			{
				m_fPassedTime -= m_fNextTime;
				if (++m_nCurrentFrame >= m_nMaxFrame)
					m_nCurrentFrame -= m_nMaxFrame;
				UpdateUV();
			}

			m_pEffect->SetInt("g_nOffsetX", m_nOffsetX);
			m_pEffect->SetInt("g_nOffsetY", m_nOffsetY);
		}
		if (m_nOption & EFFECT_BILLBOARING)
		{
			D3DXMatrixInverse(&matWorld, 0, &matView);
			matWorld._41 = m_vPosition.x;
			matWorld._42 = m_vPosition.y;
			matWorld._43 = m_vPosition.z;
			
			matWorld = matWorld * m_matScale;
		}
		else
		{
			D3DXMATRIXA16 matR, matT;
			D3DXMatrixRotationX(&matR, m_fAngle);
			D3DXMatrixTranslation(&matT, m_vPosition.x, m_vPosition.y, m_vPosition.z);

			matWorld = matWorld * matR * matT;
		}

		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
		g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
		
		g_pD3DDevice->SetFVF(ST_PCT_VERTEX::FVF);
		
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		mat = matWorld * matView * matProj;

		m_pEffect->SetMatrix("g_matWVP", &mat);
		m_pEffect->SetFloat("g_fPassedTime", m_fPassedTime);
		m_pEffect->SetFloat("g_fAlpha", m_fAlpha);

		//if (m_pTexture)
		//	m_pEffect->SetTexture("DiffuseMap_Tex", m_pTexture);
		//if (m_pTexture2)
		//	m_pEffect->SetTexture("DiffuseMap_Tex2", m_pTexture2);
		//if (m_pBumpMap)
		//	m_pEffect->SetTexture("BumpMap_Tex", m_pBumpMap);
		Setting();

		UINT uiPasses, uiPass;
		m_pEffect->Begin(&uiPasses, 0);
		for (uiPass = 0; uiPass < uiPasses; ++uiPass)
		{
			m_pEffect->BeginPass(uiPass);
			g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PCT_VERTEX));
			g_pD3DDevice->DrawPrimitive(
				D3DPT_TRIANGLELIST,
				0,
				2);
			m_pEffect->EndPass();
		}
		m_pEffect->End();

		g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
		g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	}
}


void cEffect::UpdateUV()
{
	m_nOffsetX = m_nCurrentFrame % m_nMaxFrameX;
	m_nOffsetY = m_nCurrentFrame / m_nMaxFrameX;

	//int nX = m_nCurrentFrame % m_nMaxFrameX;
	//int nY = m_nCurrentFrame / m_nMaxFrameX;
	//float fRatioX = 1 / (float)m_nMaxFrameX;
	//float fRatioY = 1 / (float)m_nMaxFrameY;

	//// 1─2  4
	//// | / / |
	//// 0  3─5
	//
	//m_vecVertex[0].t = D3DXVECTOR2(fRatioX * nX, fRatioY * (nY + 1));
	//m_vecVertex[1].t = D3DXVECTOR2(fRatioX * nX, fRatioY * nY);
	//m_vecVertex[2].t = D3DXVECTOR2(fRatioX * (nX + 1), fRatioY * nY);
	//m_vecVertex[3].t = D3DXVECTOR2(fRatioX * nX, fRatioY * (nY + 1));
	//m_vecVertex[4].t = D3DXVECTOR2(fRatioX * (nX + 1), fRatioY * nY);
	//m_vecVertex[5].t = D3DXVECTOR2(fRatioX * (nX + 1), fRatioY * (nY + 1));
}


void cEffect::Start()
{
	m_bProcess = true;
}


void cEffect::Stop()
{
	m_bProcess = false;
	m_fPassedTime = 0.0f;
	m_nCurrentFrame = 0;
}


void cEffect::Pause()
{
	m_bProcess = false;
}


void cEffect::SetTexture(string sKey, E_EFFECT_TEXTURE eTex)
{
	switch (eTex)
	{
	case E_TEXTURE1:
		m_pTexture = GETSINGLE(cTextureMgr)->GetTexture(sKey);
		m_pEffect->SetTexture("DiffuseMap_Tex", m_pTexture);
		break;
	case E_TEXTURE2:
		m_pTexture2 = GETSINGLE(cTextureMgr)->GetTexture(sKey);
		m_pEffect->SetTexture("DiffuseMap_Tex2", m_pTexture2);
		break;
	case E_BUMPMAP:
		m_pBumpMap = GETSINGLE(cTextureMgr)->GetTexture(sKey);
		m_pEffect->SetTexture("BumpMap_Tex", m_pBumpMap);
		break;
	}
}


void cEffect::SetTotalFrame(int nFrameX, int nFrameY, int nTotalFrame)
{
	m_nMaxFrameX = nFrameX;
	m_nMaxFrameY = nFrameY;
	m_nMaxFrame = nTotalFrame;

	m_fRatioX = 1 / (float)m_nMaxFrameX;
	m_fRatioY = 1 / (float)m_nMaxFrameY;

	m_pEffect->SetFloat("g_fRatioX", m_fRatioX);
	m_pEffect->SetFloat("g_fRatioY", m_fRatioY);
}


void cEffect::SetTech(E_EFFECT_TECHNIQUE eTech)
{
	switch (eTech)
	{
	case E_TECH_NORMAL:
		m_pEffect->SetTechnique("NormalShader");
		break;
	case E_TECH_BLUE:
		m_pEffect->SetTechnique("BlueShader");
		break;
	case E_TECH_FRAMEMOVEX:
		m_pEffect->SetTechnique("FrameMoveX");
		break;
	case E_TECH_FRAMEMOVEY:
		m_pEffect->SetTechnique("FrameMoveY");
		break;
	case E_TECH_WAVE:
		m_pEffect->SetTechnique("Wave");
		break;
	case E_TECH_FRAMEADD:
		m_pEffect->SetTechnique("FrameAdd");
		break;
	case E_TECH_TEST:
		m_pEffect->SetTechnique("Test");
		break;
	default:
		break;
	}
}


void cEffect::Setting()
{
	m_pEffect->SetTexture("DiffuseMap_Tex", m_pTexture);
	m_pEffect->SetTexture("DiffuseMap_Tex2", m_pTexture2);
	m_pEffect->SetTexture("BumpMap_Tex", m_pBumpMap);

	SetTech(m_eTechnique);
}