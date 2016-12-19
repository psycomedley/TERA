#pragma once

#include"cStaticMesh.h"
#include"cStaticObj.h"
class cStuff :public cStaticObj
{
private:
	D3DXMATRIXA16	m_matWorld;
	
	D3DXMATRIXA16	m_matS, m_matT;
	D3DXMATRIXA16	m_matRX, m_matRY, m_matRZ;
	D3DXVECTOR3		m_vPosition, m_vScale;
	float			m_fRotX, m_fRotY, m_fRotZ;

public:
	cStuff(char* szFolder, char* szFilename);
	~cStuff();

	virtual void Update() override;
	virtual void Render() override;

private:
	cStuff();
};

