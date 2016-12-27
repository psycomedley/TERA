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
	float RealAngle;


public:
	cCircleEffect(char* szFolder, char* szFilename);
	~cCircleEffect();
	HRESULT Setup(int Wheels, float RotationSpeed, bool Left,
		D3DXVECTOR3 s, D3DXVECTOR3 t, float Angle);
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
	bool IsStart()
	{
		return start;
	}
	void SetPosition(D3DXVECTOR3 t);
};

