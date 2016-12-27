#pragma once

class cDynamicObj;
class cBattleMgr : public cSingleton<cBattleMgr>
{
private:
	bool		m_bMultiHit;				//for Player
	float		m_fDamageTime;				//for Player
	vector<cDynamicObj*> m_vecHitted;		//for Player
	SYNTHESIZE(bool, m_bHit, Hit);			//for Player
	SYNTHESIZE(bool, m_bHitted, Hitted);	//for Monster

public:
	void PlayerDamage(bool bDoubleHit, float fAddDamage = 0.0f);
	void EnemyDamage(cDynamicObj* pParent, cBoundingSphere sphere, float fAddDamage = 0.0f, bool bMultieHit = false, float fDamageTime = 0.0f);
	void Reset(E_OBJTYPE eType);
	void ResetList(E_OBJTYPE eType);

	void Update();
	void Release();

public:
	cBattleMgr();
	~cBattleMgr();
};

