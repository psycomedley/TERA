#include "stdafx.h"
#include "cObjectToolMgr.h"
#include "cStuff.h"
#include "cStaticMesh.h"
#include "cStaticObj.h"


cObjectToolMgr::cObjectToolMgr()
{
}


cObjectToolMgr::~cObjectToolMgr()
{
}
void cObjectToolMgr::Setup()
{
	cStuff* pTree = new cStuff("Object", "tree1.x");
	GETSINGLE(cObjMgr)->AddStuff("³ª¹«1", pTree);
}
void cObjectToolMgr::Render()
{

}