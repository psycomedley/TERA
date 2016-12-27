#include "stdafx.h"
#include "cSkyBox.h"


cSkyBox::cSkyBox()
	:m_pVB(NULL)
{
	for (int i = 0; i < 6; ++i)
		m_pTexture[i] = NULL;
}


cSkyBox::~cSkyBox()
{
}
void cSkyBox::Release()
{
	SAFE_RELEASE(m_pVB);
}
void cSkyBox::SetUp()
{
	g_pD3DDevice->CreateVertexBuffer(24 * sizeof(ST_PT_VERTEX), D3DUSAGE_WRITEONLY, ST_PT_VERTEX::FVF,
		D3DPOOL_DEFAULT, &m_pVB, NULL);

	m_pTexture[0] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0A0.tga");
	m_pTexture[1] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0A1.tga");
	m_pTexture[2] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0B0.tga");
	m_pTexture[3] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0B1.tga");
	m_pTexture[4] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0C0.tga");
	m_pTexture[5] = GETSINGLE(cTextureMgr)->GetTexture("Map/skyImage/ASW_TOC_L0C1.tga");

	//top
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, -250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, -250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, 250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, 250.0f), D3DXVECTOR2(1.0f, 1.0f)));

	//front
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, 250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, 250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, 250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, 250.0f), D3DXVECTOR2(1.0f, 1.0f)));

	//back

	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, -250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, -250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, -250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, -250.0f), D3DXVECTOR2(1.0f, 1.0f)));

	//left
	
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, -250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, 250.0f, 250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, -250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, 250.0f), D3DXVECTOR2(1.0f, 1.0f)));

	//right
	
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, 250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, 250.0f, -250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, 250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, -250.0f), D3DXVECTOR2(1.0f, 1.0f)));

	//bottom
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, 250.0f), D3DXVECTOR2(0.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, 250.0f), D3DXVECTOR2(1.0f, 0.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(-250.0f, -250.0f, -250.0f), D3DXVECTOR2(0.0f, 1.0f)));
	m_vecVertax.push_back(ST_PT_VERTEX(D3DXVECTOR3(250.0f, -250.0f, -250.0f), D3DXVECTOR2(1.0f, 1.0f)));



	VOID* vertaxies = NULL;
	m_pVB->Lock(0, 24 * sizeof(ST_PT_VERTEX), (void**)&vertaxies, 0);
	memcpy(vertaxies, &m_vecVertax, 24*sizeof(ST_PT_VERTEX));
	m_pVB->Unlock();

}
void cSkyBox::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	// D3DSAMP_ADDRESSU : u 좌표로 사용하는 텍스처어드레싱모드. 디폴트는 D3DTADDRESS_WRAP 이다. 더 자세한 정보는, 「D3DTEXTUREADDRESS 」를 참조할것. 
	// D3DSAMP_ADDRESSV : v 좌표로 사용하는 텍스처어드레싱모드. 디폴트는 D3DTADDRESS_WRAP 이다. 더 자세한 정보는, 「D3DTEXTUREADDRESS 」를 참조할것. 
	// D3DTADDRESS_CLAMP: 범위 [0.0, 1.0] 의 외측의 텍스처 좌표가, 각각, 0.0 으로 1.0 의 텍스처 컬러로 설정된다. 
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	g_pD3DDevice->SetFVF(ST_PT_VERTEX::FVF);
	g_pD3DDevice->SetStreamSource(0, m_pVB, 0, sizeof(ST_PT_VERTEX));
	for (int i = 0; i < 6; i++)
	{
		g_pD3DDevice->SetTexture(0, m_pTexture[i]);
		g_pD3DDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, i*4,2);
	}
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	g_pD3DDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
}