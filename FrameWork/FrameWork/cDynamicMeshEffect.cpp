#include "stdafx.h"
#include "cDynamicMeshEffect.h"

cDynamicMeshEffect::cDynamicMeshEffect(char* szFolder, char* szFilename)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);
}


cDynamicMeshEffect::~cDynamicMeshEffect()
{
}


HRESULT cDynamicMeshEffect::Setup()
{
	return S_OK;
}


void cDynamicMeshEffect::Update()
{

}


void cDynamicMeshEffect::Render()
{
	AnimationStart();
	UpdateAndRender();
}
