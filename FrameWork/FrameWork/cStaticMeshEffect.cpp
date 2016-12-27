#include "stdafx.h"
#include "cStaticMeshEffect.h"
#include "cStaticMesh.h"
#include "cPlayer.h"


cStaticMeshEffect::cStaticMeshEffect(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
}


cStaticMeshEffect::~cStaticMeshEffect()
{
}

HRESULT cStaticMeshEffect::Setup(D3DXVECTOR3 s, D3DXVECTOR3 t, float Angle)
{
	m_fAngle = Angle;
	
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, s.x, s.y, s.z);
	D3DXMatrixRotationY(&matR, m_fAngle);
	D3DXMatrixTranslation(&matT, t.x, t.y, t.z);
	matWorld = matS * matR * matT;
	return S_OK;
}

void cStaticMeshEffect::Update()
{

}

void cStaticMeshEffect::Render()
{
	// D3DBLEND_ZERO : (0, 0, 0, 0)
	// D3DBLEND_ONE : (1, 1, 1, 1)
	// D3DBLEND_SRCCOLOR : (rs, gs, bs, as)
	// D3DBLEND_INVSRCCOLOR : (1-rs, 1-gs, 1-bs, 1-as)
	// D3DBLEND_SRCALPHA : (as, as, as, as) (Source Blend 기본값)
	// D3DBLEND_INVSRCALPHA : (1-as, 1-as, 1-as, 1-as) (Destination Blend 기본값)
	// D3DBLEND_DESTALPHA : (ad, ad, ad, ad)
	// D3DBLEND_INVDESTALPHA : (1-ad, 1-ad, 1-ad, 1-ad)
	// D3DBLEND_DESTCOLOR : (rd, gd, bd, ad)
	// D3DBLEND_INVDESTCOLOR : (1-rd, 1-gd, 1-bd, 1-ad)
	// D3DBLEND_SRCALPHASAT : (f, f, f, 1); f=min(as, 1-ad)

	// D3DBLENDOP_ADD (기본값)   : src + dest
	// D3DBLENDOP_SUBTRACT      : src - dest
	// D3DBLENDOP_REVSUBTRACT   : dest - src
	// D3DBLENDOP_MIN         : MIN(src, dest)
	// D3DBLENDOP_MAX         : MAX(src, dest)
	
	/*g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);*/

	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false);


	//g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	g_pD3DDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
	g_pD3DDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
	cStaticObj::Render();/*
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);*/

	g_pD3DDevice->SetRenderState(D3DRS_ZENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
	g_pD3DDevice->SetRenderState(D3DRS_ZWRITEENABLE, true);
}

