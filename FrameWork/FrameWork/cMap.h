#pragma once
#include"cStaticMesh.h"
#include"cStaticObj.h"

class cFrustum;

class cMap:public cStaticObj
{
private:
	D3DXMATRIXA16			m_matWorld;
	cFrustum*				m_cFrustum;

	vector<D3DXVECTOR3>		m_vecCullingVertexies;
	vector<D3DXVECTOR3>		m_vecVertex;

public:
	cMap(char* szFolder, char* szFilename);
	~cMap();

	virtual void Update() override;
	virtual void Render() override;

	bool GetHeight(IN float x, OUT float& y, IN float z, IN vector<D3DXVECTOR3> pVecVertex);
	vector<D3DXVECTOR3>* FindCullingVertex();

private:
	cMap();
};

