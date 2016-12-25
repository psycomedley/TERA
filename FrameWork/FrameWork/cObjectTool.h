#pragma once

#include "cStaticObj.h"

class cStuff;

class cObjectTool :public cStaticObj
{
private:
	cStaticObj*		m_BodyStuff;
	int				m_RotDirection;
	float			m_fRx, m_fRy, m_fRz;
	D3DXVECTOR3		m_vScaling;
	D3DXVECTOR3		m_vPosition;
	D3DXVECTOR3 playerPos;
	bool			m_IsSelect[4];

public:
	cObjectTool();
	~cObjectTool();
	
	void Setup();
	void ResetVariable();
	void Update() override;
	void Render() override;


	void ChangeBodyStuff();
	void ChangeScaleAndAngle();
	void AddClone();
	cStuff* CopyInfoToClone(cStaticObj* BodyStuff, cStuff* CloneStuff);
	void SaveInfoStuff(cStuff* CloneStuff);
	void LoadInfoStuff();
};

