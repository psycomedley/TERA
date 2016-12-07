#pragma once

#include "cDynamicEffectObj.h"
#include "cDynamicObj.h"
class cDynamicMeshEffect : public cDynamicEffectObj
{
private:

public:
	//virtual void ChangeState(iState* pState, int nSkillIndex = -1) override;
	//virtual void ChangeState(int pState, int nSkillIndex = -1) override;

	//bool IsMoveAble();

	cDynamicMeshEffect(char* szFolder, char* szFilename);
	~cDynamicMeshEffect();

	HRESULT Setup();
	void Update();
	void Render();
};
