#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cOrca.h"
#include "cFrustum.h"


cMap::cMap(char* szFolder, char* szFilename)
	:m_cFrustum(NULL)
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

	m_vecVertex = *((cStaticMesh*)m_pMesh)->GetVecVertaxies();
}
cMap::cMap()
	:m_cFrustum(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}
cMap::~cMap()
{
	SAFE_DELETE(m_cFrustum);
}
void cMap::Update()
{

	//m_cFrustum->Update();

	//m_vecCullingVertexies = *FindCullingVertex();

	//지형 충돌 
	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPosition();

	if (GetHeight(playerPos.x, playerPos.y, playerPos.z, m_vecVertex))
	{
		float y = playerPos.y;
		pPlayer->SetPosition(D3DXVECTOR3(playerPos.x, playerPos.y, playerPos.z));
	}

	vector<cDynamicObj*> pVecAllMonster = GETSINGLE(cObjMgr)->GetALLMonsterList();
	for (size_t i = 0; i < pVecAllMonster.size(); ++i)
	{
		D3DXVECTOR3 MonsterPos = pVecAllMonster[i]->GetPosition();
		if (GetHeight(MonsterPos.x, MonsterPos.y, MonsterPos.z, m_vecVertex))
		{
			float y = MonsterPos.y;
			pVecAllMonster[i]->SetPosition(D3DXVECTOR3(MonsterPos.x, MonsterPos.y, MonsterPos.z));
		}
	}
}
void cMap::Render()
{


	
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	cStaticObj::Render();
}
bool cMap::GetHeight(IN float x, OUT float& y, IN float z, IN vector<D3DXVECTOR3>	pVecVertex)
{

	D3DXVECTOR3 rayPos(x, 1000, z);
	D3DXVECTOR3 rayDir(0, -1, 0);
	float u, v, d;
	D3DXVECTOR3 p1;
	D3DXVECTOR3 p2;
	D3DXVECTOR3 p3;

	for (int i = 0; i < pVecVertex.size(); i += 3)
	{
		p1 = pVecVertex[i];
		p2 = pVecVertex[i + 1];
		p3 = pVecVertex[i + 2];
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
bool cMap::GetHeight(IN float x, OUT float& y, IN float z)
{
	return true;
}
vector<D3DXVECTOR3>* cMap::FindCullingVertex()
{
	vector<D3DXVECTOR3> vecVertex = *((cStaticMesh*)m_pMesh)->GetVecVertaxies();
	vector<D3DXVECTOR3> vecCullingVertex;
	D3DXVECTOR3			coodVertex1;
	D3DXVECTOR3			coodVertex2;
	D3DXVECTOR3			coodVertex3;

	for (size_t i = 0; i < vecVertex.size(); i+=3)
	{
		D3DXVec3TransformCoord(&coodVertex1, &vecVertex[i], &m_matWorld);
		D3DXVec3TransformCoord(&coodVertex2, &vecVertex[i+1], &m_matWorld);
		D3DXVec3TransformCoord(&coodVertex3, &vecVertex[i+2], &m_matWorld);
		if (m_cFrustum->IsinFrustum(&coodVertex1))
		{
			vecCullingVertex.push_back(coodVertex1);
			vecCullingVertex.push_back(coodVertex2);
			vecCullingVertex.push_back(coodVertex3);
		}
		else if (m_cFrustum->IsinFrustum(&coodVertex2))
		{
			vecCullingVertex.push_back(coodVertex1);
			vecCullingVertex.push_back(coodVertex2);
			vecCullingVertex.push_back(coodVertex3);
		}
		else if (m_cFrustum->IsinFrustum(&coodVertex3))
		{
			vecCullingVertex.push_back(coodVertex1);
			vecCullingVertex.push_back(coodVertex2);
			vecCullingVertex.push_back(coodVertex3);
		}

	}
	
	return &vecCullingVertex;
}