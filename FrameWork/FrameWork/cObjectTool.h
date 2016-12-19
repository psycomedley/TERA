#pragma once

#include "cStaticObj.h"

class cObjectTool :public cStaticObj
{
private:
	cStaticObj* m_BodyStuff;

public:
	cObjectTool();
	~cObjectTool();
	
	void Setup();
	void Update() override;
};

