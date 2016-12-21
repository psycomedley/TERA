#pragma once
#include "cMonster.h"

class cSkillElectricGlobe : public cMonster
{
public:
	cSkillElectricGlobe();
	~cSkillElectricGlobe();

protected:
	virtual void SetupState() PURE;
	virtual void SetupStatus() PURE;
	virtual void Update() override;
};

