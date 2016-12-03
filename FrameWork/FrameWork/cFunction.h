#include <time.h>
#include <stdlib.h>

namespace MY_FUNCTION
{
	int GetInt(int num);
	int GetFromIntTo(int fromNum, int toNum);

	//getFloat 
	//0.0 ~ 1.0 RAND_MAX의 최대값 (32767)
	float GetFloat(void);
	float GetFloat(float num);
	float GetFromFloatTo(float fromNum, float toNum);
}