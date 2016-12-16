#include "stdafx.h"
#include "cStraightEffect.h"
#include "cStaticMesh.h"


cStraightEffect::cStraightEffect(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
}


cStraightEffect::~cStraightEffect()
{
}

HRESULT cStraightEffect::Setup(float StraightSpeed, D3DXVECTOR3 s, D3DXVECTOR3 t)
{
	start = false;
	m_fStraightSpeed = StraightSpeed;
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, s.x, s.y, s.z);
	D3DXMatrixTranslation(&matT, t.x, t.y, t.z);
	saveMatT = matT;

	return S_OK;
}

void cStraightEffect::Update()
{
	if (start)
	{
		
	}
}

void cStraightEffect::Render()
{
	if (start)
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000044);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		cStaticObj::Render();
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}
}
