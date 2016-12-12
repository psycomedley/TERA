#include "stdafx.h"
#include "cUIMgr.h"
#include "cUIObject.h"


cUIMgr::cUIMgr()
{
}


cUIMgr::~cUIMgr()
{
}


void cUIMgr::Update()
{
	for each (auto ui in m_listUI)
		ui->Update(NULL);
}


void cUIMgr::Render()
{
	/*LPD3DXEFFECT effect;
	effect = GETSINGLE(cShaderMgr)->GetEffect(E_EFFECT_UI);
	D3DXMATRIXA16 matWorld, matView, matProj;
	g_pD3DDevice->GetTransform(D3DTS_WORLD, &matWorld);
	
	effect->SetMatrix("gWorldMatrix", &matWorld);

	UINT uiPasses, uiPass;
	effect->Begin(&uiPasses, 0);
	for (uiPass = 0; uiPass < uiPasses; ++uiPass)
	{
		effect->BeginPass(uiPass);*/
		for each (auto ui in m_listUI)
			ui->Render();
	//	effect->EndPass();
	//}
	//effect->End();
}


void cUIMgr::Release()
{
	for each (auto ui in m_mapUI)
		ui.second->Release();

	cSingleton::Release();
}


void cUIMgr::AddUI(string sKey, cUIObject* pUI)
{
	auto iter = m_mapUI.find(sKey);
	if (iter == m_mapUI.end())
		m_mapUI[sKey] = pUI;
}


void cUIMgr::AddList(string sKey)
{
	if (m_mapUI[sKey])
		m_listUI.push_back(m_mapUI[sKey]);
}


void cUIMgr::RemoveList(string sKey)
{
	for (auto iter = m_listUI.begin(); iter != m_listUI.end(); iter++)
	{
		if (*iter == m_mapUI[sKey])
		{
			m_listUI.remove(*iter);
			return;
		}
	}
}


cUIObject* cUIMgr::GetUIInList(string sKey)
{
	for (auto iter = m_listUI.begin(); iter != m_listUI.end(); iter++)
		if (*iter == m_mapUI[sKey])
			return *iter;
}


cUIObject* cUIMgr::GetUIInMap(string sKey)
{
	return m_mapUI[sKey];
}