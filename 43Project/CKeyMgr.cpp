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
	// ��� Ű�� ���¸� NONE���� �ʱ�ȭ
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
			// ȣ�� �������� ���� ����
			if (GetAsyncKeyState(g_arrVK[(UINT)m_vecKey[i].key]) & 0x8000)
			{
				// �������� ������ ���� ��� 
				if (false == m_vecKey[i].bPrev)
				{
					m_vecKey[i].state = KEY_STATE::TAP;
					m_vecKey[i].bPrev = true;
				}
				else
				{
					// ���ݵ� �����ְ� ���� ���� �����ӿ����� �����ִ� ���
					m_vecKey[i].state = KEY_STATE::PRESSED;
				}
			}
			// ���� �ȴ����ִ� ���
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
	// �����찡 ��Ŀ�� ���°� �ƴ� ���
	else
	{
		// ��� Ű�� NONE�� �Ǳ� ���� RELEASE �ܰ踦 ��ģ��. (release �ܰ迡�� �ʼ������� �����ؾ� �ϴ� �ڵ尡 ���� �� �ֱ� ������)
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
