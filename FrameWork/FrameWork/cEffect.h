#pragma once
class cPlayer;
class cEffect
{
private:
	std::vector<ST_PCT_VERTEX> m_vecVertex1;	//fire
	std::vector<ST_PCT_VERTEX> m_vecVertex2;	//attack


	int fireFrameTimer;
	int fireFrameNumber;
	bool startAttackEffect;
	int attackFrameTimer;
	int attackFrameNumber;

public:
	cEffect();
	~cEffect();

	void Setup();
	void Update();
	void Render();
	void setFireFrame(int fn);
	void attackEffectFrame();
	void fireEffectSetup();
	void attackEffectSetup();
};

