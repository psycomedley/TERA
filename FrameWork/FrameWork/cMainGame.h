#pragma once
#include "cUIButton.h"

class cCube;
class cCamera;
class cStaticMesh;
class cDynamicMesh;
class cDynamicObj;
class cStaticObj;
class cPlayer;
class cOrca;
class cGrid;
class cMap;
class cEffect;
class cStaticMeshEffect;
class cDynamicMeshEffect;
class cCircleEffect;
class cRushEffect;
class cUIImageView;
class cText;
class cAlphaText;
class cUIObject;
class cObjectTool;
class cSkyBox;
class cMainGame
{
private:
	cMap*				m_pMap;
	cObjectTool*		m_cObjectTool;
	cSkyBox*			m_cSkyBox;
	bool				m_bLockMouse;



	//юс╫ц
	int a = 0;
	float b = 0.1;

	//cEffect*			m_pEffect4;

	//cDynamicMeshEffect*	m_pDynamicMeshEffect;
	//cCircleEffect*		m_pCircleEffect;
	//cRushEffect*		m_pRushEffect;

	void SetCamera();
	void SetLighting();
	void SetUI();
	void SetShader();
	void SetEffect();
	void MonsterPositionSetting();


	//cDynamicMesh*	m_pMesh;
	//cDynamicMesh*	m_pMesh2;

	//	cDynamicObj*	m_pPlayer;
	//	cDynamicObj*	m_pBoss;


public:
	HRESULT		Setup();
	void		Update();
	void		Render();
	void		Release();

public:
	cMainGame();
	~cMainGame();
};

