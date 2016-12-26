#include "stdafx.h"
#include "cEffectMgr.h"
#include "cEffect.h"
#include "cStaticMeshEffect.h"


cEffectMgr::cEffectMgr()
{
}


cEffectMgr::~cEffectMgr()
{
}


void cEffectMgr::Update()
{
	for (auto iter = m_listEffect.begin(); iter != m_listEffect.end();)
	{
		(*iter)->Update();
		if (!(*iter)->GetProcess())
		{
			cEffect* effect = (*iter++);
			RemoveList(effect->GetName(), effect);
		}
		else
			iter++;
	}
//	for each (auto effect in m_listEffect)
//		effect->Update();
}


void cEffectMgr::Render()
{
	/*for (auto iter = m_listEffect.begin(); iter != m_listEffect.end();)
	{
		(*iter)->Render();
		if (!(*iter)->GetProcess())
		{
			cEffect* effect = (*iter++);
			RemoveList(effect->GetName(), effect);
		}
		else
			iter++;
	}*/
	for each (auto effect in m_listEffect)
		effect->Render();

	for each(auto effect in m_vecStaticMeshEffect)
		effect->Render();

}


void cEffectMgr::Release()
{
	m_listEffect.clear();

	for each (auto iter in m_mapEffect)
		for each (auto effect in iter.second)
			effect->Release();

	for each(auto effect in m_vecStaticMeshEffect)
		effect->Release();


	cSingleton::Release();
}


void cEffectMgr::AddEffect(string sKey, cEffect* pEffect)
{
//	auto iter = m_mapEffect.find(sKey);
//	if (iter == m_mapEffect.end())
	m_mapEffect[sKey].push_back(pEffect);
}


cEffect* cEffectMgr::AddList(string sKey, D3DXVECTOR3 vPosition, D3DXMATRIXA16& matRotation)
{
	for (auto iter = m_mapEffect[sKey].begin(); iter != m_mapEffect[sKey].end(); iter++)
	{
		if (!(*iter)->GetProcess())
		{
			(*iter)->SetPosition(vPosition);
			(*iter)->SetMatRotation(matRotation);
//			if ((*iter)->GetMaxFrame() > 1)
//				(*iter)->SetCurrentFrame(GetInt((*iter)->GetMaxFrame()));
			m_listEffect.push_back(*iter);
			(*iter)->Start();
			return (*iter);
		}
	}
	if (m_mapEffect[sKey].size() > 0)
	{
		cEffect* pEffect = new cEffect(m_mapEffect[sKey].front());
		pEffect->SetPosition(vPosition);
		pEffect->SetMatRotation(matRotation);
//		if (pEffect->GetMaxFrame() > 1)
//			pEffect->SetCurrentFrame(GetInt(pEffect->GetMaxFrame()));
		pEffect->Start();
		m_mapEffect[sKey].push_back(pEffect);
		m_listEffect.push_back(pEffect);
		return pEffect;
	}
}


void cEffectMgr::RemoveList(string sKey, cEffect* pEffect)
{
	for (auto iter = m_mapEffect[sKey].begin(); iter != m_mapEffect[sKey].end();)
	{
		if (*iter == pEffect)
		{
			m_listEffect.remove(*iter);
			return;
		}
		else
			iter++;
	}
	//for (auto iter = m_mapEffect[sKey].begin(); iter != m_mapEffect[sKey].end();)
	//{
	//	if (!(*iter)->GetProcess())
	//		m_listEffect.remove(*iter);
	//	else
	//		iter++;
	//}
}


list<cEffect*>* cEffectMgr::GetEffectInList(string sKey)
{
//	for (auto iter = m_listEffect.begin(); iter != m_listEffect.end(); iter++)
//		if (*iter == m_mapEffect[sKey])
//			return *iter;
	return &m_listEffect;
}


list<cEffect*>* cEffectMgr::GetEffectInMap(string sKey)
{
	return &m_mapEffect[sKey];
}

void cEffectMgr::AddStaticMeshEffect(char * szFolder, char * szFilename, D3DXVECTOR3 s, D3DXVECTOR3 t, float Angle)
{
	cStaticMeshEffect* m_pStaticMeshEffect = new cStaticMeshEffect(szFolder, szFilename);
	m_pStaticMeshEffect->Setup(s, t, Angle);
	m_vecStaticMeshEffect.push_back(m_pStaticMeshEffect);
}

void cEffectMgr::RemoveStaticMeshEffect()
{
	m_vecStaticMeshEffect.clear();
}

void cEffectMgr::StaticMeshEffectRender()
{
	for each(auto effect in m_vecStaticMeshEffect)
		effect->Render();
}