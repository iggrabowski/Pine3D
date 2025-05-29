#pragma once
namespace pine {
	// KeyCode
	enum KeyCode : int
	{
		// Gamepad codes
		// Note: These are not the same as GLFW gamepad button codes, but are used for input handling in Pine (for now).
		GAMEPAD_BUTTON_A = 0,
		GAMEPAD_BUTTON_B = 1,
		GAMEPAD_BUTTON_X = 2,
		GAMEPAD_BUTTON_Y = 3,
		GAMEPAD_BUTTON_LEFT_BUMPER = 4,
		GAMEPAD_BUTTON_RIGHT_BUMPER = 5,
		GAMEPAD_BUTTON_BACK = 6,
		GAMEPAD_BUTTON_START = 7,
		GAMEPAD_BUTTON_GUIDE = 8,
		GAMEPAD_BUTTON_LEFT_THUMB = 9,
		GAMEPAD_BUTTON_RIGHT_THUMB = 10,
		GAMEPAD_BUTTON_DPAD_UP = 11,
		GAMEPAD_BUTTON_DPAD_RIGHT = 12,
		GAMEPAD_BUTTON_DPAD_DOWN = 13,
		GAMEPAD_BUTTON_DPAD_LEFT = 14,
		GAMEPAD_BUTTON_LAST = 14,
		GAMEPAD_BUTTON_CROSS = 0, // Cross is the same as A on Xbox controllers
		GAMEPAD_BUTTON_CIRCLE = 1, // Circle is the same as B on Xbox controllers
		GAMEPAD_BUTTON_SQUARE = 2, // Square is the same as X on Xbox controllers
		GAMEPAD_BUTTON_TRIANGLE = 3, // Triangle is the same as Y on Xbox controllers

		// MouseButton codes
		// Note: These are not the same as GLFW mouse button codes, but are used for input handling in Pine (for now).
		MB_BUTTON_RIGHT = 1,
		MB_BUTTON_MIDDLE = 2,
		MB_BUTTON_4 = 3,
		MB_BUTTON_5 = 4,
		MB_BUTTON_6 = 5,
		MB_BUTTON_7 = 6,
		MB_BUTTON_LAST = 7,

		// Keyboard key codes
		// Note: These are not the same as GLFW key codes, but are used for input handling in Pine (for now).
		SPACE = 32,
		APOSTROPHE = 39, /* ' */
		COMMA = 44, /* , */
		MINUS = 45, /* - */
		PERIOD = 46, /* . */
		SLASH = 47, /* / */
		D0 = 48, /* 0 */
		D1 = 49, /* 1 */
		D2 = 50, /* 2 */
		D3 = 51, /* 3 */
		D4 = 52, /* 4 */
		D5 = 53, /* 5 */
		D6 = 54, /* 6 */
		D7 = 55, /* 7 */
		D8 = 56, /* 8 */
		D9 = 57, /* 9 */
		SEMICOLON = 59, /* ; */
		EQUAL = 61, /* = */
		A = 65,
		B = 66,
		C = 67,
		D = 68,
		E = 69,
		F = 70,
		G = 71,
		H = 72,
		I = 73,
		J = 74,
		K = 75,
		L = 76,
		M = 77,
		N = 78,
		O = 79,
		P = 80,
		Q = 81,
		R = 82,
		S = 83,
		T = 84,
		U = 85,
		V = 86,
		W = 87,
		X = 88,
		Y = 89,
		Z = 90,
		LEFT_BRACKET = 91, /* [ */
		BACKSLASH = 92, /* \ */
		RIGHT_BRACKET = 93, /* ] */
		GRAVE_ACCENT = 96, /* ` */
		WORLD1 = 161, /* non-US #1 */
		WORLD2 = 162, /* non-US #2 */
		ESCAPE = 256,
		ENTER = 257,
		TAB = 258,
		BACKSPACE = 259,
		INSERT = 260,
		DELETE = 261,
		RIGHT = 262,
		LEFT = 263,
		DOWN = 264,
		UP = 265,
		PAGE_UP = 266,
		PAGE_DOWN = 267,
		HOME = 268,
		END = 269,
		CAPS_LOCK = 280,
		SCROLL_LOCK = 281,
		NUM_LOCK = 282,
		PRINT_SCREEN = 283,
		PAUSE = 284,
		F1 = 290,
		F2 = 291,
		F3 = 292,
		F4 = 293,
		F5 = 294,
		F6 = 295,
		F7 = 296,
		F8 = 297,
		F9 = 298,
		F10 = 299,
		F11 = 300,
		F12 = 301,
		F13 = 302,
		F14 = 303,
		F15 = 304,
		F16 = 305,
		F17 = 306,
		F18 = 307,
		F19 = 308,
		F20 = 309,
		F21 = 310,
		F22 = 311,
		F23 = 312,
		F24 = 313,
		F25 = 314,
		KP0 = 320,
		KP1 = 321,
		KP2 = 322,
		KP3 = 323,
		KP4 = 324,
		KP5 = 325,
		KP6 = 326,
		KP7 = 327,
		KP8 = 328,
		KP9 = 329,
		KP_DECIMAL = 330,
		KP_DIVIDE = 331,
		KP_MULTIPLY = 332,
		KP_SUBTRACT = 333,
		KP_ADD = 334,
		KP_ENTER = 335,
		KP_EQUAL = 336,
		LEFT_SHIFT = 340,
		LEFT_CONTROL = 341,
		LEFT_ALT = 342,
		LEFT_SUPER = 343,
		RIGHT_SHIFT = 344,
		RIGHT_CONTROL = 345,
		RIGHT_ALT = 346,
		RIGHT_SUPER = 347,
		MENU = 348
	};

/*	enum InputDevice : uint8_t
	{
		KEYBOARD = 0,
		MOUSE = 1,
		JOYSTICK = 2,
		TOUCH = 3,
		GAMEPAD = 4
	};*/
}