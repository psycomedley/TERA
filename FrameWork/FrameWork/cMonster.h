#pragma once
#include "cDynamicObj.h"

class cMonster : public cDynamicObj
{
protected:
	ST_UNIT_INFO	m_stInfo;

public:
	virtual void Update() override;

public:
	cMonster(char* szFolder, char* szFilename);
	~cMonster();

protected:
	cMonster();
};

