#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cOrca.h"


cMap::cMap(char* szFolder, char* szFilename)
{
	m_pMesh = new cStaticMesh(szFolder, szFilename);
	D3DXMatrixIdentity(&m_matWorld);

	D3DXMATRIXA16	mat, matS, matT;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixIdentity(&matS);
	D3DXMatrixIdentity(&matT);
	D3DXMatrixTranslation(&matT, -210, -153.7f, -210);
	D3DXMatrixScaling(&matS, 0.05f, 0.05f, 0.05f);
	m_matWorld = matS*matT;
}


cMap::cMap()
{
	D3DXMatrixIdentity(&m_matWorld);
}
cMap::~cMap()
{
}
void cMap::Update()
{
	//지형 충돌 
	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPosition();

	if (GetHeight(playerPos.x, playerPos.y, playerPos.z))
	{
		float y = playerPos.y;
		pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
	}

	vector<cDynamicObj*> pVecAllMonster = GETSINGLE(cObjMgr)->GetALLMonsterList();
	for (size_t i = 0; i < pVecAllMonster.size(); ++i)
	{
		D3DXVECTOR3 MonsterPos = pVecAllMonster[i]->GetPosition();
		if (GetHeight(MonsterPos.x, MonsterPos.y, MonsterPos.z))
		{
			float y = MonsterPos.y;
			pVecAllMonster[i]->SetPosition(D3DXVECTOR3(MonsterPos.x, MonsterPos.y, MonsterPos.z));
		}
	}
}
void cMap::Render()
{


	//m_matWorld = m_matWorld* mat;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	cStaticObj::Render();
}
bool cMap::GetHeight(IN float x, OUT float& y, IN float z)
{

	D3DXVECTOR3 rayPos(x, 1000, z);
	D3DXVECTOR3 rayDir(0, -1, 0);
	float u, v, d;
	BOOL Hit;
	D3DXVECTOR3 p1;
	D3DXVECTOR3 p2;
	D3DXVECTOR3 p3;
	vector<D3DXVECTOR3> vecVertex = *((cStaticMesh*)m_pMesh)->GetVecVertaxies();

	for (int i = 0; i < vecVertex.size(); i += 3)
	{
		p1 = vecVertex[i];
		p2 = vecVertex[i + 1];
		p3 = vecVertex[i + 2];
		D3DXVec3TransformCoord(&p1, &p1, &m_matWorld);
		D3DXVec3TransformCoord(&p2, &p2, &m_matWorld);
		D3DXVec3TransformCoord(&p3, &p3, &m_matWorld);
		if (D3DXIntersectTri(&p1, &p2, &p3, &rayPos, &rayDir, &u, &v, &d))
		{
			y = 1000 - d;
			return true;

		}
	}
	y = 0;
	return false;
}