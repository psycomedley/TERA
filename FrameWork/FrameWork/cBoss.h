#pragma once
#include "cMonster.h"

class iState;
class cBoss : public cMonster
{
private:
	iState*			m_pState;

	iState*			m_aStates[E_STATE_END];

public:
	virtual void ChangeState(iState* pState, int nSkillIndex = -1);
	virtual void ChangeState(int pState, int nSkillIndex = -1);

	bool IsMoveAble();



public:
	void SetupState();
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat) override;
	void CheckState();

public:
	cBoss(char* szFolder, char* szFilename);
	~cBoss();

private:
	cBoss();
};

