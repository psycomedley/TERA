#pragma once

class cCamera;
class cCameraMgr : public cSingleton<cCameraMgr>
{
private:
	map<string, cCamera*> m_mapCamera;
	cCamera*	m_pCurrentCamera;

public:
	void AddCamera(string sKey, cCamera* pCamera);

public:
	cCamera* GetCurrentCamera() { return m_pCurrentCamera; }
	cCamera* GetCamera(string sKey);

	void SetCurrentCamera(string sKey) { m_pCurrentCamera = m_mapCamera[sKey]; }

public:
	HRESULT Setup();
	void Update();
	void Release();

public:
	cCameraMgr();
	~cCameraMgr();
};

#define CAMERA cCameraMgr::GetInst()->GetCamera("MainCamera")
