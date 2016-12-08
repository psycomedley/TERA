#pragma once
#include "cUIObject.h"

class cUIImageView : public cUIObject
{
private:
	LPDIRECT3DTEXTURE9	m_pTexture;
	int					m_nFrameX;
	int					m_nFrameY;
	RECT				m_rect;

//	SYNTHESIZE(int, m_nCurrentFrame, CurrentFrame);
	int					m_nCurrentFrame;
	int					m_nFrameWidth;
	int					m_nFrameHeight;

	//연산없애려고..
	int					m_nFramePosX;
	int					m_nFramePosY;

public:
	void SetTexture(string sKey, int nFrameX, int nFrameY);
	virtual void SetCenterPosition(D3DXVECTOR3 vPosition) override;
	void SetCurrentFrame(int nFrame);

public:
	virtual void Render() override;

public:
	cUIImageView();
	~cUIImageView();
};

