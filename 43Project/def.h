#pragma once


#define SINGLE(type) public:\
					 static type* GetInst()\
					 {\
						 static type inst;\
						 return &inst;\
					 }\
					 private:\
						type();\
						~type();

#define DT CTimeMgr::GetInst()->GetDeltaTime()

#define PI 3.1415926535f

#define DEL(p) if(nullptr != p) {delete p;}

#define IsTap(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::TAP
#define IsPressed(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::PRESSED
#define IsRelease(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::RELEASE
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define CLONE(type) virtual type* Clone() {return new type(*this);}
#define CLONE_DEACTIVATE(type) virtual type* Clone() { assert(nullptr); return nullptr;}

#define TILE_SIZE 64

enum class LEVEL_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,
	EDITOR,

	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,

	END,
};

enum class LAYER
{
	BACKGROUND,
	TILE,
	DEFAULT,
	PLAYER,
	MONSTER,
	PLAYER_PROJECTILE,
	MONSTER_PROJECTILE,
	FORCE,
	GROUNDPLATFORM,




	END = 16
};

enum class EVENT_TYPE
{
	CREATE_OBJECT, // wParam : Object Adress lPARAM : layer Type
	DELETE_OBJECT, // wParam : Object Adress
	LEVEL_CHANGE, // wParam : LEVEL_TYPE(Next Level Type)
};

enum class CAMERA_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE
};