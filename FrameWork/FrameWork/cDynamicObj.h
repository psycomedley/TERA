#pragma once
#include "cGameObject.h"
#include "cDynamicMesh.h"

//class cDynamicMesh;
class iState;
class cDynamicObj : public cGameObject
{
protected:
	iState*			m_pState;
	iState*			m_aStates[E_STATE_END];
	string			m_eSoundKey[E_SOUND_END];
	SYNTHESIZE(cDynamicObj*, m_pTarget, Target);
	SYNTHESIZE(ST_UNIT_INFO, m_stInfo, Info);
	SYNTHESIZE(bool, m_bHit, Hit);
	SYNTHESIZE(float, m_fPassedVanishTime, PassedVanishTime);
	SYNTHESIZE(float, m_fPassedHitTime, PassedHitTime);

public:
	cAnimationController* GetAnimController() { return ((cDynamicMesh*)m_pMesh)->GetAnimController(); }

public:
	void AddAnimation(ST_ANIMATION_INFO stAnimationInfo);
	void SetAnimationIdx(int nIdx, bool bPlayOnce = false);
	void SetAnimationIdxBlend(int nIdx, bool bPlayOnce = false);

	void AnimationStart();
	bool AnimationNext();
	void AnimationRemove();

	ST_ANIMATION_INFO GetCurrentAnimInfo();
	double GetCurrentAnimPosition();
	string GetSoundKey(E_SOUND eSound) { return m_eSoundKey[eSound]; }

	virtual void ChangeState(iState* pState, int nSkillIndex = -1) PURE;
	virtual void ChangeState(int pState, int nSkillIndex = -1) PURE;

	virtual void Attack() {};
	virtual bool IsMoveAble() PURE;
	virtual bool IsTargetCollision();
	virtual bool IsTargetBoxCollision();
	virtual void LookTarget();

	virtual float Damaged(ST_UNIT_INFO stInfo, float fAddDamage = 0);

public:
	virtual cBoundingSphere GetSphere() { return cGameObject::GetSphere(); }
	virtual cBoundingBox GetBox() { return cGameObject::GetBox(); }

public:
	virtual void UpdateAndRender(D3DXMATRIXA16* pmat = NULL, bool bRender = true);

public:
	cDynamicObj(char* szFolder, char* szFilename);
	cDynamicObj();
	~cDynamicObj();

protected:
	iState* GetState(E_STATE eState) { return m_aStates[eState]; }
	virtual void SetSound() {};
};

//D3DXTRACK_DESC position check