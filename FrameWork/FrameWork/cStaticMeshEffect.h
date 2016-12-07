#pragma once
#include "cStaticObj.h"
class cStaticMeshEffect : public cStaticObj
{
private:

public:
	cStaticMeshEffect(char* szFolder, char* szFilename);
	~cStaticMeshEffect();

	HRESULT Setup();
	void Update();
	void Render();


};

