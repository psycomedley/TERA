#pragma once

class cGameObject;
class cCamera
{
private:
	D3DXVECTOR3		m_vEye;
	D3DXVECTOR3		m_vLookAt;
	D3DXVECTOR3		m_vUp;

	float			m_fCamDist;
	float			m_fPrevDist;
	SYNTHESIZE(float, m_fCamRotX, CamRotX);
	SYNTHESIZE(float, m_fCamRotY, CamRotY);

	SYNTHESIZE(bool, m_bUse, Use);
	SYNTHESIZE(bool, m_bControl, Control);
	SYNTHESIZE(cGameObject*, m_pTarget, Target);
	SYNTHESIZE(D3DXVECTOR3*, m_vTarget, VecTarget);

public:
	cCamera(void);
	~cCamera(void);

	void Setup();
//	void Update(D3DXVECTOR3* pTarget = NULL);
	void Update();
	void CameraMove();

	//
	void WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);
};

