#pragma once
#include "cDynamicObj.h"

class cUIObject;
class cBoundingBox;
class cMonster : public cDynamicObj
{
protected:
	bool				m_bIsBattle;
	float				m_fDetectRange;
//	float				m_fHpRatio;
	cUIObject*			m_pUIHp;

	cBoundingSphere*	m_pShotSphere;
	cBoundingBox*		m_pMoveColBox;
	cBoundingSphere*	m_pMoveColSphere;

public:
	float GetMaxHp() { return m_stInfo.fMaxHp; }
	cBoundingSphere GetShotSphere();
	cBoundingBox GetMoveColBox();
	cBoundingSphere GetMoveColSphere();

	void SetName(string sName) { m_stInfo.sName = sName; }
	void SetMaxHp(float fMaxHp) { m_stInfo.fMaxHp = fMaxHp; }
	void SetHp(float fHp) { m_stInfo.fHp = fHp; }
	void SetMaxMp(float fMaxMp) { m_stInfo.fMaxMp = fMaxMp; }
	void SetMp(float fMp) { m_stInfo.fMp = fMp; }
//	void SetDamage(float fDamage) { m_stInfo.fDamage = fDamage; }
	void SetDefence(float fDefence) { m_stInfo.fDefence = fDefence; }
	
	void SetShotSphere(float fRadius);
	void SetBox();
	void ResetHp();

public:
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat = NULL, bool bRender = true) override;

public:
	cMonster(char* szFolder, char* szFilename);
	~cMonster();

protected:
	cMonster();
	virtual void SetupState() PURE;
	virtual void SetupStatus() PURE;
	virtual void Update() override;
};

