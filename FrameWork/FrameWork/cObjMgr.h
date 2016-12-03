#pragma once

class cStaticObj;
class cDynamicObj;
class cObjMgr : public cSingleton<cObjMgr>
{
private:
	cDynamicObj* m_pPlayer;
//	SYNTHESIZE(cDynamicObj*, m_pPlayer, Player);
	map<string, list<cDynamicObj*>>		m_mapMonster;

public:
	void AddMonster(string sKey, cDynamicObj* pMonster);

	map<string, list<cDynamicObj*>>* GetMonsterMap() { return &m_mapMonster; }

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

