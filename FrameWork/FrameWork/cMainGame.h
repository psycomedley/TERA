#pragma once
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
class cStuff;
class cMainGame
{
private:
	cCube*				cube;

	cMap*				m_pMap;
	cGrid*				m_pGrid;
	
	cStuff*				m_cObjectTree;

	bool				m_bLockMouse;




	//юс╫ц
	int a = 0;
	float b = 0.1;

	cEffect*			m_pEffect;
	cEffect*			m_pEffect2;
	cEffect*			m_pEffect3;

	cDynamicMeshEffect*	m_pDynamicMeshEffect;
	cCircleEffect*		m_pCircleEffect;
	cRushEffect*		m_pRushEffect;

	void SetLighting();
	void SetUI();
	void SetShader();

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

