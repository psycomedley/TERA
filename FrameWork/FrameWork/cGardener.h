#pragma once
#include "cMonster.h"

class iState;
//class cGardener : public cMonster
//{
//private:
//	ST_SKILL_INFO	m_skillRush;
//	ST_SKILL_INFO	m_skillAttack;
//
//public:
//	virtual void ChangeState(iState* pState, int nSkillIndex = -1) override;
//	virtual void ChangeState(int pState, int nSkillIndex = -1) override;
//
//public:
//	virtual void UpdateAndRender(D3DXMATRIXA16* pmat) override;
//
//	virtual bool IsMoveAble() override;
//
//public:
//	cGardener(char* szFolder, char* szFilename);
//	~cGardener();
//
//private:
//	cGardener();
//	virtual void SetupState() override;
//	virtual void SetupStatus() override;
//	virtual void Update() override;
//};

class cGardener
{
public:
	cGardener();
	~cGardener();
};

