#include "stdafx.h"
#include "cEffectThunderGlobe.h"


cEffectThunderGlobe::cEffectThunderGlobe()
{
}


cEffectThunderGlobe::cEffectThunderGlobe(cEffectThunderGlobe* pEffect)
{
	cEffect::cEffect(pEffect);
	pEffect->SetCurrentFrame(GetInt(pEffect->GetMaxFrame()));
}


cEffectThunderGlobe::~cEffectThunderGlobe()
{
}


void cEffectThunderGlobe::Update()
{
	if (m_bProcess)
	{
		m_fPassedTime += GETSINGLE(cTimeMgr)->getElapsedTime();

		if (m_bEnd)
		{
			m_fRemovePassedTime += GETSINGLE(cTimeMgr)->getElapsedTime();
			if (m_fRemovePassedTime >= m_fRemoveTime)
			{
				Stop();
				return;
			}
		}

		if (m_nOption & EFFECT_CUTTEDFRAME)
		{
			if (m_fPassedTime >= m_fNextTime)
			{
				if (++m_nCurrentFrame >= m_nMaxFrame)
				{
					if (--m_nLeftLoopTimes <= 0)
						SetTech(E_TECH_ORCA1_Remove);
//					if (!m_bLoop)
//						Stop();
					else
						m_nCurrentFrame -= m_nMaxFrame;
				}
				UpdateUV();
			}

			m_pEffect->SetInt("g_nOffsetX", m_nOffsetX);
			m_pEffect->SetInt("g_nOffsetY", m_nOffsetY);
		}
		else if (!m_bLoop)
		{
			if (m_fPassedTime >= m_fRemoveTime)
			{
				Stop();
				g_pD3DDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
				return;
			}
		}
	}
}


void cEffectThunderGlobe::Start()
{
	cEffect::Start();
	SetCurrentFrame(GetInt(m_nMaxFrame));
}