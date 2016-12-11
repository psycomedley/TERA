#pragma once
#include "cUIObject.h"

class iButtonDelegate
{
public:
	virtual void OnClick(cUIObject* pObj) PURE;
};

class cUIButton : public cUIObject
{
private:
	enum eBtnState
	{
		BTN_NORMAL,
		BTN_MOUSEOVER,
		BTN_DOWN,
		BTN_END,
	};

	eBtnState				m_eBtnState;
	LPDIRECT3DTEXTURE9		m_aTexture[BTN_END];
	SYNTHESIZE(iButtonDelegate*, m_pDelegate, Delegate);

public:
	void SetTexture(string sNormal, string sMouseOver, string sDown);

public:
	virtual void Update(D3DXMATRIXA16* pParent) override;
	virtual void Render() override;

public:
	cUIButton();
	~cUIButton();
};

