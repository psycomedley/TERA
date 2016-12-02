#pragma once
#include "cDynamicMesh.h"
#include "cDynamicObj.h"
#include "cWeapon.h"

class iState;


class cPlayer : public cDynamicObj
{
private:


private:
	iState*		m_pState;

	cWeapon*	m_pRightWeapon;
	cWeapon*	m_pLeftWeapon;

	//이후에 몸통 따로 구성

	//State
	iState*		m_pStates[E_STATE_END];
	//iState*		m_pStateIdle;
	//iState*		m_pStateRun;
	//iState*		m_pStateDefence;
	//iState*		m_pStateAttack;

public:
	virtual void ChangeState(iState* pState);
	virtual void ChangeState(int pState);

	bool IsMoveAble();

	void SetupBaseWeapon();
	void SetupState();
	void CheckControl();
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat) override;


	//임시
	void dlatl();

public:
	cPlayer(char* szFolder, char* szFilename);
	~cPlayer();

private:
	cPlayer();
};

