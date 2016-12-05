#pragma once

class cCamera;
class cCameraMgr : public cSingleton<cCameraMgr>
{
private:
	cCamera*	m_pCamera;

public:
	cCamera* GetCamera() { return m_pCamera; }

public:
	HRESULT Setup();
	void Update();
	void Release();

public:
	cCameraMgr();
	~cCameraMgr();
};

#define CAMERA cCameraMgr::GetInst()->GetCamera()
