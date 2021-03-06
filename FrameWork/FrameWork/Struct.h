#include "stdafx.h"

struct ST_PC_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR	c;

	ST_PC_VERTEX() : p(0, 0, 0), c(D3DCOLOR_XRGB(0, 0, 0)) {}
	ST_PC_VERTEX(D3DXVECTOR3 _p, D3DCOLOR _c) : p(_p), c(_c) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE, };
};

struct ST_PT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR2	t;

	ST_PT_VERTEX() : p(0, 0, 0), t(0, 0) {}
	ST_PT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR2 _t) : p(_p), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};

struct ST_PNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;

	ST_PNT_VERTEX() : p(0, 0, 0), n(0, 0, 0), t(0, 0) {}
	ST_PNT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _n, D3DXVECTOR2 _t) : p(_p), n(_n), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};

struct ST_PPPNT_VERTEX
{
	D3DXVECTOR3 p;
	D3DXVECTOR3 p0;
	D3DXVECTOR3 p1;
	D3DXVECTOR3 n;
	D3DXVECTOR2	t;

	ST_PPPNT_VERTEX() : p(0, 0, 0), p0(0, 0, 0), p1(0, 0, 0), n(0, 0, 0), t(0, 0) {}
	ST_PPPNT_VERTEX(D3DXVECTOR3 _p, D3DXVECTOR3 _p0, D3DXVECTOR3 _p1, D3DXVECTOR3 _n, D3DXVECTOR2 _t) 
		: p(_p), p0(_p0), p1(_p1), n(_n), t(_t) {}

	enum { FVF = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_TEX1, };
};


struct ST_BONE : public D3DXFRAME
{
	D3DXMATRIXA16 CombinedTransformationMatrix;
};


struct ST_BONE_MESH : public D3DXMESHCONTAINER
{
	vector<LPDIRECT3DTEXTURE9>	vecTexture;
	vector<D3DMATERIAL9>		vecMaterial;

	LPD3DXMESH			pOrigMesh;
	LPD3DXMESH			pWorkingMesh;
	D3DXMATRIXA16**		ppBoneMatrixPtrs;
	D3DXMATRIXA16*		pBoneOffsetMatrices;

	DWORD				dwNumPaletteEntries;
	DWORD				dwMaxNumFaceInfls;
	DWORD				dwNumAttrGroups;
	LPD3DXBUFFER		pBufBoneCombos;

	vector<LPDIRECT3DTEXTURE9>	vecTextureNormal;
	vector<LPDIRECT3DTEXTURE9>	vecTextureSpecular;
	vector<LPDIRECT3DTEXTURE9>	vecTextureMask;
	vector<LPDIRECT3DTEXTURE9>	vecTextureEmission;

	ST_BONE_MESH() : pOrigMesh(NULL), pWorkingMesh(NULL) {}
};


struct ST_ANIMATION_INFO
{
	int		nIndex;
	bool	bPlayOnce;
	bool	bBlend;

	ST_ANIMATION_INFO() : nIndex(-1), bPlayOnce(false), bBlend(true) {}
	ST_ANIMATION_INFO(int _nIndex, bool _bPlayOnce, bool _bBlend = true) : nIndex(_nIndex), bPlayOnce(_bPlayOnce), bBlend(_bBlend) {}

	void SetInfo(int _nIndex, bool _bPlayOnce, bool _bBlend) { nIndex = _nIndex; bPlayOnce = _bPlayOnce; bBlend = _bBlend; }
};


struct ST_UNIT_INFO
{
	string	sName;

	float	fMaxHp;
	float	fHp;
	float	fMaxMp;
	float	fMp;
	float	fDamage;
	float	fMinDamage;
	float	fMaxDamage;
	float	fDefence;
};


struct ST_SKILL_INFO
{
	float	fCoolTime;
	float	fPassedTime;
	float	fValue;
	string	sSpeech;
	bool	bUseAble;

	void SetInfo(float _fCoolTime, float _fValue, bool _bUseAble = true, string _sSpeech = "") { fCoolTime = _fCoolTime; fPassedTime = 0; fValue = _fValue; sSpeech = _sSpeech; bUseAble = _bUseAble; }
};


struct ST_TEXT
{
	LPD3DXSPRITE	pSprite;
	E_FONT_TYPE		eFontType;
	string			sText;
	float			fShowTime;
	float			fPassedTime;
	RECT			rect;
	bool			bRender;

	ST_TEXT() : pSprite(NULL), eFontType(E_FONT_END), sText(""), fShowTime(0.0f), fPassedTime(0.0f) { bRender = true; }
	ST_TEXT(E_FONT_TYPE _eType, string _sText, float _fShowTime, RECT _rect) : eFontType(_eType), sText(_sText), fShowTime(_fShowTime), fPassedTime(0.0f), rect(_rect) { bRender = true; }
};

struct ST_PCT_VERTEX
{
	D3DXVECTOR3 p;
	D3DCOLOR c;
	D3DXVECTOR2 t;

	ST_PCT_VERTEX() : p(0, 0, 0), c(D3DCOLOR_XRGB(255, 255, 255)), t(0, 0) {}
	ST_PCT_VERTEX(D3DXVECTOR3 _p, D3DXCOLOR _c, D3DXVECTOR2 _t) : p(_p), c(_c), t(_t) {}

	enum {FVF = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1,};
};

struct ST_SIZE
{
	float	fWidth;
	float	fHeight;
	
	ST_SIZE() : fWidth(0), fHeight(0) {}
	ST_SIZE(float _fWidth, float _fHeight) : fWidth(_fWidth), fHeight(_fHeight) {}
};

struct ST_OBB
{
	D3DXVECTOR3 vOrgCenterPos;
	D3DXVECTOR3 vOrgAxisDir[3];

	D3DXVECTOR3 vCenterPos;		// 상자 중앙의 좌표
	D3DXVECTOR3 vAxisDir[3];		// 상자에 평행한 세 축의 단위벡터
	float		fAxisLen[3];		// 상자의 평행한 세 축의 길이 fAxisLen[n]은 vAxisDir[n]에 각각 대응한다.
	float		fAxisHalfLen[3];
};

struct SKYVERTEX
{
	float x, y, z, u, v;

	enum { FVF = D3DFVF_XYZ | D3DFVF_TEX1, };
};