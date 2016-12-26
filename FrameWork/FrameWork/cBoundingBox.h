#pragma once
#include "cBounding.h"

class cBoundingBox : public cBounding
{
private:
	/*LPD3DXMESH		m_pBoxMesh;*/

	SYNTHESIZE(D3DXVECTOR3, m_vMin, vMin);
	SYNTHESIZE(D3DXVECTOR3, m_vMax, vMax);

	ST_OBB m_stObb;
	//D3DXVECTOR3 m_vOrgCenterPos;
	//D3DXVECTOR3 m_vOrgAxisDir[3];

	//D3DXVECTOR3 m_vCenterPos;		// ���� �߾��� ��ǥ
	//D3DXVECTOR3 m_vAxisDir[3];		// ���ڿ� ������ �� ���� ��������
	//float		m_fAxisLen[3];		// ������ ������ �� ���� ���� fAxisLen[n]�� vAxisDir[n]�� ���� �����Ѵ�.
	//float		m_fAxisHalfLen[3];

public:
	ST_OBB GetObb() { return m_stObb; }

public:
	HRESULT Setup(D3DXVECTOR3* pMin, D3DXVECTOR3* pMax);
	HRESULT ReSetup(float Scale);
	void Update(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, float fAngle, D3DXMATRIXA16* matRevision = NULL);
	void Render(D3DXVECTOR3 vPos, D3DXVECTOR3 vScale, float fAngle, D3DXMATRIXA16* matRevision = NULL);
	void Release();

public:
	cBoundingBox();
	~cBoundingBox();
};

