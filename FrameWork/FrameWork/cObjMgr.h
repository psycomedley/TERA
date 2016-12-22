#pragma once

class cStaticObj;
class cDynamicObj;
class cObjMgr : public cSingleton<cObjMgr>
{
private:
	cDynamicObj*							m_pPlayer;
//	SYNTHESIZE(cDynamicObj*, m_pPlayer, Player);
	map<string, list<cDynamicObj*>>			m_mapMonster;
	map<string, cStaticObj*>				m_mapStuff;
	vector<cStaticObj*>						m_vecCloneStuff;

	map<string, list<cDynamicObj*>>			m_mapMonsterPool;

public:
	void AddMonster(string sKey, cDynamicObj* pMonster);
	void AddStuff(string sKey, cStaticObj* pStuff);
	void AddCloneStuff(cStaticObj* pStuff);

	
	map<string, list<cDynamicObj*>>* GetMonsterMap() { return &m_mapMonster; }
	map<string, cStaticObj*>* GetStuffMap() { return &m_mapStuff; }
	list<cDynamicObj*>* GetMonsterList(string sKey);
	cStaticObj* GetStuffList(string sKey);

	vector<cDynamicObj*> GetALLMonsterList();

	cDynamicObj* GetMonsterPool(string sKey);
	void AddInMonsterPoolFromMap(string sKey, cDynamicObj* pMonster);

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

