#pragma once
#include "cDynamicObj.h"
#include "cWeapon.h"
class iState;
class cUIObject;
class cPlayer : public cDynamicObj
{
private:
	cWeapon*		m_pRightWeapon;
	cWeapon*		m_pLeftWeapon;

	bool			m_bIsBattle;
	float			m_fWaitTime;
	bool			m_firstMenu;
	bool			m_nowMenu;

	SYNTHESIZE(int, m_nKeyDir, KeyDir);
	SYNTHESIZE(float, m_fTempAngle, TempAngle);

	cUIObject*		m_pUIHp;


	//이후에 몸통 따로 구성
	/*cDynamicObj*	m_pArm;
	cDynamicObj*	m_pLeg;
	cDynamicObj*	m_pHead;*/

public:
	virtual void ChangeState(iState* pState, int nSkillIndex = -1) override;
	virtual void ChangeState(int pState, int nSkillIndex = -1) override;

	virtual void Attack() override;

	virtual float Damaged(ST_UNIT_INFO stInfo) override;
	virtual void Move(float fSpeed) override;

	bool IsMoveAble();
	void UpdateUI();


public:
	virtual void SetSound() override;
	void SetupBaseWeapon();
	void SetupState();
	void SetupStatus();
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat) override;
	void CheckControl();
	void CheckState();

	virtual void SetScale(D3DXVECTOR3 vScale) override;

	cBoundingBox GetRightWeaponBox() { return m_pRightWeapon->GetBox(); }
	cBoundingBox GetLeftWeaponBox() { return m_pLeftWeapon->GetBox(); }
	cBoundingSphere GetRightWeaponSphere() { return m_pRightWeapon->GetSphere(); }
	cBoundingSphere GetLeftWeaponSphere() { return m_pLeftWeapon->GetSphere(); }

	//임시
	void dlatl();


public:
	cPlayer(char* szFolder, char* szFilename);
	~cPlayer();

private:
	cPlayer();
};

