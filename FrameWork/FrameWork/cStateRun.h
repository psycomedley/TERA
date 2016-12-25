#pragma once
#include "iState.h"

class cDynamicObj;
class cStateRun : public iState
{
private:
	vector<float> m_vTiming;

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

	virtual void OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo) override;

	vector<float>* GetVecTiming() { return &m_vTiming; }

public:
	cStateRun();
	~cStateRun();
};

