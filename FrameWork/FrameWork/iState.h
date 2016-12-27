#pragma once
#include "iAnimationDelegate.h"
#include "cAnimationController.h"

class cDynamicObj;
class iState : public iAnimationDelegate
{
protected:
	cDynamicObj*	m_pParent;
	bool			m_bSoundPlay;
	bool			m_bSoundPlay2;
	SYNTHESIZE(float, m_fPassedTime, PassedTime);
	SYNTHESIZE(int, m_nSkillIndex, SkillIndex);

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

protected:
	void PlaySound(E_SOUND eSound, float fVolume = 1.0f, bool bDouble = false);

public:
	iState();
	~iState();
};

