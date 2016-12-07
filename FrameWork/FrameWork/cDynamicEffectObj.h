#pragma once
#include "cGameObject.h"
#include "cDynamicMesh.h"
class cDynamicEffectObj : public cGameObject
{
protected:
	SYNTHESIZE(cDynamicObj*, m_pTarget, Target);
public:
		cAnimationController* GetAnimController() { return ((cDynamicMesh*)m_pMesh)->GetAnimController(); }
public:
	void AddAnimation(ST_ANIMATION_INFO stAnimationInfo);
	void SetAnimationIdx(int nIdx, bool bPlayOnce = false);
	void SetAnimationIdxBlend(int nIdx, bool bPlayOnce = false);

	void AnimationStart();
	void AnimationNext();
	void AnimationRemove();

	ST_ANIMATION_INFO GetCurrentAnimInfo();
	double GetCurrentAnimPosition();

public:
	virtual cBoundingSphere GetSphere() { return cGameObject::GetSphere(); }
	virtual cBoundingBox GetBox() { return cGameObject::GetBox(); }

public:
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);

public:
	cDynamicEffectObj(char* szFolder, char* szFilename);
	cDynamicEffectObj();
	~cDynamicEffectObj();
};

