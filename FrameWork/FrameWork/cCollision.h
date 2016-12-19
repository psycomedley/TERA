#pragma once
#include "cSingleton.h"

class cRay;
class cBoundingBox;
class cBoundingSphere;
class cPlayer;
class cDynamicObj;
class cCollision : public cSingleton<cCollision>
{
public:
	bool Collision(cRay* pRay, cBoundingSphere* pSphere);
	bool Collision(cBoundingSphere* pSphere, cRay* pRay);
	bool Collision(cBoundingSphere* pSphere1, cBoundingSphere* pSphere2);
	bool Collision(cBoundingBox* pBox1, cBoundingBox* pBox2);
	bool CollisionOBB(cBoundingBox* pBox1, cBoundingBox* pBox2);

	bool Collision(cPlayer* pPlayer, cDynamicObj* pMonster);

public:
	void Release();

public:
	cCollision();
	~cCollision();
};

