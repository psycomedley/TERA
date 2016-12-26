#pragma once
#include "cEvent.h"

class cEvent2 : public cEvent
{
private:
//	SYNTHESIZE(bool, m_bPlayed, Played);
//	SYNTHESIZE(bool, m_bProcess, Process);
//	SYNTHESIZE(float, m_fPassedTime, PassedTime);

public:
	virtual void Play() override;

public:
	virtual void Update() override;

public:
	cEvent2();
	~cEvent2();
};

