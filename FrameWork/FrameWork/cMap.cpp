#include "stdafx.h"
#include "cMap.h"
#include "cPlayer.h"
#include "cOrca.h"
#include "cFrustum.h"
#include "cBoundingSphere.h"


cMap::cMap(char* szFolder, char* szFilename)
	:m_cFrustum(NULL)
	, m_cBoundingSphere(NULL)
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
	m_vecPNTVertex = *((cStaticMesh*)m_pMesh)->GetVecPNTVertaxies();

	/*for (int i = 0; i < m_vecPNTVertex.size(); ++i)
	{
		m_vecTerrainVertex.push_back(m_vecPNTVertex[i].p);
	}*/

	SetupHeight();
}
cMap::cMap()
	:m_cFrustum(NULL)
{
	D3DXMatrixIdentity(&m_matWorld);
}
cMap::~cMap()
{
	SAFE_DELETE(m_cFrustum);

	for each (auto p in m_vecBoundingSphere)
	{
		p->Release();
	}
	
//	m_cBoundingSphere->Release();
}
void cMap::Update()
{

	//m_cFrustum->Update();

	//m_vecCullingVertexies = *FindCullingVertex();

	//지형 충돌 
	cDynamicObj* pPlayer = GETSINGLE(cObjMgr)->GetPlayer();
	D3DXVECTOR3 playerPos = pPlayer->GetPosition();

	if (GetHeight(playerPos.x, playerPos.y, playerPos.z ,m_vecVertex))
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

	/*for (int i = 0; i <m_vecTerrainVertex.size(); ++i)
	{
		m_vecBoundingSphere[i]->Render(m_CoodVecVertex[i], D3DXVECTOR3(1.0f, 1.0f, 1.0f));
	}*/
	
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	cStaticObj::Render();
	//g_pD3DDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);


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
void cMap::SetupHeight()
{
	D3DXVECTOR3			coodVertex1;

	
	float _x, _z;
	int b, a;

	for (size_t i = 0; i < m_vecPNTVertex.size(); ++i)
	{
		D3DXVECTOR3 p1 = m_vecPNTVertex[i].p;
		D3DXVec3TransformCoord(&p1, &p1, &m_matWorld);
		m_CoodVecVertex.push_back(p1);
	}

	for (size_t i = 0; i < m_CoodVecVertex.size(); ++i)
	{
		//D3DXVec3TransformCoord(&coodVertex1, &m_CoodVecVertex[i], &m_matWorld);
		coodVertex1 = m_CoodVecVertex[i];
		if (coodVertex1.x < 10 && coodVertex1.x > 0)
		{
			_x = coodVertex1.x;
			a = i;
		}
		if (coodVertex1.z < 10 && coodVertex1.z > 0)
		{
			_z = coodVertex1.z;
			b= i;
		}
		if (MaxX < coodVertex1.x)
		{
			MaxX = coodVertex1.x;
		}
		if (MinX > coodVertex1.x)
		{
			MinX = coodVertex1.x;
		}
		if (MaxZ < coodVertex1.z)
		{
			MaxZ = coodVertex1.z;
		}
		if (MinZ > coodVertex1.z)
		{
			MinZ = coodVertex1.z;
		}
	}

	//y값만 저장
	
	
	for (size_t i = 0; i < m_vecPNTVertex.size(); ++i)
	{
		m_vecHeight.push_back(m_CoodVecVertex[i].y);
	}

	 MapSize = m_vecHeight.size();
	 IndexX = sqrt(MapSize); // x축 인덱스 총수
	 Indexy = IndexX;		// y축 인덱스 총수
	 NumTile = IndexX; // 한 줄당 타일 갯수00
	 tileSpacing = m_CoodVecVertex[0].x*(-1) + m_CoodVecVertex[1].x;
	float startX = MinX;
	float endX = MaxX+1;
	float startZ = MinZ;
	float endZ = MaxZ;

	 int g = 0;
	 for (float z = startZ; z <= endZ; z += tileSpacing)
	 {
		 int h = 0;
		 for (float x = startX; x <= endX; x += tileSpacing)
		 {
			 int index = g *NumTile + h;
			 D3DXVECTOR3 p(x, m_vecHeight[index], z);
			 m_vecTerrainVertex.push_back(p);
			 h++;
		 }
		 g++;
	 }

	 for (int i = 0; i < m_vecTerrainVertex.size(); ++i)
	 {
		 for (int j = 0; j < m_CoodVecVertex.size(); ++j)
		 {
			 if (fabs(m_vecTerrainVertex[i].x - m_CoodVecVertex[j].x) < M_EPSILON&&
				 fabs(m_vecTerrainVertex[i].z - m_CoodVecVertex[j].z) < M_EPSILON)
			 {
				 m_vecTerrainVertex[i].y = m_CoodVecVertex[j].y;
				 break;
			 }
		 }
		 
	 }
	 int c = 0;
	/*int index;
	for (size_t i = 0; i < NumTile; i++)
	{
		for (size_t j = 0; j < NumTile; j++)
		{
			index = i*NumTile + j;
			m_vecTerrainVertex.push_back(D3DXVECTOR3(j, ((float)m_vecHeight[index]), i));
		}
	}*/

	for (int i = 0; i < m_vecPNTVertex.size(); ++i)
	{
		cBoundingSphere* BoundingSphere = new cBoundingSphere;
		BoundingSphere->Setup(&D3DXVECTOR3(0, 0, 0), 3.0f, 20, 20);
		m_vecBoundingSphere.push_back(BoundingSphere);
	}

}
bool cMap::GetHeight(IN float x, OUT float& y, IN float z)
{
	/*if (x < 0 || z < 0 || x > NumTile + 1 || z > NumTile + 1)
	{
		return false;
	}*/

	if (x < -210 || z < -210 || x > 558|| z > 558)
	{
	return false;
	}



	float fDeltaX;
	float fDeltaZ;
	float fMinx = MinX*(-1);
	float fMinz = MinZ*(-1);

	float nX = x;
	float nZ = z;
	int intX = x;
	int intZ = z;
	fDeltaX = x - intX;
	fDeltaZ = z - intZ;
	/*if (nX >= 0)
	{
		fDeltaX = x - nX;
	}
	else if (nX < 0)
	{
		nX *= -1;
		fDeltaX = (x*(-1)) - nX;
	}
	
	if (nZ >= 0)
	{
		fDeltaZ = z - nZ;
	}
	else if (nZ < 0)
	{
		nZ *= -1;
		fDeltaZ = (z*(-1)) - nZ;
	}*/
	//		1--3
	//		|\ |
	//		| \|
	//		0--2
	int Ze, Xe;
	int ze = (((nZ + fMinz) / tileSpacing) + 0);
	int num = NumTile;
	int xe = ((nX + fMinx) / tileSpacing);

	int _0 = ze*num + xe;
	int _1 = (ze+1)*num + xe;
	int _2 = ze*num + xe+1;
	int _3 = (ze+1)*num + xe+1;

	//int _1 = (((nZ + fMinz) / tileSpacing) + 1) * (NumTile)+((nX + fMinx) / tileSpacing);
	//int _2 = (((nZ + fMinz) / tileSpacing) + 0) * (NumTile)+((nX + fMinx) / tileSpacing) + 1;
	//int _3 = (((nZ + fMinz) / tileSpacing) + 1) * (NumTile)+((nX + fMinx) / tileSpacing) + 1;

	if (fDeltaX + fDeltaZ < 1)
	{
		D3DXVECTOR3 v01 = m_vecTerrainVertex[_1] - m_vecTerrainVertex[_0];
		D3DXVECTOR3 v02 = m_vecTerrainVertex[_2] - m_vecTerrainVertex[_0];
		v01 *= fDeltaZ;
		v02 *= fDeltaX;
		y = (v01 + v02).y + m_vecTerrainVertex[_0].y;
		
	}
	else
	{
		fDeltaX = 1 - fDeltaX;
		fDeltaZ = 1 - fDeltaZ;
		D3DXVECTOR3 v31 = m_vecTerrainVertex[_1] - m_vecTerrainVertex[_3];
		D3DXVECTOR3 v32 = m_vecTerrainVertex[_2] - m_vecTerrainVertex[_3];
		v31 *= fDeltaX;
		v32 *= fDeltaZ;
		y = (v31 + v32).y + m_vecTerrainVertex[_3].y;
	}
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