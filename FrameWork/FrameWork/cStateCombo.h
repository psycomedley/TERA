#pragma once
#include "iState.h"

class cDynamicObj;
class cStateCombo : public iState
{
private:
	SYNTHESIZE(bool, m_bNextAttack, NextAttack);
	vector<cDynamicObj*> m_vecHitted;
	bool m_bHit;

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

	virtual void OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo) override;

public:
	cStateCombo();
	~cStateCombo();
};

