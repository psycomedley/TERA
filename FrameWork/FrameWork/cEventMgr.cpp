#include "stdafx.h"
#include "cEventMgr.h"
#include "cEvent.h"
#include "cEvent2.h"


cEventMgr::cEventMgr()
	: m_nEventIdx(0)
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


void cEventMgr::Play(int nIdx)
{
	m_nEventIdx = nIdx;
	m_vecEvent[m_nEventIdx]->Play();
}


void cEventMgr::Update()
{
	m_vecEvent[m_nEventIdx]->Update();
}
void cEventMgr::Release()
{
	cSingleton::Release();
}