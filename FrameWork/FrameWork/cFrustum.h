#pragma once

class cBoundingSphere;
class cFrustum : public cSingleton<cFrustum>
{
private:
	vector<D3DXVECTOR3>		m_vecV;
	vector<D3DXPLANE>		m_vecPlane;

public:
	void Setup();
	void Update();
	bool IsinFrustum(cBoundingSphere* pSphere);
	bool IsinFrustum(D3DXVECTOR3* v);

public:
	cFrustum();
	~cFrustum();
};

