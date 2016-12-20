#pragma once

#include"cStaticObj.h"
class cStuff :public cStaticObj
{
private:
	D3DXMATRIXA16	m_matWorld;
	
	D3DXMATRIXA16	m_matS, m_matT;
	SYNTHESIZE(bool, m_IsCullMode, IsCullMode);
	SYNTHESIZE(DWORD, m_SubSetNum, SubSetNum);
	SYNTHESIZE(char*, m_sfilename, Filename);
	SYNTHESIZE(char*, m_sFoldername, Foldername);

public:
	cStuff(char* szFolder, char* szFilename);
	~cStuff();

	virtual void Update() override;
	virtual void Render() override;

private:
	cStuff();
};

