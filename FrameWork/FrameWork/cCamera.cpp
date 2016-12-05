#include "StdAfx.h"
#include "cCamera.h"
#include "cGameObject.h"


cCamera::cCamera(void)
	: m_vEye(0, 0, -5)
	, m_vLookAt(0, 0, 0)
	, m_vUp(0, 1, 0)
	, m_fCamRotX(0.0f)
	, m_fCamRotY(0.0f)
	, m_fCamDist(5)
	, m_bUse(false)
	, m_bControl(true)
{
}


cCamera::~cCamera(void)
{
}


void cCamera::Setup()
{
	D3DXMATRIXA16 matView, matProj;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);

	RECT rc;
	GetClientRect(g_hWnd, &rc);
	D3DXMatrixPerspectiveFovLH(&matProj, D3DX_PI / 4.0f, rc.right / (float)rc.bottom, 1.f, 5000.f);
	g_pD3DDevice->SetTransform(D3DTS_PROJECTION, &matProj);
}


void cCamera::Update()
{
	if (KEYBOARD->IsOnceKeyDown(DIK_ESCAPE))
	{
		m_bControl = !m_bControl;
		ShowCursor(!m_bControl);
	}

	if (m_bControl)
		CameraMove();

	D3DXMATRIXA16 matR, matRX, matRY;
	D3DXMatrixRotationX(&matRX, m_fCamRotY);
	D3DXMatrixRotationY(&matRY, m_fCamRotX);
	matR = matRX * matRY;

	m_vEye = D3DXVECTOR3(0, 0, -m_fCamDist);
	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);

	if (m_pTarget)
	{
		m_vEye = m_vEye + m_pTarget->GetPosition();
		m_vLookAt = m_pTarget->GetPosition();
	}

	D3DXMATRIXA16 matView;
	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
}


//void cCamera::Update(D3DXVECTOR3* pTarget /*= NULL*/)
//{
//	if (KEYBOARD->IsOnceKeyDown(DIK_ESCAPE))
//		m_bControl = !m_bControl;
//
//	if (m_bControl)
//		CameraMove();
//
//	D3DXMATRIXA16 matR, matRX, matRY;
//	D3DXMatrixRotationX(&matRX, m_fCamRotY);
//	D3DXMatrixRotationY(&matRY, m_fCamRotX);
//	matR = matRX * matRY;
//
//	m_vEye = D3DXVECTOR3(0, 0, -m_fCamDist);
//	D3DXVec3TransformCoord(&m_vEye, &m_vEye, &matR);
//
//	if (pTarget)
//	{
//		m_vEye = m_vEye + *pTarget;
//		m_vLookAt = *pTarget;
//	}
//
//	D3DXMATRIXA16 matView;
//	D3DXMatrixLookAtLH(&matView, &m_vEye, &m_vLookAt, &m_vUp);
//	g_pD3DDevice->SetTransform(D3DTS_VIEW, &matView);
//}


void cCamera::CameraMove()
{
	//���� �ܾƿ� ����
	m_fCamDist -= MOUSE->GetWheelVariation() / 100.0f;
	if (m_fCamDist < 1)
		m_fCamDist = 1;

//	if (MOUSE->IsStayKeyDown(MOUSEBTN_LEFT))
//	{
	POINT movePoint = MOUSE->GetMouseVariation();

	m_fCamRotY += (movePoint.y / 300.f);
	m_fCamRotX += (movePoint.x / 300.f);

	if (m_fCamRotY < -D3DX_PI / 2.0f + 0.0001f)
		m_fCamRotY = -D3DX_PI / 2.0f + 0.0001f;

	if (m_fCamRotY > D3DX_PI / 2.0f - 0.0001f)
		m_fCamRotY = D3DX_PI / 2.0f - 0.0001f;
//	}
}


void cCamera::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	/*switch (message)
	{
	case WM_LBUTTONDOWN:
		m_isLButtonDown = true;
		m_ptPrevMouse.x = LOWORD(lParam);
		m_ptPrevMouse.y = HIWORD(lParam);
		break;
	case WM_LBUTTONUP:
		m_isLButtonDown = false;
		break;
	case WM_MOUSEMOVE:
	{
		if (m_isLButtonDown)
		{
			POINT ptCurrMouse;
			ptCurrMouse.x = LOWORD(lParam);
			ptCurrMouse.y = HIWORD(lParam);
			float fDeltaX = ptCurrMouse.x - m_ptPrevMouse.x;
			float fDeltaY = ptCurrMouse.y - m_ptPrevMouse.y;

			m_fCamRotX += (fDeltaY / 100.f);
			m_fCamRotY += (fDeltaX / 100.f);

			if (m_fCamRotX < -D3DX_PI / 2.0f + 0.0001f)
				m_fCamRotX = -D3DX_PI / 2.0f + 0.0001f;

			if (m_fCamRotX > D3DX_PI / 2.0f - 0.0001f)
				m_fCamRotX = D3DX_PI / 2.0f - 0.0001f;

			m_ptPrevMouse = ptCurrMouse;
		}
	}
	break;
	case WM_MOUSEWHEEL:
		m_fCamDist += -GET_WHEEL_DELTA_WPARAM(wParam) / 100.f;
		if (m_fCamDist < 1)
			m_fCamDist = 1;

		break;
	}*/
}