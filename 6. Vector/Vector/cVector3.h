#pragma once
class cVector3
{
public:
	cVector3(void);
	cVector3(float _x, float _y, float _z);
	~cVector3(void);

	float x, y, z;

	// ==, !=, +, -, *(scalar, 교환법칙), 
	bool operator == (cVector3& v);
	bool operator != (cVector3& v);
	cVector3 operator + (cVector3& v);
	cVector3 operator - (cVector3& v);
	cVector3 operator * (float f);
	cVector3 Normalize();
	float Length();
	static float Dot(cVector3& v1, cVector3& v2);
	static cVector3 Cross(cVector3& v1, cVector3& v2);
	void Print(); // (x, y, z) 소수 2째자리까지
};

