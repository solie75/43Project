#include "pch.h"
#include "CKeyMgr.h"

int g_arrVK[(UINT)KEY::END]
=
{
	 VK_UP,
	 VK_DOWN,
	 VK_LEFT,
	 VK_RIGHT,

	 VK_SPACE,
	 VK_RETURN,
	 VK_ESCAPE,
	 VK_LMENU,
	 VK_LCONTROL,
	 VK_LSHIFT,
	 VK_TAB,

	 VK_LBUTTON,
	 VK_RBUTTON,

	 'Q',
	 'W',
	 'E',
	 'R',

	 'A',
	 'S',
	 'D',
	 'F',
};

CKeyMgr::CKeyMgr() {}
CKeyMgr::~CKeyMgr() {}


void CKeyMgr::KeyMgrInit()
{
	// 모든 키의 상태를 NONE으로 초기화
	for (int i = 0; i < (int)KEY::END; ++i)
	{
		m_vecKey.push_back(tKeyInfo{ (KEY)i, KEY_STATE::NONE });
	}
}

void CKeyMgr::KeyMgrTick()
{
	if (GetFocus())
	{
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			// 호출 시점에서 눌린 상태
			if (GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].key]) & 0x8000)
			{
				// 이전에는 눌리지 않은 경우 
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP;
					m_vecKey[i].bPrev = true;
				}
				else
				{
					// 지금도 눌려있고 또한 이전 프레임에서도 눌려있던 경우
					m_vecKey[i].state = KEY_STATE::PRESSED;
				}
			}
			// 현재 안눌려있는 경우
			else
			{
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::NONE;
				}
				else
				{
					m_vecKey[i].state = KEY_STATE::RELEASE;
					m_vecKey[i].bPrev = false;
				}
			}
		}
	}
	// 윈도우가 포커스 상태가 아닌 경우
	else
	{
		// 모든 키는 NONE이 되기 전에 RELEASE 단계를 거친다. (release 단계에서 필수적으로 수행해야 하는 코드가 있을 수 있기 때문에)
		for (size_t i = 0; i < m_vecKey.size(); ++i)
		{
			if (m_vecKey[i].state == KEY_STATE::TAP || m_vecKey[i].state == KEY_STATE::PRESSED)
			{
				m_vecKey[i].state = KEY_STATE::RELEASE;
			}
			else if (m_vecKey[i].state == KEY_STATE::RELEASE)
			{
				m_vecKey[i].state = KEY_STATE::NONE;
			}
		}
	}
}
