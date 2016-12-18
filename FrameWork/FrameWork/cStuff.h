#pragma once

#include"cStaticMesh.h"
#include"cStaticObj.h"
class cStuff :public cStaticObj
{
private:
	D3DXMATRIXA16 matWorld;
	SYNTHESIZE(int, a, ab);

public:
	cStuff(char* szFolder, char* szFilename);
	~cStuff();

	virtual void Update() override;
	virtual void Render() override;

private:
	cStuff();
};

