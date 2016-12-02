#pragma once
#include "cGameObject.h"
#include "cBoundingBox.h"
#include "cBoundingSphere.h"

class cMesh
{
protected:
	SYNTHESIZE(D3DXVECTOR3, m_vMin, vMin);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, vMax);

	SYNTHESIZE(cBoundingBox*, m_pBox, Box);
	SYNTHESIZE(cBoundingSphere*, m_pSphere, Sphere);

public:
	virtual HRESULT Load(char* szFolder, char* szFile) PURE;

public:
	HRESULT SetupBounding(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax);

public:
	virtual void Render();
	void Bounding_Render();
	virtual void Release();

public:
	cMesh();
	~cMesh();
};

