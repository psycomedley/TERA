#include "stdafx.h"
#include "iState.h"
#include "cDynamicObj.h"
#include "cText.h"


iState::iState()
	: m_fPassedTime(0.0f)
	, m_nSkillIndex(-1)
	, m_bSoundPlay(false)
{
}


iState::~iState()
{
}


void iState::PlaySound(E_SOUND eSound, bool bDouble /*= false*/)
{
	if (bDouble)
	{
		if (!m_bSoundPlay2)
		{
			string sKey = m_pParent->GetSoundKey(eSound);
			if (sKey != "")
				GETSINGLE(cSoundMgr)->Play(sKey);
			m_bSoundPlay2 = true;
		}
	}
	else
	{
		if (!m_bSoundPlay)
		{
			string sKey = m_pParent->GetSoundKey(eSound);
			if (sKey != "")
				GETSINGLE(cSoundMgr)->Play(sKey);
			m_bSoundPlay = true;
		}
		
	}
}