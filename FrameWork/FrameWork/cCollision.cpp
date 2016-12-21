#include "stdafx.h"
#include "cCollision.h"
#include "cRay.h"
#include "cBoundingBox.h"
#include "cBoundingSphere.h"
#include "cPlayer.h"
#include "cMonster.h"


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
	ST_OBB stObb1 = pBox1->GetObb();
	ST_OBB stObb2 = pBox2->GetObb();

	float cos[3][3];
	float absCos[3][3];
	float dist[3];
	float r0, r1, r;

	const float cutOff = 0.999999f;
	bool existsParallelPair = false;

	D3DXVECTOR3 D = stObb2.vCenterPos - stObb1.vCenterPos;

	// OBB_A 의 3 축을 기준으로 OBB_B 의 3축을 검사
	for (int a = 0; a < 3; a++)
	{
		for (int b = 0; b < 3; b++)
		{
			//OBB_A a 축과 OBB_B b 축의 cos 값
			cos[a][b] = D3DXVec3Dot(&stObb1.vAxisDir[a], &stObb2.vAxisDir[b]);

			//위에서 구한 cos 값의 절대값
			absCos[a][b] = abs(cos[a][b]);


			//한축이 직각이다 
			//이러한경우 AABB 형태가 된다.
			if (absCos[a][b] > cutOff)
				existsParallelPair = true;
		}


		//사각형 끼리의 중심 거리 벡터를 OBB_A 의 a 축으로 투영한 거리
		dist[a] = D3DXVec3Dot(&stObb1.vAxisDir[a], &D);
		r = abs(dist[a]);

		//OBB_A 의 a 축의 길이
		r0 = stObb1.fAxisHalfLen[a];

		//OBB_B 의 꼭지점이 OBB_A 의a 축으로 투영된 길이
		r1 = stObb2.fAxisHalfLen[0] * absCos[a][0] +
			stObb2.fAxisHalfLen[1] * absCos[a][1] +
			stObb2.fAxisHalfLen[2] * absCos[a][2];

		if (r > r0 + r1)
			return false;
	}



	// OBB_B 의 3축을 기준으로 OBB_A 의 3축을 검사
	for (int b = 0; b < 3; b++)
	{
		r = abs(D3DXVec3Dot(&stObb2.vAxisDir[b], &D));
		r0 = stObb1.fAxisHalfLen[0] * absCos[0][b] +
			stObb1.fAxisHalfLen[1] * absCos[1][b] +
			stObb1.fAxisHalfLen[2] * absCos[2][b];

		r1 = stObb2.fAxisHalfLen[b];

		if (r > r0 + r1)
			return false;
	}


	if (existsParallelPair) return true;




	/////////////////////////////////////////////////////////////////

	r = abs(dist[0] * cos[2][0] - dist[2] * cos[0][0]);
	r0 = stObb1.fAxisHalfLen[0] * absCos[2][0] + stObb1.fAxisHalfLen[2] * absCos[0][0];
	r1 = stObb2.fAxisHalfLen[1] * absCos[1][2] + stObb2.fAxisHalfLen[2] * absCos[1][1];
	if (r > r0 + r1)
		return false;

	r = abs(dist[0] * cos[2][1] - dist[2] * cos[0][1]);
	r0 = stObb1.fAxisHalfLen[0] * absCos[2][1] + stObb1.fAxisHalfLen[2] * absCos[0][1];
	r1 = stObb2.fAxisHalfLen[0] * absCos[1][2] + stObb2.fAxisHalfLen[2] * absCos[1][0];
	if (r > r0 + r1)
		return false;

	r = abs(dist[0] * cos[2][2] - dist[2] * cos[0][2]);
	r0 = stObb1.fAxisHalfLen[0] * absCos[2][2] + stObb1.fAxisHalfLen[2] * absCos[0][2];
	r1 = stObb2.fAxisHalfLen[0] * absCos[1][1] + stObb2.fAxisHalfLen[1] * absCos[1][0];
	if (r > r0 + r1)
		return false;


	/////////////////////////////////////////////////////////////////	 


	r = abs(dist[1] * cos[0][0] - dist[0] * cos[1][0]);
	r0 = stObb1.fAxisHalfLen[0] * absCos[1][0] + stObb1.fAxisHalfLen[1] * absCos[0][0];
	r1 = stObb2.fAxisHalfLen[1] * absCos[2][2] + stObb2.fAxisHalfLen[2] * absCos[2][1];
	if (r > r0 + r1)
		return false;

	r = abs(dist[1] * cos[0][1] - dist[0] * cos[1][1]);
	r0 = stObb1.fAxisHalfLen[0] * absCos[1][1] + stObb1.fAxisHalfLen[1] * absCos[0][1];
	r1 = stObb2.fAxisHalfLen[0] * absCos[2][2] + stObb2.fAxisHalfLen[2] * absCos[2][0];
	if (r > r0 + r1)
		return false;


	r = abs(dist[1] * cos[0][2] - dist[0] * cos[1][2]);
	r0 = stObb1.fAxisHalfLen[0] * absCos[1][2] + stObb1.fAxisHalfLen[1] * absCos[0][2];
	r1 = stObb2.fAxisHalfLen[0] * absCos[2][1] + stObb2.fAxisHalfLen[1] * absCos[2][0];
	if (r > r0 + r1)
		return false;


	/////////////////////////////////////////////////////////////////

	r = abs(dist[2] * cos[1][0] - dist[1] * cos[2][0]);
	r0 = stObb1.fAxisHalfLen[1] * absCos[2][0] + stObb1.fAxisHalfLen[2] * absCos[1][0];
	r1 = stObb2.fAxisHalfLen[1] * absCos[0][2] + stObb2.fAxisHalfLen[2] * absCos[0][1];
	if (r > r0 + r1)
		return false;



	r = abs(dist[2] * cos[1][1] - dist[1] * cos[2][1]);
	r0 = stObb1.fAxisHalfLen[1] * absCos[2][1] + stObb1.fAxisHalfLen[2] * absCos[1][1];
	r1 = stObb2.fAxisHalfLen[0] * absCos[0][2] + stObb2.fAxisHalfLen[2] * absCos[0][0];
	if (r > r0 + r1)
		return false;



	r = abs(dist[2] * cos[1][2] - dist[1] * cos[2][2]);
	r0 = stObb1.fAxisHalfLen[1] * absCos[2][2] + stObb1.fAxisHalfLen[2] * absCos[1][2];
	r1 = stObb2.fAxisHalfLen[0] * absCos[0][1] + stObb2.fAxisHalfLen[1] * absCos[0][0];
	if (r > r0 + r1)
		return false;




	return true;
}


bool cCollision::Collision(cPlayer* pPlayer, cDynamicObj* pMonster)
{
	if (pMonster->IsMesh())
	{
		cBoundingBox stMonsterBox = pMonster->GetBox();
		if (Collision(&pPlayer->GetRightWeaponBox(), &stMonsterBox))
			return true;
		if (Collision(&pPlayer->GetLeftWeaponBox(), &stMonsterBox))
			return true;

		return false;
	}
	else
	{
		cBoundingSphere stMonsterSphere = ((cMonster*)pMonster)->GetShotSphere();
		if (Collision(&pPlayer->GetRightWeaponSphere(), &stMonsterSphere))
			return true;
		if (Collision(&pPlayer->GetLeftWeaponSphere(), &stMonsterSphere))
			return true;

		return false;
	}
}