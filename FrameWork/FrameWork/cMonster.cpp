#include "stdafx.h"
#include "cMonster.h"


cMonster::cMonster(char* szFolder, char* szFilename)
{
	m_pMesh = new cDynamicMesh(szFolder, szFilename);
}


cMonster::cMonster()
{
}


cMonster::~cMonster()
{
}
