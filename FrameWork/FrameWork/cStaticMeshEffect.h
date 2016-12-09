#pragma once
#include "cStaticObj.h"
class cStaticMeshEffect : public cStaticObj
{
private:

	D3DXMATRIXA16 matWorld, matS, matR, matT;

public:
	cStaticMeshEffect(char* szFolder, char* szFilename);
	~cStaticMeshEffect();

	HRESULT Setup();
	void Update();
	void Render();


};

