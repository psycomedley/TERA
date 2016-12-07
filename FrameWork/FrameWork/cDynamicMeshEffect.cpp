#include "stdafx.h"
#include "cDynamicMeshEffect.h"


<<<<<<< HEAD

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

cDynamicMeshEffect::cDynamicMeshEffect(char * szFolder, char * szFilename)
=======
cDynamicMeshEffect::cDynamicMeshEffect(char* szFolder, char* szFilename)
>>>>>>> f066ad06ff51ddca91a3deab0d1081d14c69b0c7
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
