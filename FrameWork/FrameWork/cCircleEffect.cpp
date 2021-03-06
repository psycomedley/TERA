#include "stdafx.h"
#include "cCircleEffect.h"
#include "cStaticMesh.h"


cCircleEffect::cCircleEffect(char* szFolder, char* szFilename)
	: start(false)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
}


cCircleEffect::~cCircleEffect()
{
}

HRESULT cCircleEffect::Setup(int Wheels, float RotationSpeed, bool Left,
	D3DXVECTOR3 s, D3DXVECTOR3 t, float Angle)
{
	m_fAngle = Angle;
	RealAngle = 0;
	needWheels = Wheels;
	nowWheels = 0;
	m_fRotationSpeed = RotationSpeed;
	D3DXMatrixIdentity(&matWorld);
	isLeft = Left;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixScaling(&matS,s.x,s.y,s.z);
	D3DXMatrixTranslation(&matT, t.x,t.y,t.z);


	return S_OK;
}

void cCircleEffect::Update()
{
	if (start)
	{
		if (!isLeft)
		{
			m_fAngle += m_fRotationSpeed;
			RealAngle += m_fRotationSpeed;
		}
		else
		{
			m_fAngle -= m_fRotationSpeed;
			RealAngle -= m_fRotationSpeed;
		}
		nowWheels = RealAngle / (D3DX_PI);
		if (abs(nowWheels) >= needWheels)
		{
			Stop();
		}
	}
}

void cCircleEffect::Render()
{
	if (start)
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000044);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

		D3DXMatrixRotationY(&matR, m_fAngle);
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		cStaticObj::Render();
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}
}

void cCircleEffect::SetPosition(D3DXVECTOR3 t)
{
	D3DXMatrixTranslation(&matT, t.x, t.y, t.z);
}
