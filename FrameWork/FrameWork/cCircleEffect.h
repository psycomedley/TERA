#pragma once
#include "cStaticObj.h"
class cCircleEffect : public cStaticObj
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
	cCircleEffect(char* szFolder, char* szFilename);
	~cCircleEffect();
	HRESULT Setup(int Wheels, float RotationSpeed, bool Left);
	void Update();
	void Render();
	float GetNowWheels()
	{
		return nowWheels;
	}
	void ResetAngle()
	{
		m_fAngle = 0.0f;
	}
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

