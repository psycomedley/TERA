#pragma once
#include "cGameObject.h"
#include "cBoundingBox.h"
#include "cBoundingSphere.h"

class cMesh
{
protected:
	SYNTHESIZE(D3DXVECTOR3, m_vMin, vMin);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, vMax);

	cBoundingBox* m_pBox;
	cBoundingSphere* m_pSphere;

public:
	virtual HRESULT Load(char* szFolder, char* szFile) PURE;

public:
	HRESULT SetupBounding(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax);
	HRESULT ReSetupBoundingBox(D3DXVECTOR3 vMin, D3DXVECTOR3 vMax);
	cBoundingBox GetBox(D3DXVECTOR3 vPosition, float fScale, float fAngle = 0);
	cBoundingBox GetBox(D3DXMATRIXA16* mat);
	cBoundingSphere GetSphere(D3DXVECTOR3 vPosition, float fScale);
	cBoundingSphere GetSphere(D3DXMATRIXA16* mat);

public:
	virtual void Render();
	void Bounding_Update(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, float fAngle = 0, D3DXMATRIXA16* matRevision = NULL);
	void Bounding_Render(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, float fAngle = 0, D3DXMATRIXA16* matRevision = NULL);
	virtual void Release();

public:
	cMesh();
	~cMesh();
};

