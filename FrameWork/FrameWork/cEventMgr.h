#pragma once

class cEvent;
class cEventMgr : public cSingleton<cEventMgr>
{
private:
//	map<string, cEvent*> m_mapEvent;
	vector<cEvent*> m_vecEvent;

public:
	void Play(/*string sKey*/);

public:
	void Update();

public:
	cEventMgr();
	~cEventMgr();
};

