#pragma once
class cObjectTool;

class cObjectToolMgr : public cSingleton<cObjectToolMgr>
{
private:
	D3DXVECTOR3		m_PrevPlayerPos;
public:
	cObjectToolMgr();
	~cObjectToolMgr();
	void Setup();
	void Update();
	void Render();
};

