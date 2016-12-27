#include "stdafx.h"
#include "cObjMgr.h"
#include "cDynamicObj.h"
#include "cStaticObj.h"
#include "cMap.h"


cObjMgr::cObjMgr()
{
}


cObjMgr::~cObjMgr()
{
}


void cObjMgr::AddMonster(string sKey, cDynamicObj* pMonster)
{
	auto iter = m_mapMonster.find(sKey);

	if (iter == m_mapMonster.end())
	{
		list<cDynamicObj*> ObjList;
		ObjList.push_back(pMonster);
		m_mapMonster.insert(make_pair(sKey, ObjList));
	}

	else
		iter->second.push_back(pMonster);
}


void cObjMgr::AddStuff(string sKey, cStaticObj* pStuff)
{
	auto iter = m_mapStuff.find(sKey);
	if (iter == m_mapStuff.end())
	{
		m_mapStuff.insert(make_pair(sKey, pStuff));
	}
	else
		iter->second;
}


void cObjMgr::AddCloneStuff(cStaticObj* pStuff)
{
	m_vecCloneStuff.push_back(pStuff);
}


void cObjMgr::Update()
{
	if (m_pMap)
		m_pMap->Update();
	/*for (auto iter = m_mapMonster.begin(); iter != m_mapMonster.end(); iter++)
	{
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
		{
			(*iter2)->Update();
		}
	}*/
}


void cObjMgr::Render()
{
	if (m_pMap)
		m_pMap->Render();
	if (m_pPlayer)
		m_pPlayer->UpdateAndRender();
	m_pPlayer->Bounding_Update();
	m_pPlayer->Bounding_Render();

	for (auto iter = m_mapMonster.begin(); iter != m_mapMonster.end(); iter++)
	{
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
		{
			(*iter2)->UpdateAndRender();
			(*iter2)->Bounding_Update();
	//		(*iter2)->Bounding_Render();
		}
	}

	for each(auto p in m_vecCloneStuff)
	{
		p->Render();
		p->Bounding_Update();
		p->Bounding_Render();
	}

	/*for (auto iter = m_mapStuff.begin(); iter != m_mapStuff.end(); iter++)
	{
		iter->second->Render();
	}*/
}


void cObjMgr::Release()
{
	SAFE_RELEASE(m_pPlayer);

	for (auto iter = m_mapMonster.begin(); iter != m_mapMonster.end(); iter++)
	{
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
		{
			SAFE_RELEASE((*iter2));
		}
		iter->second.clear();
	}

	for (auto iter = m_mapMonsterPool.begin(); iter != m_mapMonsterPool.end(); iter++)
	{
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
		{
			SAFE_RELEASE((*iter2));
		}
		iter->second.clear();
	}

	for (auto iter = m_mapStuff.begin(); iter != m_mapStuff.end(); iter++)
	{
		SAFE_RELEASE(iter->second);
	}

	for each(auto p in m_vecCloneStuff)
	{
		p->Release();
	}

	cSingleton::Release();
}


list<cDynamicObj*>* cObjMgr::GetMonsterList(string sKey)
{
	auto iter = m_mapMonster.find(sKey);

	if (iter == m_mapMonster.end())
		return NULL;
	return &m_mapMonster[sKey];
}


cStaticObj* cObjMgr::GetStuffList(string sKey)
{
	auto iter = m_mapStuff.find(sKey);

	if (iter == m_mapStuff.end())
		return NULL;
	return iter->second;
}


vector<cStaticObj*>* cObjMgr::GetAllCloneStuff()
{
	return &m_vecCloneStuff;
}


vector<cDynamicObj*> cObjMgr::GetALLMonsterList()
{
	vector<cDynamicObj*> pVecAllMonster;

	for (auto iter = m_mapMonster.begin(); iter != m_mapMonster.end(); iter++)
	{
		for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
		{
			pVecAllMonster.push_back(*iter2);
		}
	}

	return pVecAllMonster;
}


cDynamicObj* cObjMgr::GetMonsterPool(string sKey)
{
	auto iter = m_mapMonsterPool.find(sKey);

	if (iter == m_mapMonsterPool.end() || iter->second.size() > 0)
		return NULL;
	
	cDynamicObj* monster = iter->second.front();
	iter->second.pop_front();
	return monster;
}


void cObjMgr::AddInMonsterPoolFromMap(string sKey, cDynamicObj* pMonster)
{
	auto iter = m_mapMonster.find(sKey);

	if (iter == m_mapMonster.end())
		return;
	
	for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
	{
		if (*iter2 == pMonster)
		{
			m_mapMonsterPool[sKey].push_back(pMonster);
			iter->second.remove(pMonster);
			return;
		}
	}
}


void cObjMgr::SetMap(cMap* pMap)
{
	m_pMap = pMap;
	GETSINGLE(cSoundMgr)->Play(m_pMap->GetSoundKey(E_MAP_SOUND_BGM));
}