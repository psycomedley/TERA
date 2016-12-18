#pragma once
class cSoundMgr : public cSingleton<cSoundMgr>
{
public:
	void Release();

public:
	cSoundMgr();
	~cSoundMgr();
};

