#pragma once
#include "cStaticObj.h"
class cPlayer;
class cStraightEffect : public cStaticObj
{
private:
	D3DXMATRIXA16 matWorld, matS, matR, matT, saveMatT;
	bool start;
	float m_fStraightSpeed;

public:
	cStraightEffect(char* szFolder, char* szFilename);
	~cStraightEffect();
	HRESULT Setup(float StraightSpeed, D3DXVECTOR3 s, D3DXVECTOR3 t);
	void Update();
	void Render();
	void Start()
	{
		start = true;
	}
	void Stop()
	{
		start = false;
		matT = saveMatT;
	}
};

