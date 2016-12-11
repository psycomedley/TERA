#pragma once
class cUIObject
{
protected:
	vector<cUIObject*>	m_vecChild;
	D3DXMATRIXA16		m_matWorld;
	SYNTHESIZE_ADD_REF(LPD3DXSPRITE, m_pSprite, Sprite);
	SYNTHESIZE(D3DXVECTOR3, m_vPosition, Position);
	SYNTHESIZE(ST_SIZE, m_stSize, Size);
	//SYNTHESIZE(float, m_fWidth, Width);
	//SYNTHESIZE(float, m_fHeight, Height);
	SYNTHESIZE(int, m_nTag, Tag);
	SYNTHESIZE(D3DCOLOR, m_dwColor, Color);
	SYNTHESIZE(float, m_fScaleX, ScaleX);
	SYNTHESIZE(float, m_fScaleY, ScaleY);

public:
	cUIObject* FindChildByTag(int nTag);
	virtual void SetCenterPosition(D3DXVECTOR3 vPosition) {}

public:
	virtual void AddChild(cUIObject* pChild);
	virtual void Update(D3DXMATRIXA16* pParent);
	virtual void Render();
	virtual void Release();

public:
	cUIObject();
	~cUIObject();
};

