#include "stdafx.h"
#include "cCircleEffect.h"
#include "cStaticMesh.h"


cCircleEffect::cCircleEffect(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
}


cCircleEffect::~cCircleEffect()
{
}

HRESULT cCircleEffect::Setup(int Wheels, float RotationSpeed, bool Left)
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
	return S_OK;
}

void cCircleEffect::Update()
{
	if (start)
	{
		if(!isLeft)
			m_fAngle += m_fRotationSpeed;
		else
			m_fAngle -= m_fRotationSpeed;
		nowWheels = m_fAngle / (D3DX_PI * 2);
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
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
		g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
		D3DXMatrixTranslation(&matT,((cGameObject*)m_pMesh)->GetPosition().x, ((cGameObject*)m_pMesh)->GetPosition().y, ((cGameObject*)m_pMesh)->GetPosition().z);
		D3DXMatrixRotationY(&matR, m_fAngle);
		matWorld = matS * matR * matT;
		g_pD3DDevice->SetTransform(D3DTS_WORLD, &matWorld);
		cStaticObj::Render();
		g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
	}
}
