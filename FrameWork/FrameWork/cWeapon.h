#pragma once
#include "cStaticMesh.h"
#include "cStaticObj.h"

class cWeapon : public cStaticObj
{
private:
//	SYNTHESIZE(string, m_sHolderKey, HolderKey);
	string m_sHolderKey;
	D3DXMATRIXA16 m_matWorld;
	SYNTHESIZE(string, m_sParentKey, ParentKey);
	SYNTHESIZE(D3DXMATRIXA16*, m_matParent, MatParent);

	SYNTHESIZE(float, m_fHolderScale, HolderScale);

//	SYNTHESIZE(D3DXVECTOR3, m_vScale, Scale);

public:
	virtual cBoundingBox GetBox() override;
	virtual cBoundingSphere GetSphere() override;

	string GetHolderKey() { return m_sHolderKey; }
	void SetHolderKey(char* szFolder, char* szFilename) { m_sHolderKey = string(szFolder) + string("/") + string(szFilename); }

	HRESULT SetParentMat();

private:
	void SetWorldMat();

public:
	virtual void Update() override;
	virtual void Render() override;

public:
	cWeapon(char* szFolder, char* szFilename);
	~cWeapon();

private:
	cWeapon();
};
