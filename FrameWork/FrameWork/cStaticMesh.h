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

public:
	virtual void Update();
	virtual void Render();
	virtual void Release();

public:
	cStaticMesh(char* szFolder, char* szFilename);
	~cStaticMesh();

protected:
	cStaticMesh();
	virtual HRESULT Load(char* szDirectory, char* szFilename) override;
};

