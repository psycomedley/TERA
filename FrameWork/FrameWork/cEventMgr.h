#pragma once

class cEvent;
class cEventMgr : public cSingleton<cEventMgr>
{
private:
//	map<string, cEvent*> m_mapEvent;
	vector<cEvent*> m_vecEvent;
	SYNTHESIZE(int, m_nEventIdx, EventIdx);

public:
	void Play(int nIdx);

public:
	void Update();
	void Release();

public:
	cEventMgr();
	~cEventMgr();
};

