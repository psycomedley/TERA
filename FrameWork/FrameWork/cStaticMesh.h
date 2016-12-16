#pragma once
#include "cMesh.h"

class cStaticMesh : public cMesh
{
	friend class cMeshMgr;

protected:
	LPD3DXMESH					m_pMesh;
	LPD3DXBUFFER				m_pSubSetBuffer;
	DWORD						m_dwSubSetCnt;

	LPD3DXEFFECT				m_pEffect;
	LPDIRECT3DTEXTURE9			m_DiffuseTex;
	LPDIRECT3DTEXTURE9			m_SpecularTex;
	E_SHADER_TYPE				m_ShadeType;

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
	cStaticMesh(char* szFolder, char* szFilename, E_SHADER_TYPE ShadeType = E_SHADER_TYPE_END);
	~cStaticMesh();

	vector<D3DXVECTOR3>* GetVecVertaxies(){ return &m_vecVertaxies; }
	vector<ST_PNT_VERTEX>* GetVecPNTVertaxies(){ return &m_vecPNTVertaxies; }
	DWORD GetStaticMeshFVF(){ return m_pMesh->GetFVF(); }

	void SetShaderTexture();
protected:
	cStaticMesh();
	virtual HRESULT Load(char* szDirectory, char* szFilename) override;
};

