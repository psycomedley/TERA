#pragma once
#include "cGameObject.h"
#include "cStaticMesh.h"

class cStaticObj : public cGameObject
{
public:
	virtual void Update();
	virtual void Render() override;

public:
	cStaticObj(char* szFolder, char* szFilename);
	cStaticObj();
	~cStaticObj();
};

