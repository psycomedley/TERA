#pragma once
#include "cDynamicObj.h"
#include "cWeapon.h"

class iState;


class cPlayer : public cDynamicObj
{
private:


private:
	iState*			m_pState;

	cWeapon*		m_pRightWeapon;
	cWeapon*		m_pLeftWeapon;

	bool			m_bIsBattle;
	float			m_fWaitTime;

	//이후에 몸통 따로 구성
	/*cDynamicObj*	m_pArm;
	cDynamicObj*	m_pLeg;
	cDynamicObj*	m_pHead;*/

	//State
	iState*			m_aStates[E_STATE_END];
	//iState*		m_pStateIdle;
	//iState*		m_pStateRun;
	//iState*		m_pStateDefence;
	//iState*		m_pStateAttack;

public:
	virtual void ChangeState(iState* pState, int nSkillIndex = -1);
	virtual void ChangeState(int pState, int nSkillIndex = -1);

	bool IsMoveAble();

	void SetupBaseWeapon();
	void SetupState();
	void CheckControl();
	void CheckState();

public:
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat) override;


	//임시
	void dlatl();

public:
	cPlayer(char* szFolder, char* szFilename);
	~cPlayer();

private:
	cPlayer();
};

