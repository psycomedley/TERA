#pragma once

class cStaticObj;
class cDynamicObj;
class cMap;
class cObjMgr : public cSingleton<cObjMgr>
{
private:
	cDynamicObj*							m_pPlayer;
	cMap*									m_pMap;
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
	list<cDynamicObj*>* GetMonsterList(string sKey);

	map<string, cStaticObj*>* GetStuffMap() { return &m_mapStuff; }
	cStaticObj* GetStuffList(string sKey);
	vector<cStaticObj*>* GetAllCloneStuff();

	vector<cDynamicObj*> GetALLMonsterList();

	cDynamicObj* GetMonsterPool(string sKey);
	void AddInMonsterPoolFromMap(string sKey, cDynamicObj* pMonster);

public:
	cDynamicObj* GetPlayer() { return m_pPlayer; }
	void SetPlayer(cDynamicObj* pPlayer) { m_pPlayer = pPlayer; }

	cMap* GetMap() { return m_pMap; }
	void SetMap(cMap* pMap);

public:
	void Update();
	void Render();
	void Release();

public:
	cObjMgr();
	~cObjMgr();
};

