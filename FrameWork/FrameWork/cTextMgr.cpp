#include "stdafx.h"
#include "cTextMgr.h"
#include "cText.h"
#include "cAlphaText.h"


cTextMgr::cTextMgr()
{
}


cTextMgr::~cTextMgr()
{
}


void cTextMgr::Update()
{
	float fPassedTime = GETSINGLE(cTimeMgr)->getElapsedTime();

	for (auto iter = m_listText.begin(); iter != m_listText.end();)
	{
		if ((*iter)->Update(fPassedTime))
			m_listText.erase(iter++);
		else
			iter++;
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
	for each (auto text in m_listText)
	{
		text->Render();
	}
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

	for each(auto p in m_mapText)
		SAFE_DELETE(p.second);

	cSingleton::Release();
}


void cTextMgr::AddText(cText* stText)
{
	m_mapText[stText->GetText()] = stText;
}


void cTextMgr::AddText(E_FONT_TYPE eType, string sText, float fShowTime,
	D3DXVECTOR2 vPosition, ST_SIZE stSize,
	D3DCOLOR dwColor /*= XWHITE*/,
	DWORD dwFormat /*= DT_VCENTER | DT_CENTER | DT_WORDBREAK*/)
{
	cText* pText = new cText;
	pText->Setup(eType, sText, fShowTime, vPosition, stSize, dwColor, dwFormat);
	m_mapText[sText] = pText;

	//ST_TEXT stText(eFontType, sText, fShowTime, _rect);
	//D3DXCreateSprite(g_pD3DDevice, &stText.pSprite);
	//m_listText.push_back(stText);
}


void cTextMgr::AddAlphaText(E_FONT_TYPE eType, string sText, float fShowTime,
	D3DXVECTOR2 vPosition, ST_SIZE stSize,
	D3DCOLOR dwColor /*= XWHITE*/, int nAlpha /*= 255*/, float fAlphaTime /*= 0.0f*/,
	DWORD dwFormat /*= DT_VCENTER | DT_CENTER | DT_WORDBREAK*/)
{
	cText* pText = new cAlphaText;
	((cAlphaText*)pText)->Setup(eType, sText, fShowTime, vPosition, stSize, dwColor, nAlpha, fAlphaTime, dwFormat);
	m_mapText[sText] = pText;
}


void cTextMgr::AddList(string key)
{
	if (m_mapText[key])
	{
		m_listText.push_back(m_mapText[key]);
		m_listText.back()->ResetTime();
	}
}


cText* cTextMgr::GetText(string key)
{
	if (m_mapText.find(key) == m_mapText.end())
		return NULL;
	return m_mapText[key];
}