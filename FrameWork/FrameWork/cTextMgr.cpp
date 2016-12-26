#include "stdafx.h"
#include "cTextMgr.h"
#include "cText.h"


cTextMgr::cTextMgr()
{
	D3DXCreateSprite(g_pD3DDevice, &m_pSprite);
}


cTextMgr::~cTextMgr()
{
}


void cTextMgr::Update()
{
	float fPassedTime = GETSINGLE(cTimeMgr)->getElapsedTime();

	for (auto iter = m_listText.begin(); iter != m_listText.end();)
	{
		(*iter)->Update(fPassedTime);
		if (!(*iter)->GetProcess())
		{
			cText* text = (*iter++);
			RemoveList(text->GetKey(), text);
		}
		else
			iter++;

		/*if ((*iter)->Update(fPassedTime))
			m_listText.erase(iter++);
		else
			iter++;*/
	}
	//auto iter = m_listText.begin();
	//while (iter != m_listText.end())
	//{
	//	iter->fPassedTime += fPassedTime;
	//	if (iter->fPassedTime >= iter->fShowTime)
	//		iter->bRender = false;
	//	else
	//		iter++;
	//}
}


void cTextMgr::Render()
{
	m_pSprite->Begin(D3DXSPRITE_ALPHABLEND);
	for each (auto text in m_listText)
		text->Render(m_pSprite);
	m_pSprite->End();
	/*for each (auto text in m_mapText)
	{
	LPD3DXFONT pFont = GETSINGLE(cFontMgr)->GetFont(text.second.eFontType);

	if (text.second.bRender)
	{
	pFont->DrawTextA(NULL,
	text.second.sText.c_str(),
	text.second.sText.size(),
	&text.second.rect,
	DT_CENTER | DT_VCENTER | DT_WORDBREAK,
	D3DCOLOR_XRGB(255, 255, 255));
	}
	}*/

}


void cTextMgr::Release()
{

	m_listText.clear();

	for each (auto iter in m_mapText)
		for each (auto text in iter.second)
			SAFE_DELETE(text);

	SAFE_RELEASE(m_pSprite);

//	for each(auto p in m_mapText)
//		SAFE_DELETE(p.second);

	cSingleton::Release();
}


void cTextMgr::AddText(cText* stText)
{
	m_mapText[stText->GetKey()].push_back(stText);
}


void AddText(E_FONT_TYPE eType, string sKey, string sText,
	D3DXVECTOR2 vPosition, ST_SIZE stSize,
	D3DCOLOR dwColor /*= XWHITE*/, int nOption /*= TEXT_NONE*/,
	DWORD dwFormat /*= DT_VCENTER | DT_CENTER | DT_WORDBREAK*/)
{
	cText* pText = new cText;
	pText->Setup(eType, sKey, sText, vPosition, stSize,
		dwColor, nOption, dwFormat);
}


void cTextMgr::AddList(string sKey)
{
	for (auto iter = m_mapText[sKey].begin(); iter != m_mapText[sKey].end(); iter++)
	{
		if (!(*iter)->GetProcess())
		{
			m_listText.push_back((*iter));
			(*iter)->Start();
			return;
		}
	}
	if (m_mapText[sKey].size() > 0)
	{
		cText* pText = new cText(m_mapText[sKey].front());
		pText->Start();
		m_mapText[sKey].push_back(pText);
		m_listText.push_back(pText);
	}

	/*if (m_mapText[sKey])
	{
		m_listText.push_back(m_mapText[sKey]);
		m_listText.back()->ResetTime();
	}*/
}


void cTextMgr::RemoveList(string sKey, cText* pText)
{
	for (auto iter = m_mapText[sKey].begin(); iter != m_mapText[sKey].end();)
	{
		if (*iter == pText)
		{
			m_listText.remove(*iter);
			return;
		}
		else
			iter++;
	}
}


cText* cTextMgr::GetText(string sKey)
{
	if (m_mapText.find(sKey) == m_mapText.end())
		return NULL;
	return m_mapText[sKey].front();
}