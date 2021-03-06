#pragma once
#include "iState.h"

class cDynamicObj;
//class cStaticMeshEffect;
class cStateDefence : public iState
{
private:
	cStaticMeshEffect* m_pEffect;
	bool nowEffect;

public:
	virtual void Start() override;
	virtual void Update() override;
	virtual void End() override;

	virtual void OnAnimationFinish(cAnimationController* pController, ST_ANIMATION_INFO animInfo) override;

public:
	cStateDefence();
	~cStateDefence();
};

