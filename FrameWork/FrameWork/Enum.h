enum MOUSEBUTTON
{
	MOUSEBTN_LEFT,
	MOUSEBTN_RIGHT,
	MOUSEBTN_WHEEL,
	MOUSEBTN_END,
};

typedef enum _UNITSTATE
{
	STATE_IDLE,
	STATE_WALK,
	STATE_RUN,
	STATE_ATTACK,
	STATE_END,
} USTATE;

enum MESHTYPE
{
	MESHTYPE_STATIC,
	MESHTYPE_DYNAMIC,
};

enum E_STATE
{
	E_STATE_IDLE,
	E_STATE_RUN,
	E_STATE_DEFENCE,
	E_STATE_COMBO,
	E_STATE_WAIT,
	E_STATE_END,
};

enum E_ANIMATION_PLAYER
{
	E_ANI_IDLE,
	E_ANI_RUN,
	E_ANI_DEFENCE_START,
	E_ANI_DEFENCE_LOOP,
	E_ANI_DEFENCE_HIT,
	E_ANI_DEFENCE_CALCEL,
	E_ANI_WAIT,
	E_ANI_COMBO1,
	E_ANI_COMBO1R,
	E_ANI_COMBO2,
	E_ANI_COMBO2R,
	E_ANI_COMBO3,
	E_ANI_COMBO3R,
	E_ANI_COMBO4,
	E_ANI_COMBO4R,
	E_ANI_COMBO5,
	E_ANI_END,
};