#include "stdafx.h"
#include "cSkillElectricGlobe.h"
#include "iState.h"
#include "cStateIdle.h"
#include "cStateBossSkill.h"


cSkillElectricGlobe::cSkillElectricGlobe()
{
	SetupState();
	SetupStatus();
}


cSkillElectricGlobe::~cSkillElectricGlobe()
{
	for (int i = 0; i < E_STATE_END; i++)
		SAFE_DELETE(m_aStates[i]);
}


void cSkillElectricGlobe::SetupState()
{
	m_aStates[E_STATE_IDLE] = new cStateIdle;
	m_aStates[E_STATE_IDLE]->SetParent(this);
	m_aStates[E_STATE_SKILL] = new cStateBossSkill;
	m_aStates[E_STATE_SKILL]->SetParent(this);
}


void cSkillElectricGlobe::SetupStatus()
{

}