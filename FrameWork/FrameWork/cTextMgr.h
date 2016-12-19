#pragma once

class cText;
class cTextMgr : public cSingleton<cTextMgr>
{
private:
	map<string, list<cText*>>	m_mapText;
	list<cText*>				m_listText;
//	map<E_FONT_TYPE, ST_TEXT> m_mapFont;

public:
	void AddText(cText* stText);
	void AddText(E_FONT_TYPE eType, string sKey, string sText,
		D3DXVECTOR2 vPosition, ST_SIZE stSize,
		D3DCOLOR dwColor = XWHITE, int nOption = TEXT_NONE,
		DWORD dwFormat = DT_VCENTER | DT_CENTER | DT_WORDBREAK);

	/*void AddText(E_FONT_TYPE eType, string sKey, string sText, float fShowTime,
		D3DXVECTOR2 vPosition, ST_SIZE stSize,
		D3DCOLOR dwColor = XWHITE,
		int nOption = TEXT_NONE,
		DWORD dwFormat = DT_VCENTER | DT_CENTER | DT_WORDBREAK);*/
	/*void AddAlphaText(E_FONT_TYPE eType, string sKey, string sText, float fShowTime,
		D3DXVECTOR2 vPosition, ST_SIZE stSize,
		D3DCOLOR dwColor = XWHITE,
		int nOption = TEXT_NONE, int nAlpha = 255, float fAlphaTime = 0.0f,
		DWORD dwFormat = DT_VCENTER | DT_CENTER | DT_WORDBREAK);*/
	void AddList(string sKey);
	void RemoveList(string sKey, cText* pText);
//	cText* GetText(string key);

public:
	void Update();
	void Render();
	void Release();

public:
	cTextMgr();
	~cTextMgr();
};

