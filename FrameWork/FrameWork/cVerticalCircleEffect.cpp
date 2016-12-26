#include "stdafx.h"
#include "cVerticalCircleEffect.h"
#include "cStaticMesh.h"


cVerticalCircleEffect::cVerticalCircleEffect(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
}


cVerticalCircleEffect::~cVerticalCircleEffect()
{
	SAFE_RELEASE(m_pMesh);
}

HRESULT cVerticalCircleEffect::Setup(int Wheels, float RotationSpeed, bool Front, D3DXVECTOR3 s, D3DXVECTOR3 t, float Angle)
{
	start = false;
	m_fAngle = Angle;
	RealAngle = 0;
	needWheels = Wheels;
	nowWheels = 0;
	m_fRotationSpeed = RotationSpeed;
	D3DXMatrixIdentity(&matWorld);
	isFront = Front;
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matR);
	D3DXMatrixIdentity(&matT);

	D3DXMatrixRotationY(&matRy, m_fAngle);
	D3DXMatrixScaling(&matS, s.x, s.y, s.z);
	D3DXMatrixTranslation(&matT, t.x, t.y, t.z);

	return S_OK;
}

void cVerticalCircleEffect::Update()
{
	if (start)
	{
		if (!isFront)
		{
		//	m_fAngle -= m_fRotationSpeed;
			RealAngle -= m_fRotationSpeed;
		}
		else
		{
		//	m_fAngle += m_fRotationSpeed;
			RealAngle += m_fRotationSpeed;
		}
		nowWheels = RealAngle / (D3DX_PI);
		if (abs(nowWheels) >= needWheels)
		{
			Stop();
		}
	}
}

void cVerticalCircleEffect::Render()
{
	if (start)
	{
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000044);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);


		D3DXMatrixRotationX(&matRx, RealAngle);
		matR = matRx * matRy;
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		cStaticObj::Render();
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}
}

void cVerticalCircleEffect::SetPosition(D3DXVECTOR3 t)
{
	D3DXMatrixTranslation(&matT, t.x, t.y, t.z);
}
