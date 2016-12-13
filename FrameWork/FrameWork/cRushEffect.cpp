#include "stdafx.h"
#include "cRushEffect.h"
#include "cStaticMesh.h"


cRushEffect::cRushEffect(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
}


cRushEffect::~cRushEffect()
{
}

HRESULT cRushEffect::Setup(int Wheels, float RotationSpeed, bool Left, D3DXVECTOR3 s, D3DXVECTOR3 t)
{
	start = false;
	m_fAngle = 0;
	needWheels = Wheels;
	nowWheels = 0;
	m_fRotationSpeed = RotationSpeed;
	D3DXMatrixIdentity(&matWorld);
	isLeft = Left;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS, s.x, s.y, s.z);
	D3DXMatrixTranslation(&matT, t.x, t.y, t.z);
	return S_OK;
}

void cRushEffect::Update()
{
	if (start)
	{
		if (!isLeft)
			m_fAngle += m_fRotationSpeed;
		else
			m_fAngle -= m_fRotationSpeed;
		nowWheels = m_fAngle / (D3DX_PI);
		if (abs(nowWheels) >= needWheels)
		{
			Stop();
		}
	}
}

void cRushEffect::Render()
{
	if (start)
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000044);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		D3DXMatrixRotationZ(&matR, m_fAngle);
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		cStaticObj::Render();
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}
}
