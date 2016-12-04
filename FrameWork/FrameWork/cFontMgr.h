#pragma once
class cFontMgr : public cSingleton<cFontMgr>
{
private:
	map<E_FONT_TYPE, LPD3DXFONT> m_mapFont;

public:
	LPD3DXFONT GetFont(E_FONT_TYPE eFontType);

public:
	cFontMgr();
	~cFontMgr();
};

