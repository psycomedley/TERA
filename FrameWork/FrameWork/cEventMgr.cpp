#include "stdafx.h"
#include "cEventMgr.h"
#include "cEvent.h"
#include "cEvent2.h"


cEventMgr::cEventMgr()
{
	cEvent* pEvent = new cEvent;
	m_vecEvent.push_back(pEvent);
	pEvent = new cEvent2;
	m_vecEvent.push_back(pEvent);
}


cEventMgr::~cEventMgr()
{
	/*for each(auto p in m_vecEvent)
	{
		SAFE_DELETE(p);
	}*/
}


void cEventMgr::Play(/*string sKey*/)
{
	m_vecEvent[1]->Play();
}


void cEventMgr::Update()
{
	m_vecEvent[1]->Update();
}
void cEventMgr::Release()
{
	cSingleton::Release();
}