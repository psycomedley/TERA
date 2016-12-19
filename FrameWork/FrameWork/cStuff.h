#pragma once

#include"cStaticObj.h"
class cStuff :public cStaticObj
{
private:
	D3DXMATRIXA16	m_matWorld;
	
	D3DXMATRIXA16	m_matS, m_matT;
	D3DXMATRIXA16	m_matRX, m_matRY, m_matRZ;
	SYNTHESIZE(float, m_fRotX, RotX);
	SYNTHESIZE(float, m_fRotY, RotY);
	SYNTHESIZE(float, m_fRotZ, RotZ);
	SYNTHESIZE(bool, m_IsCullMode, IsCullMode);
	SYNTHESIZE(DWORD, m_SubSetNum, SubSetNum);

public:
	cStuff(char* szFolder, char* szFilename);
	~cStuff();

	virtual void Update() override;
	virtual void Render() override;

private:
	cStuff();
};

