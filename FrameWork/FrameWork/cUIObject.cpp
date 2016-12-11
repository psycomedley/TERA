#include "stdafx.h"
#include "cUIObject.h"


cUIObject::cUIObject()
	: m_pSprite(NULL)
	, m_vPosition(0, 0, 0)
	, m_stSize(0, 0)
	, m_nTag(-1)
	, m_dwColor(XWHITE)
	, m_fScaleX(1.0f)
	, m_fScaleY(1.0f)
{
	D3DXMatrixIdentity(&m_matWorld);
}


cUIObject::~cUIObject()
{
}


void cUIObject::AddChild(cUIObject* pChild)
{
	m_vecChild.push_back(pChild);
}


void cUIObject::Update(D3DXMATRIXA16* pParent)
{
	D3DXMATRIXA16 matS;
	D3DXMatrixScaling(&matS, m_fScaleX, m_fScaleY, 1);
//	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld = matS;

	m_matWorld._41 = m_vPosition.x;
	m_matWorld._42 = m_vPosition.y;
	m_matWorld._43 = m_vPosition.z;

	if (pParent)
	{
		m_matWorld._41 += pParent->_41;
		m_matWorld._42 += pParent->_42;
		m_matWorld._43 += pParent->_43;
	}

	for each(auto p in m_vecChild)
		p->Update(&m_matWorld);
}


void cUIObject::Render()
{
	for each(auto p in m_vecChild)
		p->Render();
}


void cUIObject::Release()
{
	SAFE_RELEASE(m_pSprite);

	for each(auto p in m_vecChild)
	{
		SAFE_RELEASE(p);
		SAFE_DELETE(p);
	}
}


cUIObject* cUIObject::FindChildByTag(int nTag)
{
	if (m_nTag == nTag)
		return this;

	for each(auto pChild in m_vecChild)
	{
		cUIObject* p = pChild->FindChildByTag(nTag);
		if (p)
			return p;
	}
	return NULL;
}