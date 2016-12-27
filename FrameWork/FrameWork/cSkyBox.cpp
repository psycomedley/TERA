#include "stdafx.h"
#include "cSkyBox.h"


cSkyBox::cSkyBox()
	:m_VB(NULL)
	, m_IB(NULL)
{
	for (int i = 0; i < 6; ++i)
		m_pTexture[i] = NULL;
}


cSkyBox::~cSkyBox()
{
}
void cSkyBox::Release()
{
	for (int i = 0; i < 6; i++)
	SAFE_RELEASE(m_pVB[i]);
	for (int i = 0; i < 6; i++)
	SAFE_RELEASE(m_pIB[i]);

	SAFE_RELEASE(m_VB);
}
void cSkyBox::SetUp()
{


	m_pTexture[0] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0A0.tga");
	m_pTexture[1] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0A1.tga");
	m_pTexture[2] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0B0.tga");
	m_pTexture[3] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0B1.tga");
	m_pTexture[4] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0C0.tga");
	m_pTexture[5] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0C1.tga");

	g_pD3DDevice->CreateVertexBuffer(24 * sizeof(SKYVERTEX), D3DUSAGE_WRITEONLY, SKYVERTEX::FVF,
		D3DPOOL_DEFAULT, &m_VB, NULL);

	SKYVERTEX vertices[24] =
	{
		{ -250.0f, 250.0f, -250.0f, 0.0f, 0.0f },		// Top vertices
		{ 250.0f, 250.0f, -250.0f, 1.0f, 0.0f },
		{ -250.0f, 250.0f, 250.0f, 0.0f, 1.0f },
		{ 250.0f, 250.0f, 250.0f, 1.0f, 1.0f },

		{ -250.0f, 250.0f, 250.0f, 0.0f, 0.0f },		// Front vertices
		{ 250.0f, 250.0f, 250.0f, 1.0f, 0.0f },
		{ -250.0f, -250.0f, 250.0f, 0.0f, 1.0f },
		{ 250.0f, -250.0f, 250.0f, 1.0f, 1.0f },

		{ 250.0f, 250.0f, -250.0f, 0.0f, 0.0f },		// Back vertices
		{ -250.0f, 250.0f, -250.0f, 1.0f, 0.0f },
		{ 250.0f, -250.0f, -250.0f, 0.0f, 1.0f },
		{ -250.0f, -250.0f, -250.0f, 1.0f, 1.0f },

		{ -250.0f, 250.0f, -250.0f, 0.0f, 0.0f },		// Left vertices
		{ -250.0f, 250.0f, 250.0f, 1.0f, 0.0f },
		{ -250.0f, -250.0f, -250.0f, 0.0f, 1.0f },
		{ -250.0f, -250.0f, 250.0f, 1.0f, 1.0f },

		{ 250.0f, 250.0f, 250.0f, 0.0f, 0.0f },		// Right vertices
		{ 250.0f, 250.0f, -250.0f, 1.0f, 0.0f },
		{ 250.0f, -250.0f, 250.0f, 0.0f, 1.0f },
		{ 250.0f, -250.0f, -250.0f, 1.0f, 1.0f },

		{ -250.0f, -250.0f, 250.0f, 0.0f, 0.0f },		// Bottom vertices
		{ 250.0f, -250.0f, 250.0f, 1.0f, 0.0f },
		{ -250.0f, -250.0f, -250.0f, 0.0f, 1.0f },
		{ 250.0f, -250.0f, -250.0f, 1.0f, 1.0f }
	};

	VOID* pVertices;
	m_VB->Lock(0, 24 * sizeof(SKYVERTEX), (void**)&pVertices, 0);
	memcpy(pVertices, vertices, 24 * sizeof(SKYVERTEX));
	m_VB->Unlock();


	//for (int i = 0; i < 6; i++)
	//{
	//	g_pD3DDevice->CreateVertexBuffer(sizeof(ST_PT_VERTEX) * 4, 0, ST_PT_VERTEX::FVF,
	//		D3DPOOL_DEFAULT, &m_pVB[i], NULL);
	//}
	//ST_PT_VERTEX* vertaxies;
	//vector<ST_PT_VERTEX> vecVertax[6];


	////top
	//m_pVB[0]->Lock(0, 0, (void**)&vertaxies, 0);
	//vecVertax[0].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, -250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	//vecVertax[0].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, -250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	//vecVertax[0].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, 250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	//vecVertax[0].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, 250.0f), D3DXVECTOR2(1.0f, 1.0f)));
	//memcpy(vertaxies, &vecVertax[0][0], vecVertax[0].size()*sizeof(ST_PT_VERTEX));
	//m_pVB[0]->Unlock();

	////front
	//m_pVB[1]->Lock(0, 0, (void**)&vertaxies, 0);
	//vecVertax[1].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, 250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	//vecVertax[1].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, 250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	//vecVertax[1].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, 250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	//vecVertax[1].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, 250.0f), D3DXVECTOR2(1.0f, 1.0f)));
	//memcpy(vertaxies, &vecVertax[1][0], vecVertax[1].size()*sizeof(ST_PT_VERTEX));
	//m_pVB[1]->Unlock();

	////back
	//m_pVB[2]->Lock(0, 0, (void**)&vertaxies, 0);
	//vecVertax[2].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, -250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	//vecVertax[2].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, -250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	//vecVertax[2].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, -250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	//vecVertax[2].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, -250.0f), D3DXVECTOR2(1.0f, 1.0f)));
	//memcpy(vertaxies, &vecVertax[2][0], vecVertax[2].size()*sizeof(ST_PT_VERTEX));
	//m_pVB[2]->Unlock();

	////left
	//m_pVB[3]->Lock(0, 0, (void**)&vertaxies, 0);
	//vecVertax[3].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, -250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	//vecVertax[3].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, 250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	//vecVertax[3].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, -250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	//vecVertax[3].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, 250.0f), D3DXVECTOR2(1.0f, 1.0f)));
	//memcpy(vertaxies, &vecVertax[3][0], vecVertax[3].size()*sizeof(ST_PT_VERTEX));
	//m_pVB[3]->Unlock();

	////right
	//m_pVB[4]->Lock(0, 0, (void**)&vertaxies, 0);
	//vecVertax[4].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, 250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	//vecVertax[4].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, -250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	//vecVertax[4].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, 250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	//vecVertax[4].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, -250.0f), D3DXVECTOR2(1.0f, 1.0f)));
	//memcpy(vertaxies, &vecVertax[4][0], vecVertax[4].size()*sizeof(ST_PT_VERTEX));
	//m_pVB[4]->Unlock();

	////bottom
	//m_pVB[5]->Lock(0, 0, (void**)&vertaxies, 0);
	//vecVertax[5].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, 250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	//vecVertax[5].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, 250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	//vecVertax[5].push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, -250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	//vecVertax[5].push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, -250.0f), D3DXVECTOR2(1.0f, 1.0f)));
	//memcpy(vertaxies, &vecVertax[5][0], vecVertax[5].size()*sizeof(ST_PT_VERTEX));
	//m_pVB[5]->Unlock();


	//for (int i = 0; i < 6; i++)
	//{
	//	g_pD3DDevice->CreateIndexBuffer(sizeof(DWORD) * 12, 0,
	//		D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB[i], NULL);
	//}
	//m_vecIndex.push_back(0); m_vecIndex.push_back(1); m_vecIndex.push_back(2);
	//m_vecIndex.push_back(0); m_vecIndex.push_back(2); m_vecIndex.push_back(3);

	//DWORD* Index;
	//for (int i = 0; i < 6; i++)
	//{
	//	m_pIB[i]->Lock(0, 0, (void**)&Index, 0);
	//	memcpy(Index, &m_vecIndex[0], m_vecIndex.size()*sizeof(DWORD));
	//	m_pIB[i]->Unlock();
	//}
	/*m_vecIndex.push_back(0); m_vecIndex.push_back(1); m_vecIndex.push_back(2);
	m_vecIndex.push_back(0); m_vecIndex.push_back(2); m_vecIndex.push_back(3);

	m_vecIndex.push_back(7); m_vecIndex.push_back(6); m_vecIndex.push_back(4);
	m_vecIndex.push_back(7); m_vecIndex.push_back(4); m_vecIndex.push_back(5);

	m_vecIndex.push_back(11); m_vecIndex.push_back(10); m_vecIndex.push_back(8);
	m_vecIndex.push_back(11); m_vecIndex.push_back(8); m_vecIndex.push_back(9);

	m_vecIndex.push_back(15); m_vecIndex.push_back(14); m_vecIndex.push_back(12);
	m_vecIndex.push_back(15); m_vecIndex.push_back(12); m_vecIndex.push_back(13);

	m_vecIndex.push_back(19); m_vecIndex.push_back(18); m_vecIndex.push_back(16);
	m_vecIndex.push_back(19); m_vecIndex.push_back(16); m_vecIndex.push_back(17);

	m_vecIndex.push_back(20); m_vecIndex.push_back(21); m_vecIndex.push_back(23);
	m_vecIndex.push_back(20); m_vecIndex.push_back(23); m_vecIndex.push_back(22);*/

	/*g_pD3DDevice->CreateVertexBuffer(m_vecVertax.size() * sizeof(ST_PT_VERTEX), D3DUSAGE_WRITEONLY, ST_PT_VERTEX::FVF,
		D3DPOOL_MANAGED, &m_pVB, NULL);
	VOID* vertaxies = NULL;
	m_pVB->Lock(0, 0, (void**)&vertaxies, 0);
	memcpy(vertaxies, &m_vecVertax[0], 24*sizeof(ST_PT_VERTEX));
	m_pVB->Unlock();

	g_pD3DDevice->CreateIndexBuffer(sizeof(WORD) * 36, 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);
	VOID* Indecies = NULL;
	m_pIB->Lock(0, 0, (void**)&Indecies, 0);
	memcpy(Indecies, &m_vecIndex[0], m_vecIndex.size()*sizeof(WORD));
	m_pIB->Unlock();*/
}
void cSkyBox::Render()
{
	D3DXMATRIX mat;
	D3DXMatrixIdentity(&mat);
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	// D3DSAMP_ADDRESSU : u 좌표로 사용하는 텍스처어드레싱모드. 디폴트는 D3DTADDRESS_WRAP 이다. 더 자세한 정보는, 「D3DTEXTUREADDRESS 」를 참조할것. 
	// D3DSAMP_ADDRESSV : v 좌표로 사용하는 텍스처어드레싱모드. 디폴트는 D3DTADDRESS_WRAP 이다. 더 자세한 정보는, 「D3DTEXTUREADDRESS 」를 참조할것. 
	// D3DTADDRESS_CLAMP: 범위 [0.0, 1.0] 의 외측의 텍스처 좌표가, 각각, 0.0 으로 1.0 의 텍스처 컬러로 설정된다. 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);

	
	g_pD3DDevice->SetFVF(SKYVERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_VB, 0, sizeof(SKYVERTEX));
	for (int i = 0; i < 6; i++)
	{
		g_pD3DDevice->SetTexture(0, m_pTexture[i]);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

	//for (int i = 0; i < 6; i++)
	//{
	//	g_pD3DDevice->SetTexture(0, m_pTexture[i]);
	//	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	//	g_pD3DDevice->SetStreamSource(0, m_pVB[i], 0, sizeof(ST_PT_VERTEX));
	//	g_pD3DDevice->SetIndices(m_pIB[i]);
	//	g_pD3DDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2); //정점갯수 , 0 , 그릴 도형갯수
	//}

	//g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0,m_vecVertax.size());

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);
}