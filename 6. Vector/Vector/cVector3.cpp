#include "StdAfx.h"
#include "cVector3.h"


cVector3::cVector3(void)
	: x(0.0f)
	, y(0.0f)
	, z(0.0f)
{
}

cVector3::cVector3( float _x, float _y, float _z )
	: x(_x)
	, y(_y)
	, z(_z)
{
}

cVector3::~cVector3(void)
{
}

bool cVector3::operator==( cVector3& v )
{
	if(fabs(x - v.x) >= EPSILON) return false;
	if(fabs(y - v.y) >= EPSILON) return false;
	if(fabs(z - v.z) >= EPSILON) return false;
	return true;
}

bool cVector3::operator!=( cVector3& v )
{
	return !((*this) == v);
}

cVector3 cVector3::operator+( cVector3& v )
{
	return cVector3(x + v.x, y + v.y, z + v.z);
}

cVector3 cVector3::operator-( cVector3& v )
{
	return cVector3(x - v.x, y - v.y, z - v.z);
}

cVector3 cVector3::operator*( float f )
{
	return cVector3(x * f, y * f, z * f);
}

cVector3 cVector3::Normalize()
{
	float l = Length();
	return cVector3(x / l, y / l, z / l);
}

float cVector3::Length()
{
	return sqrt(x * x + y * y + z * z);
}

float cVector3::Dot( cVector3& v1, cVector3& v2 )
{
	return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

cVector3 cVector3::Cross( cVector3& v1, cVector3& v2 )
{
	return cVector3(v1.y * v2.z - v1.z * v2.y,
		v1.z * v2.x - v1.x * v2.z,
		v1.x * v2.y - v1.y * v2.x);
}

void cVector3::Print()
{

}
