#include "stdafx.h"
#include "cTextMgr.h"


cTextMgr::cTextMgr()
{
}


cTextMgr::~cTextMgr()
{
}


void cTextMgr::Update()
{
	float fPassedTime = GETSINGLE(cTimeMgr)->getElapsedTime();

	for each (auto text in m_mapText)
	{
		text.second.fPassedTime += fPassedTime;
		if (text.second.fPassedTime >= text.second.fShowTime)
			text.second.bRender = false;
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
	for each (auto text in m_mapText)
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
	}

	for each (auto text in m_listText)
	{
		LPD3DXFONT pFont = GETSINGLE(cFontMgr)->GetFont(text.eFontType);
	//	pFont->DrawText(NULL, text.sText.c_str(), text.sText.size(), &text.rect, DT_NOCLIP, D3DCOLOR_XRGB(255, 255, 255));
		pFont->DrawTextA(NULL,
			text.sText.c_str(),
			text.sText.size(),
			&text.rect,
			DT_CENTER | DT_VCENTER | DT_WORDBREAK,
			D3DCOLOR_XRGB(255, 255, 255));
	}
}


void cTextMgr::Release()
{
	cSingleton::Release();
}


void cTextMgr::AddText(ST_TEXT stText)
{
	m_listText.push_back(stText);
}


void cTextMgr::AddText(E_FONT_TYPE eFontType, string sText, float fShowTime, RECT _rect)
{
	ST_TEXT stText(eFontType, sText, fShowTime, _rect);
	D3DXCreateSprite(g_pD3DDevice, &stText.pSprite);
	m_listText.push_back(stText);
}