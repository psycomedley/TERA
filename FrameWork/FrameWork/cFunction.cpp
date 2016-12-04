#include "stdafx.h"
#include "cFunction.h"

namespace MY_FUNCTION
{
	int GetInt(int nNum) { return rand() % nNum; }
	int GetFromIntTo(int fromNum, int toNum) { return (rand() % (toNum - fromNum + 1)) + fromNum; }

	//getFloat 
	//0.0 ~ 1.0 RAND_MAX의 최대값 (32767)
	float GetFloat(void) { return (float)rand() / (float)RAND_MAX; }
	float GetFloat(float num) { return (float)rand() / (float)RAND_MAX * num; }
	float GetFromFloatTo(float fromNum, float toNum)
	{
		float rnd = (float)rand() / (float)RAND_MAX;
		return (rnd * (toNum - fromNum) + fromNum);
	}
}