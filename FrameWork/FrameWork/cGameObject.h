#pragma once
#include "cAction.h"

class cMesh;
class cGameObject : public cObject
{
protected:
	SYNTHESIZE(cMesh*, m_pMesh, pMesh);
	D3DXVECTOR3 m_vScale;
	SYNTHESIZE(D3DXVECTOR3, m_vRevisionScale, RevisionScale);
	SYNTHESIZE(D3DXVECTOR3, m_vPrevPosition, PrevPosition);

	SYNTHESIZE(D3DXVECTOR3, m_vRevisionPosition, RevisionPosition);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE_PASS_BY_REF(D3DXVECTOR3, m_vCameraFocus, CameraFocus);
	SYNTHESIZE(float, m_fAngle, Angle);
//	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);

	SYNTHESIZE_ADD_REF(cAction*, m_pAction, Action);
	SYNTHESIZE(D3DXVECTOR3, m_vDirection, Direction);
	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matWorld, WorldTM);

	SYNTHESIZE_PASS_BY_REF(D3DXMATRIXA16, m_matRevision, Revision);
	SYNTHESIZE(float, m_fRevisionAngle, RevisionAngle);

	SYNTHESIZE(float, m_fRotX, fRotX);
	SYNTHESIZE(float, m_fRotY, fRotY);
	SYNTHESIZE(float, m_fRotZ, fRotZ);

public:
	virtual void Move(float fSpeed);
	virtual void Move(D3DXVECTOR3 vec);

public:
	virtual cBoundingSphere GetSphere();
	virtual cBoundingBox GetBox();

public:
	D3DXVECTOR3 GetScale() { return m_vScale; }
	virtual void SetScale(D3DXVECTOR3 vScale) { m_vScale = vScale; }
//	D3DXVECTOR3 GetPosition() { return m_vPosition; }
//	void SetPosition(D3DXVECTOR3 vPos);
	void SetBoundingPos();
	bool IsMesh() { if (m_pMesh) return true; return false; }

public:
	virtual void Update();
	virtual void Render();
	void Bounding_Update();
	void Bounding_Render();

public:
	cGameObject(void);
	virtual ~cGameObject(void);
};
