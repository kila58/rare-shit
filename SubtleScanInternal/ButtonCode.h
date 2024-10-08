#ifndef __CONSOLE_BUTTONCODE_H__
#define __CONSOLE_BUTTONCODE_H__

#ifdef _MSC_VER
#pragma once
#endif

#include "Main.h"

namespace Console
{
	enum eButtonCode
	{
		KEY_NONE = 0,
		KEY_MOUSE_LEFT,
		KEY_MOUSE_RIGHT,
		KEY_INVALID,
		KEY_MOUSE_MIDDLE,
		KEY_MOUSE_4,
		KEY_MOUSE_5,
		KEY_BACKSPACE = 8,
		KEY_ENTER = 13,
		KEY_SHIFT = 16,
		KEY_CAPSTOGGLE = 20,
		KEY_ESCAPE = 27,
		KEY_SPACE = 32,
		KEY_PAGE_UP,
		KEY_PAGE_DOWN,
		KEY_END,
		KEY_POS1,
		KEY_ARROW_LEFT,
		KEY_ARROW_UP,
		KEY_ARROW_RIGHT,
		KEY_ARROW_DOWN,
		KEY_INSERT = 45,
		KEY_DELETE,
		KEY_0 = 48,
		KEY_1,
		KEY_2,
		KEY_3,
		KEY_4,
		KEY_5,
		KEY_6,
		KEY_7,
		KEY_8,
		KEY_9,
		KEY_A = 65,
		KEY_B,
		KEY_C,
		KEY_D,
		KEY_E,
		KEY_F,
		KEY_G,
		KEY_H,
		KEY_I,
		KEY_J,
		KEY_K,
		KEY_L,
		KEY_M,
		KEY_N,
		KEY_O,
		KEY_P,
		KEY_Q,
		KEY_R,
		KEY_S,
		KEY_T,
		KEY_U,
		KEY_V,
		KEY_W,
		KEY_X,
		KEY_Y,
		KEY_Z,
		KEY_RWIN,
		KEY_LWIN,
		KEY_SETTING,
		KEY_NUMPAD_1 = 97,
		KEY_NUMPAD_2,
		KEY_NUMPAD_3,
		KEY_NUMPAD_4,
		KEY_NUMPAD_5,
		KEY_NUMPAD_6,
		KEY_NUMPAD_7,
		KEY_NUMPAD_8,
		KEY_NUMPAD_9,
		KEY_NUMPAD_MULTIPLICATE,
		KEY_NUMPAD_PLUS,
		KEY_NUMPAD_MINUS = 109,
		KEY_NUMPAD_DIVIDE = 111,
		KEY_F1,
		KEY_F2,
		KEY_F3,
		KEY_F4,
		KEY_F5,
		KEY_F6,
		KEY_F7,
		KEY_F8,
		KEY_F9,
		KEY_F10,
		KEY_F11,
		KEY_F12,
		KEY_NUMPAD_NUM = 144,
		KEY_LSHIFT = 160,
		KEY_RSHIFT,
		KEY_LSTRG,
		KEY_RSTRG,
		KEY_ALT,
		KEY_ALTGR,
		KEY_MUTE = 173,
		KEY_� = 186,
		KEY_PLUS,
		KEY_COMMA,
		KEY_MINUS,
		KEY_DOT,
		KEY_RUE,
		KEY_�,
		KEY_BACKSLAH = 219,
		KEY_ROOF, // ^
		KEY_GAY, // "�" and  "`"
		KEY_�,
		KEY_MAX = 255,
	};

	typedef struct
	{
		char    m_szDefinition[12];
		char    m_szShiftDefinition[12];
		char    m_szAltDefinition[12];
	}KeyStroke_t;

	extern KeyStroke_t m_KeyStroke[KEY_MAX];

	extern bool IsKeyPressed(int eventCode);
	extern bool IsKeyDown(int eventCode);
}

#endif  