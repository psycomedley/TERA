#pragma once
#include "cDynamicObj.h"

class cUIObject;
class cMonster : public cDynamicObj
{
protected:
	bool			m_bIsBattle;
	float			m_fDetectRange;
//	float			m_fHpRatio;
	cUIObject*		m_pUIHp;
	SYNTHESIZE(ST_UNIT_INFO, m_stInfo, Info);

public:
	void SetName(string sName) { m_stInfo.sName = sName; }
	void SetMaxHp(float fMaxHp) { m_stInfo.fMaxHp = fMaxHp; }
	void SetHp(float fHp) { m_stInfo.fHp = fHp; }
	void SetMaxMp(float fMaxMp) { m_stInfo.fMaxMp = fMaxMp; }
	void SetMp(float fMp) { m_stInfo.fMp = fMp; }
	void SetDamage(float fDamage) { m_stInfo.fDamage = fDamage; }
	void SetDefence(float fDefence) { m_stInfo.fDefence = fDefence; }

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

