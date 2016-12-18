#pragma once
#include "cEffect.h"

class cEffectThunderGlobe : public cEffect
{
public:
	virtual void Start() override;

public:
	virtual void Update() override;

public:
	cEffectThunderGlobe();
	cEffectThunderGlobe(cEffectThunderGlobe* pEffect);
	~cEffectThunderGlobe();
};

