#pragma once
#include "iAnimationDelegate.h"
#include "cAnimationController.h"

class cDynamicObj;
class iState : public iAnimationDelegate
{
protected:
	cDynamicObj* m_pParent;

	vector<cDynamicObj*> m_vecHitted;
	bool m_bHit;
	float m_fDamageTime;

public:
	void SetParent(cDynamicObj* pParent) { m_pParent = pParent; }

public:
	virtual void Start() PURE;
	virtual void Update() PURE;
//	virtual void Render() PURE;
	virtual void End() PURE;
	void AddDamage(bool bDoubleHit);
	void AddEnemyDamage(cBoundingSphere sphere, bool bDoubleHit = false, float fDamageTime = 0.0f);

public:
	iState();
	~iState();
};

