#pragma once
#include "iState.h"

class cDynamicObj;
class cCircleEffect;
class cStateCombo : public iState
{
private:
	cCircleEffect* m_pCombo1Effect;
	cCircleEffect* m_pCombo2Effect;
	cCircleEffect* m_pCombo3Effect;
	cCircleEffect* m_pCombo4Effect;
	bool StartCombo1;
	bool StartCombo2;
	bool StartCombo3;
	bool StartCombo4;


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

public:
	
};

