#include "stdafx.h"
#include "cDynamicMeshEffect.h"


//void cDynamicMeshEffect::ChangeState(iState * pState, int nSkillIndex)
//{
//}
//
//void cDynamicMeshEffect::ChangeState(int pState, int nSkillIndex)
//{
//}
//
//bool cDynamicMeshEffect::IsMoveAble()
//{
//
//	return false;
//}

cDynamicMeshEffect::cDynamicMeshEffect(char* szFolder, char* szFilename)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);
}

cDynamicMeshEffect::~cDynamicMeshEffect()
{
}
HRESULT cDynamicMeshEffect::Setup()
{
	ST_ANIMATION_INFO aniInfo(0, false, true);
	AddAnimation(aniInfo);
	AnimationStart();
	
	return S_OK;
}


void cDynamicMeshEffect::Update()
{
	
}


void cDynamicMeshEffect::Render()
{
	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, true);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAREF, 0x00000088);
	g_pD3DDevice->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);
	UpdateAndRender();

	g_pD3DDevice->SetRenderState(D3DRS_ALPHATESTENABLE, false);
}
