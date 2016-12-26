#include "stdafx.h"
#include "cEventMgr.h"
#include "cEvent.h"


cEventMgr::cEventMgr()
{
	cEvent* pEvent = new cEvent;
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
	m_vecEvent[0]->Play();
}


void cEventMgr::Update()
{
	m_vecEvent[0]->Update();
}
void cEventMgr::Release()
{
	cSingleton::Release();
}