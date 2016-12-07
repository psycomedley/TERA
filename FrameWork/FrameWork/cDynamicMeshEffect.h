#pragma once
#include "cDynamicObj.h"
class cDynamicMeshEffect 
{
private:

public:
	cDynamicMeshEffect(char* szFolder, char* szFilename);
	~cDynamicMeshEffect();

	HRESULT Setup();
	void Update();
	void Render();
};

