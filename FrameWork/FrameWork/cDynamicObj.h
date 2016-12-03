#pragma once
#include "cGameObject.h"
#include "cDynamicMesh.h"

//class cDynamicMesh;
class cDynamicObj : public cGameObject
{
private:

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
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat = NULL);

public:
	cDynamicObj(char* szFolder, char* szFilename);
	cDynamicObj();
	~cDynamicObj();
};

//D3DXTRACK_DESC position check