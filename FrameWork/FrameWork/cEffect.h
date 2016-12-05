#pragma once
class cEffect
{
private:
	std::vector<ST_PCT_VERTEX> m_vecVertex1;

	int frameTimer;
	int frameNumber;

public:
	cEffect();
	~cEffect();

	void Setup();
	void Update();
	void Render();
	void setFrame(int fn);
};

