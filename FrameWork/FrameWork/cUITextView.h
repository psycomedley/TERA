#pragma once
#include "cUIObject.h"

class cUITextView : public cUIObject
{
private:
	SYNTHESIZE_ADD_REF(LPD3DXFONT, pFont, Font);
	SYNTHESIZE(string, m_sText, Text);
	SYNTHESIZE(DWORD, m_dwFormat, Format);
	SYNTHESIZE(D3DCOLOR, m_dwColor, Color);

public:
	virtual void Render() override;
	virtual void Release() override;

public:
	cUITextView();
	~cUITextView();
};

