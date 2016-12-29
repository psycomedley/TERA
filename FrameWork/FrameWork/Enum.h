#define IDLESWITCHTIME	5.0f

#define	DIRECTION_NONE	0
#define	DIRECTION_LEFT	(1 << 0)
#define	DIRECTION_RIGHT	(1 << 1)
#define	DIRECTION_UP	(1 << 2)
#define	DIRECTION_DOWN	(1 << 3)

#define EFFECT_NONE			0
#define EFFECT_BILLBOARING	(1 << 0)
#define EFFECT_ALPHABLEND	(1 << 1)
#define EFFECT_CUTTEDFRAME	(1 << 2)
//#define EFFECT_LOOPEDFRAME	(1 << 3)

#define	TEXT_NONE				0
#define TEXT_ALPHA				(1 << 0)
#define TEXT_SHOWTIME			(1 << 1)
#define	TEXT_MOVE				(1 << 2)
#define TEXT_MOVEAFTERTIME		(1 << 3)
#define TEXT_SHOWAFTERTIME		(1 << 4)
#define TEXT_APPEARWITHALPHA	(1 << 5)

#define XWHITE		D3DCOLOR_XRGB(255, 255, 255)
#define XBLACK		D3DCOLOR_XRGB(0, 0, 0)
#define XRED		D3DCOLOR_XRGB(255, 0, 0)
#define XGREEN		D3DCOLOR_XRGB(0, 255, 0)
#define XBLUE		D3DCOLOR_XRGB(0, 0, 255)
#define XYELLOW		D3DCOLOR_XRGB(255, 255, 0)

#define AWHITE(a)	D3DCOLOR_ARGB(a, 255, 255, 255)
#define ABLACK(a)	D3DCOLOR_ARGB(a, 0, 0, 0)
#define ARED(a)		D3DCOLOR_ARGB(a, 255, 0, 0)
#define AGREEN(a)	D3DCOLOR_ARGB(a, 0, 255, 0)
#define ABLUE(a)	D3DCOLOR_ARGB(a, 0, 0, 255)
#define AYELLOW(a)	D3DCOLOR_ARGB(a, 255, 255, 0)

#define MAXSOUND	30

#define	RENDER_NONE				0
#define RENDER_BOUNDINGBOX		(1 << 0)
#define RENDER_BOUNDINGSPHERE	(1 << 1)
#define RENDER_BOUNDINGPLAYER	(1 << 2)
#define RENDER_BOUNDINGWEAPON	(1 << 3)
#define RENDER_BOUNDINGMONSTER	(1 << 4)
#define RENDER_BOUNDINGOBJECT	(1 << 5)
#define RENDER_FRUSTUMCULL		(1 << 6)


//enum E_DIRECTION
//{
//	E_NONE = 0,
//	E_LEFT = 1 << 0,
//	E_RIGHT = 1 << 1,
//	E_UP = 1 << 2,
//	E_DOWN = 1 << 3,
//};

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
	E_STATE_WAIT,
	E_STATE_DEFENCE,
	E_STATE_DEFENCE_HIT,
	E_STATE_COMBO,
	E_STATE_SKILL,
	E_STATE_DEATH,
	E_STATE_REACTION,
	E_STATE_HIT,
	E_STATE_END,
};

//enum E_BOSS_STATE
//{
//	E_BOSS_STATE_IDLE,
//	E_BOSS_STATE_RUN,
//	E_BOSS_STATE_WAIT,
//	E_BOSS_STATE_COMBO,
//	E_BOSS_STATE_SKILL,
//	E_BOSS_STATE_END,
//};

enum E_ANIMATION_COMMON
{
	E_ANI_IDLE,
	E_ANI_RUN,
	E_ANI_WAIT,
	E_ANI_DEATH,
	E_ANI_DEATHWAIT,
};

enum E_ANIMATION_MONSTER
{
	E_ANI_HIT = 5,
	E_ANI_ATTACK,
	E_ANI_SKILL1,
};

