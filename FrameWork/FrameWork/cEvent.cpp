#include "stdafx.h"
#include "cEvent.h"
#include "cCamera.h"
#include "cDynamicObj.h"
#include "cText.h"
#include "cMap.h"


cEvent::cEvent()
	: m_bPlayed(false)
	, m_bProcess(false)
	, m_fPassedTime(0.0f)
{
}


cEvent::~cEvent()
{
}


void cEvent::Update()
{
	if (m_bProcess)
	{
		m_fPassedTime += GETSINGLE(cTimeMgr)->getElapsedTime();
		GETSINGLE(cCameraMgr)->GetCurrentCamera()->SetCamRotY(
			GETSINGLE(cCameraMgr)->GetCurrentCamera()->GetCamRotY() - 0.001f);

		if (m_fPassedTime >= 9.0f)
		{
			m_bProcess = false;
			GETSINGLE(cCameraMgr)->SetCurrentCamera("MainCamera");

			GETSINGLE(cUIMgr)->AddList("CrossHair");
			GETSINGLE(cUIMgr)->AddList("Player");
		}
	}
}


void cEvent::Play()
{
	if (!m_bPlayed)
	{
		m_bProcess = true;
		GETSINGLE(cCameraMgr)->SetCurrentCamera("EventCamera");
		D3DXVECTOR3 pos = GETSINGLE(cObjMgr)->GetMonsterList("Orca")->front()->GetSphere().GetCenter();
		GETSINGLE(cCameraMgr)->GetCurrentCamera()->SetLookAt(pos);



		cText* pText = new cText;
		pText->Setup(E_FONT_EVENT, "Event1", "산책나온", D3DXVECTOR2(GetWindowWidth() / 2 - 70, 600), ST_SIZE(200, 50), XWHITE,
			TEXT_ALPHA | TEXT_MOVE | TEXT_SHOWTIME | TEXT_MOVEAFTERTIME | TEXT_SHOWAFTERTIME | TEXT_APPEARWITHALPHA);
		pText->SetShowTime(3.0f);
		pText->SetAlphaTime(1.0f);
		pText->SetMoveSpeed(1.5f);
		pText->SetDirection(DIRECTION_LEFT);
		pText->SetMoveTime(2.5f);
		pText->SetShowAfterTime(1.5f);
		pText->SetAppearTime(2.0f);
		GETSINGLE(cTextMgr)->AddText(pText);

		pText = new cText;
		pText->Setup(E_FONT_EVENT, "Event2", " 오르카", D3DXVECTOR2(GetWindowWidth() / 2 + 70, 600), ST_SIZE(200, 50), XWHITE,
			TEXT_ALPHA | TEXT_MOVE | TEXT_SHOWTIME | TEXT_MOVEAFTERTIME | TEXT_SHOWAFTERTIME | TEXT_APPEARWITHALPHA);
		pText->SetShowTime(3.0f);
		pText->SetAlphaTime(1.0f);
		pText->SetMoveSpeed(1.5f);
		pText->SetDirection(DIRECTION_RIGHT);
		pText->SetMoveTime(2.5f);
		pText->SetShowAfterTime(1.5f);
		pText->SetAppearTime(2.0f);
		GETSINGLE(cTextMgr)->AddText(pText);

		GETSINGLE(cTextMgr)->AddList("Event1");
		GETSINGLE(cTextMgr)->AddList("Event2");

		m_bPlayed = true;

		GETSINGLE(cUIMgr)->RemoveList("CrossHair");
		GETSINGLE(cUIMgr)->RemoveList("Player");
		GETSINGLE(cSoundMgr)->Stop(GETSINGLE(cObjMgr)->GetMap()->GetSoundKey(E_MAP_SOUND_BGM));
		GETSINGLE(cSoundMgr)->Play(GETSINGLE(cObjMgr)->GetMap()->GetSoundKey(E_MAP_SOUND_BOSS_BGM));
	}
}