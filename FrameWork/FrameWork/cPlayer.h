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

	SYNTHESIZE(ST_UNIT_INFO, m_stInfo, Info);
	SYNTHESIZE(int, m_nKeyDir, KeyDir);
	SYNTHESIZE(float, m_fTempAngle, TempAngle);

	cUIObject*		m_pUIHp;

	//���Ŀ� ���� ���� ����
	/*cDynamicObj*	m_pArm;
	cDynamicObj*	m_pLeg;
	cDynamicObj*	m_pHead;*/

public:
	virtual void ChangeState(iState* pState, int nSkillIndex = -1) override;
	virtual void ChangeState(int pState, int nSkillIndex = -1) override;

	virtual void Attack() override;

	bool IsMoveAble();
	void UpdateUI();

public:
	void SetupBaseWeapon();
	void SetupState();
	void SetupStatus();
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat) override;
	void CheckControl();
	void CheckState();

	virtual void SetScale(D3DXVECTOR3 vScale) override;

	//�ӽ�
	void dlatl();

public:
	cPlayer(char* szFolder, char* szFilename);
	~cPlayer();

private:
	cPlayer();
};

