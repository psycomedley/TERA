#pragma once
#include "cDynamicObj.h"
class cDynamicMeshEffect : public cDynamicObj
{
private:

public:
	cDynamicMeshEffect(char* szFolder, char* szFilename);
	~cDynamicMeshEffect();

	HRESULT Setup();
	void Update();
	void Render();
};

