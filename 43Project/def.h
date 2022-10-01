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

#define DT CTimeMgr::GetInst()->GetDeltaTime();

#define PI 3.1415926535f

#define DEL(p) if(nullptr != p) {delete p;}

#define IsTap(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::TAP
#define IsPressed(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::PRESSED
#define IsRelease(key) CKeyMgr::GetInst()->GetKeyState(key) == KEY_STATE::RELEASE

enum class LEVEL_TYPE
{
	START,
	STAGE_01,
	STAGE_02,
	STAGE_03,

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




	END = 16
};

enum class EVENT_TYPE
{
	CREATE_OBJECT, // wParam : Object Adress lPARAM : layer Type
	DELETE_OBJECT, // wParam : Object Adress
	LEVEL_CHANGE, // wParam : LEVEL_TYPE(Next Level Type)
};