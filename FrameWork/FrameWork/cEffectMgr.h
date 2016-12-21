#pragma once

class cEffect;
class cEffectMgr : public cSingleton<cEffectMgr>
{
private:
	map<string, list<cEffect*>>	m_mapEffect;
	list<cEffect*>				m_listEffect;
public:
	void AddEffect(string sKey, cEffect* pEffect);
	void AddList(string sKey, D3DXVECTOR3 vPosition, D3DXMATRIXA16& matRotation);
	void RemoveList(string sKey, cEffect* pEffect);
	list<cEffect*>* GetEffectInList(string sKey);
	list<cEffect*>* GetEffectInMap(string sKey);

public:
	void Update();
	void Render();
	void Release();

public:
	cEffectMgr();
	~cEffectMgr();
};

