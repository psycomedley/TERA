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
class cUIImageView;
class cText;
class cAlphaText;
class cUIObject;
class cMainGame
{
private:
	cCube*				cube;

	cDynamicObj*		m_pBoss2;

	cMap*				m_pMap;
	cGrid*				m_pGrid;
	
	cStaticObj*			m_cObjectTree;

	bool				m_bLockMouse;




	//юс╫ц
	int a = 0;
	float b = 0.1;

	cEffect*			m_pEffect;
	cEffect*			m_pEffect2;

	cDynamicMeshEffect*	m_pDynamicMeshEffect;

	cCircleEffect*		m_pCircleEffect;

//	cUIImageView*		m_pUICross;
//	cUIObject*			m_pUIBossHp;
	cUIObject*			m_pUIPlayerHp;

	void SetLighting();

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

