#pragma once

// GLFW mouse buttons
// https://www.glfw.org/docs/latest/group__buttons.html
// NOTE: For now all buttons and keycodes are put together in KeyCodes.h
// (unused)
// TODO: either delete or sort the KeyCodes.h file
enum MouseButtons : char8_t
{
	// Mouse buttons
	MB_BUTTON_LEFT = 0,
	MB_BUTTON_RIGHT = 1,
	MB_BUTTON_MIDDLE = 2,
	MB_BUTTON_4 = 3,
	MB_BUTTON_5 = 4,
	MB_BUTTON_6 = 5,
	MB_BUTTON_7 = 6,
	MB_BUTTON_LAST = 7,
};
