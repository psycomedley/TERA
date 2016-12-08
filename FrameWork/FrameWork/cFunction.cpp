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

	RECT RectMake(int x, int y, int width, int height)
	{
		RECT rc = { x, y, x + width, y + height };
		return rc;
	}
	RECT RectMakeCenter(int x, int y, int width, int height)
	{
		RECT rc = { x - (width / 2), y - (height / 2), x + (width / 2), y + (height / 2) };
		return rc;
	}

	int GetWindowWidth()
	{
		RECT rect;
		GetClientRect(g_hWnd, &rect);
		return (rect.right - rect.left);
	}
	int GetWindowHeight()
	{
		RECT rect;
		GetClientRect(g_hWnd, &rect);
		return (rect.bottom - rect.top);
	}
	void LockMouse()
	{
		POINT pWinPos = MOUSE->GetWindowPos();

		int nWidth = GetWindowWidth();
		int nHeight = GetWindowHeight();

		if (pWinPos.x <= 0)
			pWinPos.x = 0;
		else if (pWinPos.x >= nWidth - 1)
			pWinPos.x = nWidth - 1;
		if (pWinPos.y <= 0)
			pWinPos.y = 0;
		else if (pWinPos.y >= nHeight - 1)
			pWinPos.y = nHeight - 1;
		ClientToScreen(g_hWnd, &pWinPos);
		
		SetCursorPos(pWinPos.x, pWinPos.y);
	}
	void FixMouse()
	{
		POINT fixPos = MOUSE->GetFixPos();
		SetCursorPos(fixPos.x, fixPos.y);
	}

	POINT GetCursorPosition()
	{
		POINT pos;
		GetCursorPos(&pos);
		return pos;
	}
	bool IsActive()
	{
		if (GetActiveWindow())
			return true;
	}

	void DevideFilename(string szFile, string& filename, string& extension)
	{
		int dotIdx = szFile.find_last_of(".");
		int underlineIdx = szFile.find_last_of("_");
		filename = szFile.substr(0, underlineIdx);
		extension = szFile.substr(dotIdx, szFile.length());
	}
}