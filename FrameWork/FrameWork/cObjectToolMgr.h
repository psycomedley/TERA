#pragma once
class cObjectTool;

class cObjectToolMgr : public cSingleton<cObjectToolMgr>
{
private:

public:
	cObjectToolMgr();
	~cObjectToolMgr();
	void Setup();
	void Update();
	void Render();
};

