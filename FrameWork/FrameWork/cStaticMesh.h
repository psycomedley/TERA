#pragma once
#include "cMesh.h"

class cStaticMesh : public cMesh
{
	friend class cMeshMgr;

protected:
	LPD3DXMESH					m_pMesh;
	LPD3DXEFFECT				m_pEffect;
	LPD3DXBUFFER				m_pSubSetBuffer;
	DWORD						m_dwSubSetCnt;

	LPD3DXMATERIAL				m_pMaterials;
	vector<LPDIRECT3DTEXTURE9>	vecTexture;
	vector<D3DMATERIAL9>		vecMaterial;

	LPDIRECT3DVERTEXBUFFER9		m_VB;
	LPDIRECT3DINDEXBUFFER9		m_IB;

	vector<D3DXVECTOR3>			m_vecVertaxies;
	vector<ST_PNT_VERTEX>		m_vecPNTVertaxies;
	

public:
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	cStaticMesh(char* szFolder, char* szFilename);
	~cStaticMesh();

	vector<D3DXVECTOR3>* GetVecVertaxies(){ return &m_vecVertaxies; }
	vector<ST_PNT_VERTEX>* GetVecPNTVertaxies(){ return &m_vecPNTVertaxies; }
	DWORD GetStaticMeshFVF(){ return m_pMesh->GetFVF(); }
protected:
	cStaticMesh();
	virtual HRESULT Load(char* szDirectory, char* szFilename) override;
};

