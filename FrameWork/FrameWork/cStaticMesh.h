#pragma once
#include "cMesh.h"

class cStaticMesh : public cMesh
{
	friend class cMeshMgr;

protected:
	LPD3DXMESH					m_pMesh;
	LPD3DXBUFFER				m_pSubSetBuffer;
	DWORD						m_dwSubSetCnt;

	LPD3DXMATERIAL				m_pMaterials;
	vector<LPDIRECT3DTEXTURE9>	vecTexture;
	vector<D3DMATERIAL9>		vecMaterial;

	LPDIRECT3DVERTEXBUFFER9		m_VB;
	LPDIRECT3DINDEXBUFFER9		m_IB;

	vector<D3DXVECTOR3>			m_vecVertaxies;
	vector<ST_PNT_VERTEX>		m_vecPNTVertaxies;

	//특정 서브셋의 컬모드를 위한변수
	SYNTHESIZE(bool, m_IsCullMode, IsCullMode);
	SYNTHESIZE(DWORD, m_DwSubSetNum, DwSubSetNum);//특정서브셋의 번호
	

public:
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	cStaticMesh(char* szFolder, char* szFilename);
	~cStaticMesh();

	vector<D3DXVECTOR3>* GetVecVertaxies(){ return &m_vecVertaxies; }
	vector<ST_PNT_VERTEX>* GetVecPNTVertaxies(){ return &m_vecPNTVertaxies; }
	
protected:
	cStaticMesh();
	virtual HRESULT Load(char* szDirectory, char* szFilename) override;
};

