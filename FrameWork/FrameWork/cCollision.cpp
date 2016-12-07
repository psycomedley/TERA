#include "stdafx.h"
#include "cCollision.h"
#include "cRay.h"
#include "cBoundingBox.h"
#include "cBoundingSphere.h"

cCollision::cCollision()
{
}


cCollision::~cCollision()
{
}


void cCollision::Release()
{
	cSingleton::Release();
}


bool cCollision::Collision(cRay* pRay, cBoundingSphere* pSphere)
{ 
	float qq = D3DXVec3Dot(&pRay->GetOri(), &pRay->GetOri());
	float qv = D3DXVec3Dot(&pRay->GetOri(), &pRay->GetDir());
	float vv = D3DXVec3Dot(&pRay->GetDir(), &pRay->GetDir());
	float rr = pSphere->GetRadius() * pSphere->GetRadius();

	return qv * qv - vv * (qq - rr) >= 0;
}


bool cCollision::Collision(cBoundingSphere* pSphere, cRay* pRay)
{
	float qq = D3DXVec3Dot(&pRay->GetOri(), &pRay->GetOri());
	float qv = D3DXVec3Dot(&pRay->GetOri(), &pRay->GetDir());
	float vv = D3DXVec3Dot(&pRay->GetDir(), &pRay->GetDir());
	float rr = pSphere->GetRadius() * pSphere->GetRadius();

	return qv * qv - vv * (qq - rr) >= 0;
}


bool cCollision::Collision(cBoundingSphere* pSphere1, cBoundingSphere* pSphere2)
{
	D3DXVECTOR3 v = pSphere1->GetCenter() - pSphere2->GetCenter();
	float distance = D3DXVec3Length(&v);

	if (pSphere1->GetRadius() + pSphere2->GetRadius() > distance)
		return true;
	return false;
}


bool cCollision::Collision(cBoundingBox* pBox1, cBoundingBox* pBox2)
{
	D3DXVECTOR3 vMax1 = pBox1->GetvMax();
	D3DXVECTOR3 vMin1 = pBox1->GetvMin();
	D3DXVECTOR3 vMax2 = pBox2->GetvMax();
	D3DXVECTOR3 vMin2 = pBox2->GetvMin();
	if ((vMax1.x > vMin2.x && vMin1.x < vMax2.x) &&
		(vMax1.y > vMin2.y && vMin1.y < vMax2.y) &&
		(vMax1.z > vMin2.z && vMin1.z < vMax2.z))
		return true;

	return false;
}


bool cCollision::CollisionOBB(cBoundingBox* pBox1, cBoundingBox* pBox2)
{
	return false;
}