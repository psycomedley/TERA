#include "stdafx.h"
#include "cGameObject.h"
#include "cMesh.h"
#include "cCamera.h"


cGameObject::cGameObject(void)
	: m_pMesh(NULL)
	, m_vScale(1, 1, 1)
	, m_vPosition(0, 0, 0)
	, m_vCameraFocus(0, 0, 0)
	, m_fAngle(0)
	, m_vDirection(0, 0, 1)
	, m_pAction(NULL)
	, m_vPrevPosition(0, 0, 0)
	, m_fRevisionAngle(0.f)
	, m_fRotX(0)
	, m_fRotY(0)
	, m_fRotZ(0)
	, m_vRevisionScale(1,1,1)
	, m_vRevisionPosition(0,0,0)
{
	D3DXMatrixIdentity(&m_matWorld);
	D3DXMatrixIdentity(&m_matRevision);
}


cGameObject::~cGameObject(void)
{
	SAFE_RELEASE(m_pAction);
}

void cGameObject::Update()
{
	if (m_pAction)
		m_pAction->Update();

	float rX = CAMERA->GetCamRotX();
	float rY = CAMERA->GetCamRotY();

	m_vCameraFocus = m_vPosition + D3DXVECTOR3(0.3 * cosf(rX), 2.2, 0.3 * -sinf(rX));
}

void cGameObject::Render()
{

}


void cGameObject::Bounding_Update()
{
	if (m_pMesh)
		m_pMesh->Bounding_Update(m_vPosition, m_vScale, m_fAngle, &m_matRevision);
}


void cGameObject::Bounding_Render()
{
	if (m_pMesh)
	{
		m_pMesh->Bounding_Render(D3DXVECTOR3(m_vPosition.x + m_vRevisionPosition.x, m_vPosition.y + m_vRevisionPosition.y,m_vPosition.z + m_vRevisionPosition.z)
			, D3DXVECTOR3(m_vScale.x*m_vRevisionScale.x, m_vScale.y*m_vRevisionScale.y, m_vScale.z*m_vRevisionScale.z)
			, m_fAngle, &m_matRevision);
	}
}


//void cGameObject::SetPosition(D3DXVECTOR3 vPos)
//{
//	m_vPosition = vPos;
//
////	if (m_pMesh)
////		m_pMesh->GetSphere()->SetCenter(D3DXVECTOR3(vPos.x, vPos.y + m_pMesh->GetSphere()->GetOriginalY(), vPos.z));
//}


void cGameObject::SetBoundingPos()
{
	/*m_pMesh->GetBox()->SetPosition(m_vPosition);
	m_pMesh->GetSphere()->SetPosition(m_vPosition);*/
}

//임시  조금 변형할 것
void cGameObject::Move(float fSpeed)
{
	m_vPosition = m_vPosition - m_vDirection * fSpeed;
}


void cGameObject::Move(D3DXVECTOR3 vec)
{
	m_vPosition = m_vPosition + vec;
}


cBoundingBox cGameObject::GetBox()
{
	return m_pMesh->GetBox(m_vPosition, m_vScale.x, m_fAngle + m_fRevisionAngle);
}


cBoundingSphere cGameObject::GetSphere()
{
	return m_pMesh->GetSphere(m_vPosition, m_vScale.x);
}	