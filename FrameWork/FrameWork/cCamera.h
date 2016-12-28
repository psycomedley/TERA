#pragma once

class cGameObject;
class cCamera
{
private:
	SYNTHESIZE(D3DXVECTOR3, m_vEye, Eye);
	SYNTHESIZE(D3DXVECTOR3, m_vLookAt, LookAt);
	SYNTHESIZE(D3DXVECTOR3, m_vUp, Up);

	SYNTHESIZE(float, m_fCamDist, CamDist);
	SYNTHESIZE(float, m_fPrevDist, PrevDist);
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
public:
};

