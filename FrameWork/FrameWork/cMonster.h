#pragma once
#include "cDynamicObj.h"

class cMonster : public cDynamicObj
{
protected:
	SYNTHESIZE(ST_UNIT_INFO, m_stInfo, Info);

	bool			m_bIsBattle;
	float			m_fDetectRange;

public:
	void SetName(string sName) { m_stInfo.sName = sName; }
	void SetMaxHp(int nMaxHp) { m_stInfo.nMaxHp = nMaxHp; }
	void SetHp(int nHp) { m_stInfo.nHp = nHp; }
	void SetMaxMp(int nMaxMp) { m_stInfo.nMaxMp = nMaxMp; }
	void SetMp(int nMp) { m_stInfo.nMp = nMp; }
	void SetDamage(int fDamage) { m_stInfo.fDamage = fDamage; }
	void SetDefence(int fDefence) { m_stInfo.fDefence = fDefence; }

public:
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat = NULL) override;

public:
	cMonster(char* szFolder, char* szFilename);
	~cMonster();

protected:
	cMonster();
	virtual void SetupState() PURE;
	virtual void SetupStatus() PURE;
	virtual void Update() override;
};

