#pragma once
class cEvent
{
private:
	SYNTHESIZE(bool, m_bPlayed, Played);
	SYNTHESIZE(bool, m_bProcess, Process);
	SYNTHESIZE(float, m_fPassedTime, PassedTime);

public:
	void Play();

public:
	void Update();

public:
	cEvent();
	~cEvent();
};

