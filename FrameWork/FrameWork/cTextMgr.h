#pragma once

class cText;
class cTextMgr : public cSingleton<cTextMgr>
{
private:
	map<string, cText*>	m_mapText;
	list<cText*>		m_listText;
//	map<E_FONT_TYPE, ST_TEXT> m_mapFont;

public:
	void AddText(cText* stText);
	void AddText(E_FONT_TYPE eType, string sText, float fShowTime,
		D3DXVECTOR2 vPosition, ST_SIZE stSize,
		D3DCOLOR dwColor = XWHITE,
		DWORD dwFormat = DT_VCENTER | DT_CENTER | DT_WORDBREAK);
	void AddList(string key);
	cText* GetText(string key);

public:
	void Update();
	void Render();
	void Release();

public:
	cTextMgr();
	~cTextMgr();
};

