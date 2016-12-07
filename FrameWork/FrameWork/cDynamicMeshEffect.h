#pragma once
<<<<<<< HEAD
#include "cDynamicEffectObj.h"
class cDynamicMeshEffect : public cDynamicEffectObj
=======
#include "cDynamicObj.h"
class cDynamicMeshEffect/* : public cDynamicObj*/
>>>>>>> f066ad06ff51ddca91a3deab0d1081d14c69b0c7
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

