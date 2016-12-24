#pragma once
#include "cMonster.h"

class cEffect;
class cSkillElectricGlobe : public cMonster
{
private:
	SYNTHESIZE(bool, m_bActive, Active);
	SYNTHESIZE(cEffect*, m_pEffect, Effect);
	float m_fPassedTime;

public:
	virtual void ChangeState(iState* pState, int nSkillIndex = -1) override;
	virtual void ChangeState(int pState, int nSkillIndex = -1) override;
	virtual bool IsMoveAble() override;
	void Setup();
	void UpdateAndRender(D3DXMATRIXA16* pmat);

public:
	cSkillElectricGlobe();
	~cSkillElectricGlobe();
	
protected:
	virtual void SetupState() override;
	virtual void SetupStatus() override;
	virtual void Update() override;
};

