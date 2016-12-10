#pragma once
class cTextMgr : public cSingleton<cTextMgr>
{
private:
	list<ST_TEXT>			m_listText;
	map<string, ST_TEXT>	m_mapText;
//	map<E_FONT_TYPE, ST_TEXT> m_mapFont;

public:
	void AddText(ST_TEXT stText);
	void AddText(E_FONT_TYPE eFontType, string sText, float fShowTime, RECT _rect);
	void AddList();

public:
	void Update();
	void Render();
	void Release();

public:
	cTextMgr();
	~cTextMgr();
};

