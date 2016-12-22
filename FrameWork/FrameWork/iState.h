#pragma once
#include "iAnimationDelegate.h"
#include "cAnimationController.h"

class cDynamicObj;
class iState : public iAnimationDelegate
{
protected:
	SYNTHESIZE(float, m_fPassedTime, PassedTime);
	SYNTHESIZE(int, m_nSkillIndex, SkillIndex);
	cDynamicObj* m_pParent;

//	vector<cDynamicObj*> m_vecHitted;
//	bool m_bHit;
//	float m_fDamageTime;

public:
	void SetParent(cDynamicObj* pParent) { m_pParent = pParent; }

public:
	virtual void Start() PURE;
	virtual void Update() PURE;
//	virtual void Render() PURE;
	virtual void End() PURE;

public:
	iState();
	~iState();
};

