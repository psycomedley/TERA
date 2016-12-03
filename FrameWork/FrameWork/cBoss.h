#pragma once
#include "cMonster.h"

class iState;
class cBoss : public cMonster
{
private:
	iState*			m_pState;

	iState*			m_aStates[E_STATE_END];

	ST_SKILL_INFO	m_skillLongMove;
	ST_SKILL_INFO	m_skillHeavyAtk;
	ST_SKILL_INFO	m_skillAttack;

public:
	virtual void ChangeState(iState* pState, int nSkillIndex = -1);
	virtual void ChangeState(int pState, int nSkillIndex = -1);

	bool IsMoveAble();
	bool IsTargetCollision();

public:
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat) override;

public:
	cBoss(char* szFolder, char* szFilename);
	~cBoss();

private:
	cBoss();
	virtual void SetupState() override;
	virtual void SetupStatus() override;
	virtual void Update() override;
};

