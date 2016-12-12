#pragma once
#define M_EPSILON 0.001

#include"cStaticMesh.h"
#include"cStaticObj.h"

class cFrustum;
class cBoundingSphere;

class cMap :public cStaticObj
{
private:
	vector<cBoundingSphere*> m_vecBoundingSphere;
	cBoundingSphere*		m_cBoundingSphere;

	D3DXMATRIXA16			m_matWorld;

	cFrustum*				m_cFrustum;

	vector<D3DXVECTOR3>		m_vecVertex;
	vector<ST_PNT_VERTEX>	m_vecPNTVertex;
	vector<float>			m_vecHeight;
	vector<D3DXVECTOR3>		m_CoodVecVertex;
	vector<D3DXVECTOR3>		m_vecTerrainVertex;

	// height 얻기위한 변수

	int MapSize;
	int IndexX;
	int Indexy; 
	int NumTile;
	float tileSpacing;

	float MaxX = FLT_MIN;
	float MinX = FLT_MAX;
	float MaxZ = FLT_MIN;
	float MinZ = FLT_MAX;

public:
	cMap(char* szFolder, char* szFilename);
	~cMap();

	virtual void Update() override;
	virtual void Render() override;

	vector<D3DXVECTOR3>* GetVertexies(){ return &m_vecVertex; }
	bool GetHeight(IN float x, OUT float& y, IN float z, IN vector<D3DXVECTOR3>	pVecVertex);
	void SetupHeight();
	bool GetHeight(IN float x, OUT float& y, IN float z);
	vector<D3DXVECTOR3>* cMap::FindCullingVertex();
private:
	cMap();
};

