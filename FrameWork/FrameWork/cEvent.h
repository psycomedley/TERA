#pragma once
class cEvent
{
private:
	SYNTHESIZE(bool, m_bPlayed, Played);
	SYNTHESIZE(bool, m_bProcess, Process);
	SYNTHESIZE(float, m_fPassedTime, PassedTime);

public:
	virtual void Play();

public:
	virtual void Update();

public:
	cEvent();
	~cEvent();
};

