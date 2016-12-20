#pragma once

class cStaticObj;
class cDynamicObj;
class cObjMgr : public cSingleton<cObjMgr>
{
private:
	cDynamicObj*							m_pPlayer;
//	SYNTHESIZE(cDynamicObj*, m_pPlayer, Player);
	map<string, vector<cDynamicObj*>>		m_mapMonster;
	map<string, cStaticObj*>				m_mapStuff;
	vector<cStaticObj*>						m_vecCloneStuff;

public:
	void AddMonster(string sKey, cDynamicObj* pMonster);
	void AddStuff(string sKey, cStaticObj* pStuff);
	void AddCloneStuff(cStaticObj* pStuff);

	
	map<string, vector<cDynamicObj*>>* GetMonsterMap() { return &m_mapMonster; }
	map<string, cStaticObj*>* GetStuffMap() { return &m_mapStuff; }
	vector<cDynamicObj*>* GetMonsterList(string sKey);
	cStaticObj* GetStuffList(string sKey);

	vector<cDynamicObj*> GetALLMonsterList();

public:
	cDynamicObj* GetPlayer() { return m_pPlayer; }
	void SetPlayer(cDynamicObj* pPlayer) { m_pPlayer = pPlayer; }

public:
	void Update();
	void Render();
	void Release();

public:
	cObjMgr();
	~cObjMgr();
};

