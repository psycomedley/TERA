#pragma once

#include "cStaticObj.h"


class cObjectTool :public cStaticObj
{
private:
	cStaticObj*		m_BodyStuff;
	int				m_RotDirection;
	float			m_fRx, m_fRy, m_fRz;
	D3DXVECTOR3		m_vScaling;
public:
	cObjectTool();
	~cObjectTool();
	
	void Setup();
	void ResetVariable();
	void Update() override;
	void ChangeBodyStuff();
	void ChangeScaleAndAngle();
};

