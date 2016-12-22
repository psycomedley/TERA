#pragma once
#include "cMonster.h"

class iState;
class cOrca : public cMonster
{
private:
	ST_SKILL_INFO	m_skillLongMove;
	ST_SKILL_INFO	m_skillHeavyAtk;
	ST_SKILL_INFO	m_skillAttack;
	ST_SKILL_INFO	m_skillHeavyAtk2;
	ST_SKILL_INFO	m_skillBackAtk;

	int				m_nNumClone;
	SYNTHESIZE(int, m_nLoop, Loop);
	float			m_fEventCameraRange;

public:
	virtual void ChangeState(iState* pState, int nSkillIndex = -1) override;
	virtual void ChangeState(int pState, int nSkillIndex = -1) override;

public:
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat) override;

	virtual bool IsMoveAble() override;
	bool IsBehind();

public:
	cOrca(char* szFolder, char* szFilename);
	~cOrca();

private:
	cOrca();
	virtual void SetupState() override;
	virtual void SetupStatus() override;
	virtual void Update() override;

	void LongMove();
};

