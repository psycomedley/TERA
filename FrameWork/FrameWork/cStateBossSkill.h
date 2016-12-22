#pragma once
#include "iState.h"

class cDynamicObj;
class cStateBossSkill : public iState
{
private:
	SYNTHESIZE(int, m_nSkillIndex, SkillIndex);
	SYNTHESIZE(int, m_nLoop, Loop);
	int m_nEffect;

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

	virtual void OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo) override;

	void AddGlobe(float fAngle);

public:
	cStateBossSkill();
	~cStateBossSkill();
};

