#pragma once
#include "cStaticObj.h"
class cRushEffect : public cStaticObj
{
private:
	D3DXMATRIXA16 matWorld, matS, matR, matT;
	float m_fAngle;
	int needWheels;
	int nowWheels;
	float m_fRotationSpeed;
	bool start;
	bool isLeft;

public:
	cRushEffect(char* szFolder, char* szFilename);
	~cRushEffect();
	HRESULT Setup(int Wheels, float RotationSpeed, bool Left,
		D3DXVECTOR3 s, D3DXVECTOR3 t);
	void Update();
	void Render();
	void Start()
	{
		start = true;
	}
	void Stop()
	{
		m_fAngle = 0.0f;
		nowWheels = 0;
		start = false;
	}
};

