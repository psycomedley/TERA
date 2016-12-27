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
	SAFE_RELEASE(m_VB);
}
void cSkyBox::SetUp()
{



	m_pTexture[0] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage2/ATW_cloud_L0D.tga");
	m_pTexture[1] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage2/ATW_cloud_L0A.tga");
	m_pTexture[2] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage2/ATW_cloud_L0C-1.tga");
	m_pTexture[3] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage2/ATW_cloud_L0C.tga");
	m_pTexture[4] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage2/ATW_cloud_L0B.tga");
	m_pTexture[5] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage2/ASW_TOC_Lz0.tga");
//ATW_cloud_L0C-1
	g_pD3DDevice->CreateVertexBuffer(24 * sizeof(SKYVERTEX), D3DUSAGE_WRITEONLY, SKYVERTEX::FVF,
		D3DPOOL_DEFAULT, &m_VB, NULL);

	SKYVERTEX vertices[24] =
	{
		{ -512.0f, 512.0f, -512.0f, 0.0f, 0.0f },		// Top vertices
		{ 512.0f, 512.0f, -512.0f, 1.0f, 0.0f },
		{ -512.0f, 512.0f, 512.0f, 0.0f, 1.0f },
		{ 512.0f, 512.0f, 512.0f, 1.0f, 1.0f },

		{ -512.0f, 512.0f, 512.0f, 0.0f, 0.0f },		// Front vertices
		{ 512.0f, 512.0f, 512.0f, 1.0f, 0.0f },
		{ -512.0f, -512.0f, 512.0f, 0.0f, 1.0f },
		{ 512.0f, -512.0f, 512.0f, 1.0f, 1.0f },

		{ 512.0f, 512.0f, -512.0f, 0.0f, 0.0f },		// Back vertices
		{ -512.0f, 512.0f, -512.0f, 1.0f, 0.0f },
		{ 512.0f, -512.0f, -512.0f, 0.0f, 1.0f },
		{ -512.0f, -512.0f, -512.0f, 1.0f, 1.0f },

		{ -512.0f, 512.0f, -512.0f, 0.0f, 0.0f },		// Left vertices
		{ -512.0f, 512.0f, 512.0f, 1.0f, 0.0f },
		{ -512.0f, -512.0f, -512.0f, 0.0f, 1.0f },
		{ -512.0f, -512.0f, 512.0f, 1.0f, 1.0f },

		{ 512.0f, 512.0f, 512.0f, 0.0f, 0.0f },		// Right vertices
		{ 512.0f, 512.0f, -512.0f, 1.0f, 0.0f },
		{ 512.0f, -512.0f, 512.0f, 0.0f, 1.0f },
		{ 512.0f, -512.0f, -512.0f, 1.0f, 1.0f },

		{ -512.0f, -512.0f, 512.0f, 0.0f, 0.0f },		// Bottom vertices
		{ 512.0f, -512.0f, 512.0f, 1.0f, 0.0f },
		{ -512.0f, -512.0f, -512.0f, 0.0f, 1.0f },
		{ 512.0f, -512.0f, -512.0f, 1.0f, 1.0f }
	};

	VOID* pVertices;
	m_VB->Lock(0, 24 * sizeof(SKYVERTEX), (void**)&pVertices, 0);
	memcpy(pVertices, vertices, 24 * sizeof(SKYVERTEX));
	m_VB->Unlock();


}
void cSkyBox::Render()
{
	D3DXMATRIX mat,matT;
	D3DXMatrixIdentity(&mat);
	D3DXMatrixTranslation(&matT, 100, 450, 200);
	mat = matT;
	g_pD3DDevice->SetTransform(D3DTS_WORLD, &mat);

	// D3DSAMP_ADDRESSU : u 좌표로 사용하는 텍스처어드레싱모드. 디폴트는 D3DTADDRESS_WRAP 이다. 더 자세한 정보는, 「D3DTEXTUREADDRESS 」를 참조할것. 
	// D3DSAMP_ADDRESSV : v 좌표로 사용하는 텍스처어드레싱모드. 디폴트는 D3DTADDRESS_WRAP 이다. 더 자세한 정보는, 「D3DTEXTUREADDRESS 」를 참조할것. 
	// D3DTADDRESS_CLAMP: 범위 [0.0, 1.0] 의 외측의 텍스처 좌표가, 각각, 0.0 으로 1.0 의 텍스처 컬러로 설정된다. 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, false);	//조명 끄기

	
	g_pD3DDevice->SetFVF(SKYVERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_VB, 0, sizeof(SKYVERTEX));
	for (int i = 0; i < 6; i++)
	{
		g_pD3DDevice->SetTexture(0, m_pTexture[i]);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	g_pD3DDevice->SetRenderState(D3DRS_LIGHTING, true);



}