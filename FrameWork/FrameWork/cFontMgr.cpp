#include "stdafx.h"
#include "cFontMgr.h"


cFontMgr::cFontMgr()
{
}


cFontMgr::~cFontMgr()
{
}


LPD3DXFONT cFontMgr::GetFont(E_FONT_TYPE eFontType)
{
	if (m_mapFont.find(eFontType) == m_mapFont.end())
	{
		D3DXFONT_DESC fd;
		ZeroMemory(&fd, sizeof(D3DXFONT_DESC));

		switch (eFontType)
		{
		case E_FONT_BOSS:
			fd.Height = 25;
			fd.Width = 12;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "±√º≠√º");
//			AddFontResource("umberto.ttf");
//			strcpy_s(fd.FaceName, "umberto");
			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[eFontType]);
			break;
		case E_FONT_BOSS_STATUS:
			fd.Height = 15;
			fd.Width = 12;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "πŸ≈¡√º");
//			AddFontResource("umberto.ttf");
//			strcpy_s(fd.FaceName, "umberto");
			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[eFontType]);
			break;
		case E_FONT_DAMAGE:
			fd.Height = 40;
			fd.Width = 20;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			AddFontResource("BUBBLEBOY2.ttf");
			strcpy_s(fd.FaceName, "BUBBLEBOY2");
			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[eFontType]);
			break;
		case E_FONT_MONSTERDAMAGE:
			fd.Height = 30;
			fd.Width = 20;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "»ﬁ∏’∆Ì¡ˆ√º");
			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[eFontType]);
			break;
		case E_FONT_EVENT:
			fd.Height = 35;
			fd.Width = 20;
			fd.Weight = FW_NORMAL;
			fd.Italic = false;
			fd.CharSet = DEFAULT_CHARSET;
			fd.OutputPrecision = OUT_DEFAULT_PRECIS;
			fd.PitchAndFamily = FF_DONTCARE;
			strcpy_s(fd.FaceName, "πŸ≈¡√º");
			//			AddFontResource("umberto.ttf");
			//			strcpy_s(fd.FaceName, "umberto");
			D3DXCreateFontIndirect(g_pD3DDevice, &fd, &m_mapFont[eFontType]);
			break;
		}
	}
	return m_mapFont[eFontType];
}


void cFontMgr::Release()
{
	for each(auto it in m_mapFont)
		SAFE_RELEASE(it.second);

	cSingleton::Release();
}