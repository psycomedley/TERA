#pragma once

class cUIObject;
class cUIMgr : public cSingleton<cUIMgr>
{
private:
	map<string, cUIObject*>	m_mapUI;
	list<cUIObject*>		m_listUI;

public:
	void AddUI(string sKey, cUIObject* pUI);
	void AddList(string sKey);
	void RemoveList(string sKey);

public:
	void Update();
	void Render();
	void Release();
	
public:
	cUIMgr();
	~cUIMgr();
};

