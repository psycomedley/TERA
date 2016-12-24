#pragma once
#include "iState.h"

class cDynamicObj;
class cStateMonsterSkill2 : public iState
{
public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

	virtual void OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo) override;

public:
	cStateMonsterSkill2();
	~cStateMonsterSkill2();
};

