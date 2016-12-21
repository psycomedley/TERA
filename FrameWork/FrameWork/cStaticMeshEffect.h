#pragma once
#include "cStaticObj.h"
class cStaticMeshEffect : public cStaticObj
{
private:
	float m_fAngle;
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	SYNTHESIZE(bool, m_bProcess, Process);
	SYNTHESIZE(string, m_sName, Name);

public:
	cStaticMeshEffect(char* szFolder, char* szFilename);
	~cStaticMeshEffect();

	HRESULT Setup(D3DXVECTOR3 s, D3DXVECTOR3 t, float Angle);
	void Update();
	void Render();


};

