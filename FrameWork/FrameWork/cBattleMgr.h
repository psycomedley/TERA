#pragma once

class cDynamicObj;
class cBattleMgr : public cSingleton<cBattleMgr>
{
private:
	vector<cDynamicObj*> m_vecHitted;
	bool		m_bMultiHit;
	float		m_fDamageTime;
	SYNTHESIZE(bool, m_bHit, Hit);

public:
	void PlayerDamage(bool bDoubleHit);
	void EnemyDamage(cDynamicObj* pParent, cBoundingSphere sphere, bool bMultieHit = false, float fDamageTime = 0.0f);
	void Reset();
	void ResetList();

	void Update();
	void Release();

public:
	cBattleMgr();
	~cBattleMgr();
};