enum E_ANIMATION_PLAYER
{
	/*E_ANI_IDLE,
	E_ANI_RUN,
	E_ANI_WAIT,*/
	E_ANI_DEFENCE_START = 5,
	E_ANI_DEFENCE_LOOP,
	E_ANI_DEFENCE_HIT,
	E_ANI_DEFENCE_CALCEL,
	E_ANI_COMBO1,
	E_ANI_COMBO1R,
	E_ANI_COMBO2,
	E_ANI_COMBO2R,
	E_ANI_COMBO3,
	E_ANI_COMBO3R,
	E_ANI_COMBO4,
	E_ANI_COMBO4R,
	E_ANI_COMBO5,
	E_ANI_STRIKE,
	E_ANI_DOUBLEATTACK,
	E_ANI_DOUBLEATTACKR,
	E_ANI_SKILL,
	E_ANI_SKILLR,
	E_ANI_REACTION,
	E_ANI_REACTIONCOM,
	E_ANI_END,
};

enum E_ANIMATION_BOSS
{
	E_BOSS_LONGMOVE_END = 5,
	E_BOSS_LONGMOVE_RUN,
	E_BOSS_LONGMOVE_LOOP,
	E_BOSS_LONGMOVE_START,
	E_BOSS_HEAVYATK_END,
	E_BOSS_HEAVYATK_LOOP,
	E_BOSS_HEAVYATK_START,
	E_BOSS_ATK2,
	E_BOSS_ATK1,
	E_BOSS_HEAVYATK2,
	E_BOSS_BACKATK,
	E_BOSS_END,
};

enum E_FONT_TYPE
{
	E_FONT_BOSS,
	E_FONT_BOSS_STATUS,
	E_FONT_DAMAGE,
	E_FONT_MONSTERDAMAGE,
	E_FONT_EVENT,
	E_FONT_EVENT2,
	E_FONT_EVENT3,
	E_FONT_END,
};

enum E_SHADER_TYPE
{
	E_SHADER_DYNAMICMESH,
	E_SHADER_EFFECT,
	E_SHADER_MAP,
	E_SHADER_TYPE_END,
};

enum E_EFFECT_TYPE
{
	E_EFFECT_FRAME,
	E_EFFECT_END,
};

enum E_EFFECT_TECHNIQUE
{
	E_TECH_NONE,
	E_TECH_NORMAL,
	E_TECH_BLUE,
	E_TECH_FRAMEMOVEX,
	E_TECH_FRAMEMOVEY,
	E_TECH_TEST,
	E_TECH_WAVE,
	E_TECH_FRAMEADD,
	E_TECH_ORCA1,
	E_TECH_ORCA1_REMOVE,
	E_TECH_ORCA2,
	E_TECH_BACKATK,
	E_TECH_MAGICARRAY,
	E_TECH_GLOBEATK,
	E_TECH_GLOBEATK2,
	E_TECH_END,
};

enum E_DYNAMICMESH_TECHNIQE
{
	E_DYNA_TECH_NORMAL,
	E_DYNA_TECH_DIE,
	E_DYNA_TECH_APPEAR,
	E_DYNA_TECH_HIT,
	E_DYNA_TECH_END,
};

enum E_EFFECT_TEXTURE
{
	E_TEXTURE1,
	E_TEXTURE2,
	E_TEXTURE3,
	E_BUMPMAP,
	E_TEXEND,
};

enum E_UITAG
{
	E_UITAG_HP = 1,
	E_UITAG_HPTEXT,
	E_UITAG_MP,
	E_UITAG_MPTEXT,
	E_UITAG_END,
};

enum E_OBJTYPE
{
	E_PLAYER,
	E_MONSTER,
	E_END,
};

enum E_SOUND
{
	E_SOUND_ATK,
	E_SOUND_SKILL1,
	E_SOUND_SKILL2,
	E_SOUND_SKILL3,
	E_SOUND_HIT,
	E_SOUND_DEATH,
	E_SOUND_RUN,
	E_SOUND_ATK2,
	E_SOUND_ATK3,
	E_SOUND_END,
};

enum E_MAP_SOUND
{
	E_MAP_SOUND_BGM,
	E_MAP_SOUND_BOSS_BGM,
	E_MAP_SOUND_END,
};