#pragma once
class cText
{
protected:
	LPD3DXFONT		m_pFont;
	E_FONT_TYPE		m_eFontType;
	float			m_fPassedTime;					//ShowTime Option
	RECT			m_rect;
	DWORD			m_dwFormat;
	ST_SIZE			m_stSize;

	int				m_nOption;
	float			m_fElapseX;						//Move Option
	float			m_fElapseY;						//Move Option

	int				m_nCurrentAlpha;				//Alpha Option
	float			m_fPassedAlphaTime;				//Alpha Option

	float			m_fAlphaTime;					//Alpha Option
	float			m_fDecreasePerSecond;			//Alpha Option

	float			m_fPassedMoveTime;				//MoveAfterTime Option


	SYNTHESIZE(float, m_fShowTime, ShowTime);		//ShowTime Option
	SYNTHESIZE(int, m_nAlpha, Alpha);
	SYNTHESIZE(D3DXCOLOR, m_dwColor, Color);
	SYNTHESIZE(D3DXVECTOR2, m_vPosition, Position);
	SYNTHESIZE(string, m_sText, Text);
	SYNTHESIZE(string, m_sKey, Key);
	SYNTHESIZE(bool, m_bProcess, Process);
	SYNTHESIZE(float, m_fMoveSpeed, MoveSpeed);		//Move Option
	SYNTHESIZE(int, m_nDirection, Direction);		//Move Option
	SYNTHESIZE(float, m_fMoveTime, MoveTime);		//MoveAfterTime Option

public:
	void Start();
	void Stop();
	void ResetTime();
	void Move();									//Move Option
	void SetAlphaTime(float fAlphaTime);
	void SetTextInteger(int nNum);
	void SetTextFloat(float fNum);

public:
	/*virtual HRESULT Setup(E_FONT_TYPE eType, string sKey, string sText, float fShowTime,
		D3DXVECTOR2 vPosition, ST_SIZE stSize,
		D3DCOLOR dwColor = XWHITE,
		int nOption = TEXT_NONE,
		DWORD dwFormat = DT_VCENTER | DT_CENTER | DT_WORDBREAK);*/

	HRESULT Setup(E_FONT_TYPE eType, string sKey, string sText,
		D3DXVECTOR2 vPosition, ST_SIZE stSize,
		D3DCOLOR dwColor = XWHITE, int nOption = TEXT_NONE,
		DWORD dwFormat = DT_VCENTER | DT_CENTER | DT_WORDBREAK);

	virtual void Update(float fPassedTime);
	virtual void Render();

public:
	cText();
	cText(cText* pText);
	~cText();
};
