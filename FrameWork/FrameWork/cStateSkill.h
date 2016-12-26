#pragma once
#include "iState.h"

class cDynamicObj;
class cVerticalCircleEffect;
class cCircleEffect;
class cStateSkill : public iState
{
private:
	bool	m_bNextAttack;
	int		m_nCount;
//	SYNTHESIZE(int, m_nSkillIndex, SkillIndex);

private:
	cVerticalCircleEffect* m_pEffect1;
	bool StartEffect1;
	cCircleEffect* m_pSkill3Effect;
	bool StartSkill3;

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

	virtual void OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo) override;

public:
	cStateSkill();
	~cStateSkill();
};

