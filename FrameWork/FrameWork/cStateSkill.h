#pragma once
#include "iState.h"

class cDynamicObj;
class cStateSkill : public iState
{
private:
	bool	m_bNextAttack;
	int		m_nCount;
//	SYNTHESIZE(int, m_nSkillIndex, SkillIndex);

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

	virtual void OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo) override;

public:
	cStateSkill();
	~cStateSkill();
};

