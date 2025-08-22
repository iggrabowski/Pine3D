#pragma once
#include "Platform/OpenGL/GLFWWindow.h"
#include "Core/Application.h"
#include "Utils/Logger.h"


namespace pine {

static void glfw_error_callback(int error, const char* description)
{
    fprintf(stderr, "GLFW Error %d: %s\n", error, description);
}

int GlfwWindow::KeyCodeToGlfw(KeyCode code)
{
    using KC = KeyCode;
    switch (code)
    {
        // Gamepad
        case KC::GAMEPAD_BUTTON_A: return GLFW_GAMEPAD_BUTTON_A;
        case KC::GAMEPAD_BUTTON_B: return GLFW_GAMEPAD_BUTTON_B;
        case KC::GAMEPAD_BUTTON_X: return GLFW_GAMEPAD_BUTTON_X;
        case KC::GAMEPAD_BUTTON_Y: return GLFW_GAMEPAD_BUTTON_Y;
        case KC::GAMEPAD_BUTTON_LEFT_BUMPER: return GLFW_GAMEPAD_BUTTON_LEFT_BUMPER;
        case KC::GAMEPAD_BUTTON_RIGHT_BUMPER: return GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER;
        case KC::GAMEPAD_BUTTON_BACK: return GLFW_GAMEPAD_BUTTON_BACK;
        case KC::GAMEPAD_BUTTON_START: return GLFW_GAMEPAD_BUTTON_START;
        case KC::GAMEPAD_BUTTON_GUIDE: return GLFW_GAMEPAD_BUTTON_GUIDE;
        case KC::GAMEPAD_BUTTON_LEFT_THUMB: return GLFW_GAMEPAD_BUTTON_LEFT_THUMB;
        case KC::GAMEPAD_BUTTON_RIGHT_THUMB: return GLFW_GAMEPAD_BUTTON_RIGHT_THUMB;
        case KC::GAMEPAD_BUTTON_DPAD_UP: return GLFW_GAMEPAD_BUTTON_DPAD_UP;
        case KC::GAMEPAD_BUTTON_DPAD_RIGHT: return GLFW_GAMEPAD_BUTTON_DPAD_RIGHT;
        case KC::GAMEPAD_BUTTON_DPAD_DOWN: return GLFW_GAMEPAD_BUTTON_DPAD_DOWN;
        case KC::GAMEPAD_BUTTON_DPAD_LEFT: return GLFW_GAMEPAD_BUTTON_DPAD_LEFT;

        // Mouse
        case KC::MB_BUTTON_LEFT: return GLFW_MOUSE_BUTTON_LEFT;
        case KC::MB_BUTTON_RIGHT: return GLFW_MOUSE_BUTTON_RIGHT;
        case KC::MB_BUTTON_MIDDLE: return GLFW_MOUSE_BUTTON_MIDDLE;
        case KC::MB_BUTTON_4: return GLFW_MOUSE_BUTTON_4;
        case KC::MB_BUTTON_5: return GLFW_MOUSE_BUTTON_5;
        case KC::MB_BUTTON_6: return GLFW_MOUSE_BUTTON_6;
        case KC::MB_BUTTON_7: return GLFW_MOUSE_BUTTON_7;
        case KC::MB_BUTTON_8: return GLFW_MOUSE_BUTTON_8;

        // Keyboard (partial, add all as needed)
        case KC::SPACE: return GLFW_KEY_SPACE;
        case KC::APOSTROPHE: return GLFW_KEY_APOSTROPHE;
        case KC::COMMA: return GLFW_KEY_COMMA;
        case KC::MINUS: return GLFW_KEY_MINUS;
        case KC::PERIOD: return GLFW_KEY_PERIOD;
        case KC::SLASH: return GLFW_KEY_SLASH;
        case KC::D0: return GLFW_KEY_0;
        case KC::D1: return GLFW_KEY_1;
        case KC::D2: return GLFW_KEY_2;
        case KC::D3: return GLFW_KEY_3;
        case KC::D4: return GLFW_KEY_4;
        case KC::D5: return GLFW_KEY_5;
        case KC::D6: return GLFW_KEY_6;
        case KC::D7: return GLFW_KEY_7;
        case KC::D8: return GLFW_KEY_8;
        case KC::D9: return GLFW_KEY_9;
        case KC::SEMICOLON: return GLFW_KEY_SEMICOLON;
        case KC::EQUAL: return GLFW_KEY_EQUAL;
        case KC::A: return GLFW_KEY_A;
        case KC::B: return GLFW_KEY_B;
        case KC::C: return GLFW_KEY_C;
        case KC::D: return GLFW_KEY_D;
        case KC::E: return GLFW_KEY_E;
        case KC::F: return GLFW_KEY_F;
        case KC::G: return GLFW_KEY_G;
        case KC::H: return GLFW_KEY_H;
        case KC::I: return GLFW_KEY_I;
        case KC::J: return GLFW_KEY_J;
        case KC::K: return GLFW_KEY_K;
        case KC::L: return GLFW_KEY_L;
        case KC::M: return GLFW_KEY_M;
        case KC::N: return GLFW_KEY_N;
        case KC::O: return GLFW_KEY_O;
        case KC::P: return GLFW_KEY_P;
        case KC::Q: return GLFW_KEY_Q;
        case KC::R: return GLFW_KEY_R;
        case KC::S: return GLFW_KEY_S;
        case KC::T: return GLFW_KEY_T;
        case KC::U: return GLFW_KEY_U;
        case KC::V: return GLFW_KEY_V;
        case KC::W: return GLFW_KEY_W;
        case KC::X: return GLFW_KEY_X;
        case KC::Y: return GLFW_KEY_Y;
        case KC::Z: return GLFW_KEY_Z;
        case KC::LEFT_BRACKET: return GLFW_KEY_LEFT_BRACKET;
        case KC::BACKSLASH: return GLFW_KEY_BACKSLASH;
        case KC::RIGHT_BRACKET: return GLFW_KEY_RIGHT_BRACKET;
        case KC::GRAVE_ACCENT: return GLFW_KEY_GRAVE_ACCENT;
        case KC::WORLD1: return GLFW_KEY_WORLD_1;
        case KC::WORLD2: return GLFW_KEY_WORLD_2;
        case KC::ESCAPE: return GLFW_KEY_ESCAPE;
        case KC::ENTER: return GLFW_KEY_ENTER;
        case KC::TAB: return GLFW_KEY_TAB;
        case KC::BACKSPACE: return GLFW_KEY_BACKSPACE;
        case KC::INSERT: return GLFW_KEY_INSERT;
        case KC::DELETE_KEY: return GLFW_KEY_DELETE;
        case KC::RIGHT: return GLFW_KEY_RIGHT;
        case KC::LEFT: return GLFW_KEY_LEFT;
        case KC::DOWN: return GLFW_KEY_DOWN;
        case KC::UP: return GLFW_KEY_UP;
        case KC::PAGE_UP: return GLFW_KEY_PAGE_UP;
        case KC::PAGE_DOWN: return GLFW_KEY_PAGE_DOWN;
        case KC::HOME: return GLFW_KEY_HOME;
        case KC::END: return GLFW_KEY_END;
        case KC::CAPS_LOCK: return GLFW_KEY_CAPS_LOCK;
        case KC::SCROLL_LOCK: return GLFW_KEY_SCROLL_LOCK;
        case KC::NUM_LOCK: return GLFW_KEY_NUM_LOCK;
        case KC::PRINT_SCREEN: return GLFW_KEY_PRINT_SCREEN;
        case KC::PAUSE: return GLFW_KEY_PAUSE;
        case KC::F1: return GLFW_KEY_F1;
        case KC::F2: return GLFW_KEY_F2;
        case KC::F3: return GLFW_KEY_F3;
        case KC::F4: return GLFW_KEY_F4;
        case KC::F5: return GLFW_KEY_F5;
        case KC::F6: return GLFW_KEY_F6;
        case KC::F7: return GLFW_KEY_F7;
        case KC::F8: return GLFW_KEY_F8;
        case KC::F9: return GLFW_KEY_F9;
        case KC::F10: return GLFW_KEY_F10;
        case KC::F11: return GLFW_KEY_F11;
        case KC::F12: return GLFW_KEY_F12;
        case KC::F13: return GLFW_KEY_F13;
        case KC::F14: return GLFW_KEY_F14;
        case KC::F15: return GLFW_KEY_F15;
        case KC::F16: return GLFW_KEY_F16;
        case KC::F17: return GLFW_KEY_F17;
        case KC::F18: return GLFW_KEY_F18;
        case KC::F19: return GLFW_KEY_F19;
        case KC::F20: return GLFW_KEY_F20;
        case KC::F21: return GLFW_KEY_F21;
        case KC::F22: return GLFW_KEY_F22;
        case KC::F23: return GLFW_KEY_F23;
        case KC::F24: return GLFW_KEY_F24;
        case KC::F25: return GLFW_KEY_F25;
        case KC::KP0: return GLFW_KEY_KP_0;
        case KC::KP1: return GLFW_KEY_KP_1;
        case KC::KP2: return GLFW_KEY_KP_2;
        case KC::KP3: return GLFW_KEY_KP_3;
        case KC::KP4: return GLFW_KEY_KP_4;
        case KC::KP5: return GLFW_KEY_KP_5;
        case KC::KP6: return GLFW_KEY_KP_6;
        case KC::KP7: return GLFW_KEY_KP_7;
        case KC::KP8: return GLFW_KEY_KP_8;
        case KC::KP9: return GLFW_KEY_KP_9;
        case KC::KP_DECIMAL: return GLFW_KEY_KP_DECIMAL;
        case KC::KP_DIVIDE: return GLFW_KEY_KP_DIVIDE;
        case KC::KP_MULTIPLY: return GLFW_KEY_KP_MULTIPLY;
        case KC::KP_SUBTRACT: return GLFW_KEY_KP_SUBTRACT;
        case KC::KP_ADD: return GLFW_KEY_KP_ADD;
        case KC::KP_ENTER: return GLFW_KEY_KP_ENTER;
        case KC::KP_EQUAL: return GLFW_KEY_KP_EQUAL;
        case KC::LEFT_SHIFT: return GLFW_KEY_LEFT_SHIFT;
        case KC::LEFT_CONTROL: return GLFW_KEY_LEFT_CONTROL;
        case KC::LEFT_ALT: return GLFW_KEY_LEFT_ALT;
        case KC::LEFT_SUPER: return GLFW_KEY_LEFT_SUPER;
        case KC::RIGHT_SHIFT: return GLFW_KEY_RIGHT_SHIFT;
        case KC::RIGHT_CONTROL: return GLFW_KEY_RIGHT_CONTROL;
        case KC::RIGHT_ALT: return GLFW_KEY_RIGHT_ALT;
        case KC::RIGHT_SUPER: return GLFW_KEY_RIGHT_SUPER;
        case KC::MENU: return GLFW_KEY_MENU;
        default:
			return -1; // Not found
    }
}

// Returns pine::KeyCode from a GLFW key, mouse, or gamepad code.
KeyCode GlfwWindow::GlfwToKeyCode(int glfwCode, InputDeviceType deviceType)
{
    // Keyboard keys
    switch (deviceType) {
        case InputDeviceType::KEYBOARD:
            switch (glfwCode)
            {
            case GLFW_KEY_SPACE: return KeyCode::SPACE;
            case GLFW_KEY_APOSTROPHE: return KeyCode::APOSTROPHE;
            case GLFW_KEY_COMMA: return KeyCode::COMMA;
            case GLFW_KEY_MINUS: return KeyCode::MINUS;
            case GLFW_KEY_PERIOD: return KeyCode::PERIOD;
            case GLFW_KEY_SLASH: return KeyCode::SLASH;
            case GLFW_KEY_0: return KeyCode::D0;
            case GLFW_KEY_1: return KeyCode::D1;
            case GLFW_KEY_2: return KeyCode::D2;
            case GLFW_KEY_3: return KeyCode::D3;
            case GLFW_KEY_4: return KeyCode::D4;
            case GLFW_KEY_5: return KeyCode::D5;
            case GLFW_KEY_6: return KeyCode::D6;
            case GLFW_KEY_7: return KeyCode::D7;
            case GLFW_KEY_8: return KeyCode::D8;
            case GLFW_KEY_9: return KeyCode::D9;
            case GLFW_KEY_SEMICOLON: return KeyCode::SEMICOLON;
            case GLFW_KEY_EQUAL: return KeyCode::EQUAL;
            case GLFW_KEY_A: return KeyCode::A;
            case GLFW_KEY_B: return KeyCode::B;
            case GLFW_KEY_C: return KeyCode::C;
            case GLFW_KEY_D: return KeyCode::D;
            case GLFW_KEY_E: return KeyCode::E;
            case GLFW_KEY_F: return KeyCode::F;
            case GLFW_KEY_G: return KeyCode::G;
            case GLFW_KEY_H: return KeyCode::H;
            case GLFW_KEY_I: return KeyCode::I;
            case GLFW_KEY_J: return KeyCode::J;
            case GLFW_KEY_K: return KeyCode::K;
            case GLFW_KEY_L: return KeyCode::L;
            case GLFW_KEY_M: return KeyCode::M;
            case GLFW_KEY_N: return KeyCode::N;
            case GLFW_KEY_O: return KeyCode::O;
            case GLFW_KEY_P: return KeyCode::P;
            case GLFW_KEY_Q: return KeyCode::Q;
            case GLFW_KEY_R: return KeyCode::R;
            case GLFW_KEY_S: return KeyCode::S;
            case GLFW_KEY_T: return KeyCode::T;
            case GLFW_KEY_U: return KeyCode::U;
            case GLFW_KEY_V: return KeyCode::V;
            case GLFW_KEY_W: return KeyCode::W;
            case GLFW_KEY_X: return KeyCode::X;
            case GLFW_KEY_Y: return KeyCode::Y;
            case GLFW_KEY_Z: return KeyCode::Z;
            case GLFW_KEY_LEFT_BRACKET: return KeyCode::LEFT_BRACKET;
            case GLFW_KEY_BACKSLASH: return KeyCode::BACKSLASH;
            case GLFW_KEY_RIGHT_BRACKET: return KeyCode::RIGHT_BRACKET;
            case GLFW_KEY_GRAVE_ACCENT: return KeyCode::GRAVE_ACCENT;
            case GLFW_KEY_WORLD_1: return KeyCode::WORLD1;
            case GLFW_KEY_WORLD_2: return KeyCode::WORLD2;
            case GLFW_KEY_ESCAPE: return KeyCode::ESCAPE;
            case GLFW_KEY_ENTER: return KeyCode::ENTER;
            case GLFW_KEY_TAB: return KeyCode::TAB;
            case GLFW_KEY_BACKSPACE: return KeyCode::BACKSPACE;
            case GLFW_KEY_INSERT: return KeyCode::INSERT;
            case GLFW_KEY_DELETE: return KeyCode::DELETE_KEY;
            case GLFW_KEY_RIGHT: return KeyCode::RIGHT;
            case GLFW_KEY_LEFT: return KeyCode::LEFT;
            case GLFW_KEY_DOWN: return KeyCode::DOWN;
            case GLFW_KEY_UP: return KeyCode::UP;
            case GLFW_KEY_PAGE_UP: return KeyCode::PAGE_UP;
            case GLFW_KEY_PAGE_DOWN: return KeyCode::PAGE_DOWN;
            case GLFW_KEY_HOME: return KeyCode::HOME;
            case GLFW_KEY_END: return KeyCode::END;
            case GLFW_KEY_CAPS_LOCK: return KeyCode::CAPS_LOCK;
            case GLFW_KEY_SCROLL_LOCK: return KeyCode::SCROLL_LOCK;
            case GLFW_KEY_NUM_LOCK: return KeyCode::NUM_LOCK;
            case GLFW_KEY_PRINT_SCREEN: return KeyCode::PRINT_SCREEN;
            case GLFW_KEY_PAUSE: return KeyCode::PAUSE;
            case GLFW_KEY_F1: return KeyCode::F1;
            case GLFW_KEY_F2: return KeyCode::F2;
            case GLFW_KEY_F3: return KeyCode::F3;
            case GLFW_KEY_F4: return KeyCode::F4;
            case GLFW_KEY_F5: return KeyCode::F5;
            case GLFW_KEY_F6: return KeyCode::F6;
            case GLFW_KEY_F7: return KeyCode::F7;
            case GLFW_KEY_F8: return KeyCode::F8;
            case GLFW_KEY_F9: return KeyCode::F9;
            case GLFW_KEY_F10: return KeyCode::F10;
            case GLFW_KEY_F11: return KeyCode::F11;
            case GLFW_KEY_F12: return KeyCode::F12;
            case GLFW_KEY_F13: return KeyCode::F13;
            case GLFW_KEY_F14: return KeyCode::F14;
            case GLFW_KEY_F15: return KeyCode::F15;
            case GLFW_KEY_F16: return KeyCode::F16;
            case GLFW_KEY_F17: return KeyCode::F17;
            case GLFW_KEY_F18: return KeyCode::F18;
            case GLFW_KEY_F19: return KeyCode::F19;
            case GLFW_KEY_F20: return KeyCode::F20;
            case GLFW_KEY_F21: return KeyCode::F21;
            case GLFW_KEY_F22: return KeyCode::F22;
            case GLFW_KEY_F23: return KeyCode::F23;
            case GLFW_KEY_F24: return KeyCode::F24;
            case GLFW_KEY_F25: return KeyCode::F25;
            case GLFW_KEY_KP_0: return KeyCode::KP0;
            case GLFW_KEY_KP_1: return KeyCode::KP1;
            case GLFW_KEY_KP_2: return KeyCode::KP2;
            case GLFW_KEY_KP_3: return KeyCode::KP3;
            case GLFW_KEY_KP_4: return KeyCode::KP4;
            case GLFW_KEY_KP_5: return KeyCode::KP5;
            case GLFW_KEY_KP_6: return KeyCode::KP6;
            case GLFW_KEY_KP_7: return KeyCode::KP7;
            case GLFW_KEY_KP_8: return KeyCode::KP8;
            case GLFW_KEY_KP_9: return KeyCode::KP9;
            case GLFW_KEY_KP_DECIMAL: return KeyCode::KP_DECIMAL;
            case GLFW_KEY_KP_DIVIDE: return KeyCode::KP_DIVIDE;
            case GLFW_KEY_KP_MULTIPLY: return KeyCode::KP_MULTIPLY;
            case GLFW_KEY_KP_SUBTRACT: return KeyCode::KP_SUBTRACT;
            case GLFW_KEY_KP_ADD: return KeyCode::KP_ADD;
            case GLFW_KEY_KP_ENTER: return KeyCode::KP_ENTER;
            case GLFW_KEY_KP_EQUAL: return KeyCode::KP_EQUAL;
            case GLFW_KEY_LEFT_SHIFT: return KeyCode::LEFT_SHIFT;
            case GLFW_KEY_LEFT_CONTROL: return KeyCode::LEFT_CONTROL;
            case GLFW_KEY_LEFT_ALT: return KeyCode::LEFT_ALT;
            case GLFW_KEY_LEFT_SUPER: return KeyCode::LEFT_SUPER;
            case GLFW_KEY_RIGHT_SHIFT: return KeyCode::RIGHT_SHIFT;
            case GLFW_KEY_RIGHT_CONTROL: return KeyCode::RIGHT_CONTROL;
            case GLFW_KEY_RIGHT_ALT: return KeyCode::RIGHT_ALT;
            case GLFW_KEY_RIGHT_SUPER: return KeyCode::RIGHT_SUPER;
            case GLFW_KEY_MENU: return KeyCode::MENU;
            }
            break;
        // Mouse buttons
        case InputDeviceType::MOUSE:
            switch (glfwCode)
            {
            // Mouse buttons
                case GLFW_MOUSE_BUTTON_LEFT: return KeyCode::MB_BUTTON_LEFT;
                case GLFW_MOUSE_BUTTON_RIGHT: return KeyCode::MB_BUTTON_RIGHT;
                case GLFW_MOUSE_BUTTON_MIDDLE: return KeyCode::MB_BUTTON_MIDDLE;
                case GLFW_MOUSE_BUTTON_4: return KeyCode::MB_BUTTON_4;
                case GLFW_MOUSE_BUTTON_5: return KeyCode::MB_BUTTON_5;
                case GLFW_MOUSE_BUTTON_6: return KeyCode::MB_BUTTON_6;
                case GLFW_MOUSE_BUTTON_7: return KeyCode::MB_BUTTON_7;
                case GLFW_MOUSE_BUTTON_8: return KeyCode::MB_BUTTON_8;
            }
            break;
        // Gamepad buttons
        case InputDeviceType::GAMEPAD:
            switch (glfwCode)
            {
            // Gamepad buttons
				case GLFW_GAMEPAD_BUTTON_A: return KeyCode::GAMEPAD_BUTTON_A;
                case GLFW_GAMEPAD_BUTTON_B: return KeyCode::GAMEPAD_BUTTON_B;
                case GLFW_GAMEPAD_BUTTON_X: return KeyCode::GAMEPAD_BUTTON_X;
                case GLFW_GAMEPAD_BUTTON_Y: return KeyCode::GAMEPAD_BUTTON_Y;
                case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER: return KeyCode::GAMEPAD_BUTTON_LEFT_BUMPER;
                case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER: return KeyCode::GAMEPAD_BUTTON_RIGHT_BUMPER;
                case GLFW_GAMEPAD_BUTTON_BACK: return KeyCode::GAMEPAD_BUTTON_BACK;
                case GLFW_GAMEPAD_BUTTON_START: return KeyCode::GAMEPAD_BUTTON_START;
                case GLFW_GAMEPAD_BUTTON_GUIDE: return KeyCode::GAMEPAD_BUTTON_GUIDE;
                case GLFW_GAMEPAD_BUTTON_LEFT_THUMB: return KeyCode::GAMEPAD_BUTTON_LEFT_THUMB;
                case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB: return KeyCode::GAMEPAD_BUTTON_RIGHT_THUMB;
                case GLFW_GAMEPAD_BUTTON_DPAD_UP: return KeyCode::GAMEPAD_BUTTON_DPAD_UP;
                case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT: return KeyCode::GAMEPAD_BUTTON_DPAD_RIGHT;
                case GLFW_GAMEPAD_BUTTON_DPAD_DOWN: return KeyCode::GAMEPAD_BUTTON_DPAD_DOWN;
                case GLFW_GAMEPAD_BUTTON_DPAD_LEFT: return KeyCode::GAMEPAD_BUTTON_DPAD_LEFT;
            }
            break;
        default:
            return static_cast<KeyCode>(-1); // Invalid device type
	}
    switch (glfwCode) {
    

    // Gamepad buttons
        case GLFW_GAMEPAD_BUTTON_A: return KeyCode::GAMEPAD_BUTTON_A;
        case GLFW_GAMEPAD_BUTTON_B: return KeyCode::GAMEPAD_BUTTON_B;
        case GLFW_GAMEPAD_BUTTON_X: return KeyCode::GAMEPAD_BUTTON_X;
        case GLFW_GAMEPAD_BUTTON_Y: return KeyCode::GAMEPAD_BUTTON_Y;
        case GLFW_GAMEPAD_BUTTON_LEFT_BUMPER: return KeyCode::GAMEPAD_BUTTON_LEFT_BUMPER;
        case GLFW_GAMEPAD_BUTTON_RIGHT_BUMPER: return KeyCode::GAMEPAD_BUTTON_RIGHT_BUMPER;
        case GLFW_GAMEPAD_BUTTON_BACK: return KeyCode::GAMEPAD_BUTTON_BACK;
        case GLFW_GAMEPAD_BUTTON_START: return KeyCode::GAMEPAD_BUTTON_START;
        case GLFW_GAMEPAD_BUTTON_GUIDE: return KeyCode::GAMEPAD_BUTTON_GUIDE;
        case GLFW_GAMEPAD_BUTTON_LEFT_THUMB: return KeyCode::GAMEPAD_BUTTON_LEFT_THUMB;
        case GLFW_GAMEPAD_BUTTON_RIGHT_THUMB: return KeyCode::GAMEPAD_BUTTON_RIGHT_THUMB;
        case GLFW_GAMEPAD_BUTTON_DPAD_UP: return KeyCode::GAMEPAD_BUTTON_DPAD_UP;
        case GLFW_GAMEPAD_BUTTON_DPAD_RIGHT: return KeyCode::GAMEPAD_BUTTON_DPAD_RIGHT;
        case GLFW_GAMEPAD_BUTTON_DPAD_DOWN: return KeyCode::GAMEPAD_BUTTON_DPAD_DOWN;
        case GLFW_GAMEPAD_BUTTON_DPAD_LEFT: return KeyCode::GAMEPAD_BUTTON_DPAD_LEFT;
    }

    // Not found
    return static_cast<KeyCode>(-1);
}

GlfwWindow::GlfwWindow()
{
    _settings = WindowSettings();
    _lastMousePosition = { 0, 0 };
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    _window = glfwCreateWindow(
        _settings.width,
        _settings.height,
        _settings.title,
        nullptr,
        nullptr
    );

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    glfwMakeContextCurrent(_window);
    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);;

	// Enable vsync
    glfwSwapInterval(1);
}

GlfwWindow::GlfwWindow(const WindowSettings& windowSettings)
{
	_settings = windowSettings;
    _lastMousePosition = { 0, 0 };
    glfwSetErrorCallback(glfw_error_callback);
    glfwInit();

	// Decide GL+GLSL versions
#if defined(IMGUI_IMPL_OPENGL_ES2)
    // GL ES 2.0 + GLSL 100
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    // GL 3.2 + GLSL 150
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // 3.0+ only
#endif

    _window = glfwCreateWindow(
        _settings.width,
        _settings.height,
        _settings.title,
        nullptr,
        nullptr
    );

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsLight();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(_window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    
    glfwMakeContextCurrent(_window);

	// Enable vsync
    glfwSwapInterval(1);
}

void GlfwWindow::Startup()
{
	// Starting up the GLFW window
	Logger::Instance().Info("GLFW Window : starting window...");

	// assign input_handler as window user pointer
	//glfwSetWindowUserPointer(_window, &Application::input_handler);

	// set input callbacks
	// set keyboard callbacks
	glfwSetKeyCallback(_window, [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		// Call ImGui's key callback
		ImGui_ImplGlfw_KeyCallback(window, key, scancode, action, mods);

		float value = 0.0f;
		if (action == GLFW_PRESS) {
			value = 1.0f; // key pressed
		} else if (action == GLFW_RELEASE) {
			value = 0.0f; // key released
		} else if (action == GLFW_REPEAT) {
			value = 1.0f; // key held down
		}
		Application::input_handler->UpdateKeyboardState(0, GlfwToKeyCode(key, InputDeviceType::KEYBOARD), {
			.value = value
		}); 
	});

	// set mouse callbacks
	glfwSetMouseButtonCallback(_window, [](GLFWwindow* window, int button, int action, int mods) {

		// Call ImGui's mouse button callback
        ImGui_ImplGlfw_MouseButtonCallback(window, button, action, mods);

        float value = 0.0f;
		if (action == GLFW_PRESS) {
			value = 1.0f; // key pressed
		} else if (action == GLFW_RELEASE) {
			value = 0.0f; // key released
		}
		Application::input_handler->UpdateMouseState(0, GlfwToKeyCode(button, InputDeviceType::MOUSE), {
			// TODO: does mouse raise GLFW_REPEAT on hold?
			.value = value
		}); 
	});

    glfwSetCursorPosCallback(_window, [](GLFWwindow* window, double xpos, double ypos){
        // Call ImGui's mouse position callback
        ImGui_ImplGlfw_CursorPosCallback(window, xpos, ypos);

        // Update the mouse position in the input handler
		// Note: xpos and ypos are in screen coordinates, not normalized device coordinates
		Application::input_handler->UpdateMousePosition(0 , static_cast<float>(xpos), static_cast<float>(ypos));
    });

	// TODO:
	// set mouse position callback
	// set gamepad callbacks
	
	// Register the keyboard as an input device
	const auto default_keyboard = std::make_shared<InputDevice>();
	default_keyboard->index = 0;
	default_keyboard->type = InputDeviceType::KEYBOARD;
	default_keyboard->states = {};
	default_keyboard->state_func = []
	{
		return Application::input_handler->GetKeyboardState();
	};
	Application::input_handler->RegisterDevice(default_keyboard);

	
	const auto default_mouse = std::make_shared<InputDevice>();
	default_mouse->index = 1;
	default_mouse->type = InputDeviceType::MOUSE;
	default_mouse->states = {};

	//NOTE: mouse button codes are kept with the keys in the KeyCodes.h
	default_mouse->state_func = []
	{
		return Application::input_handler->GetMouseState();
	};
	Application::input_handler->RegisterDevice(default_mouse);

	Logger::Instance().Success("GLFW Window : ...startup complete.");
}

void GlfwWindow::SetCursorDisabled(const bool hidden) 
{
	if (hidden && !_cursorDisabled)
	{
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        if (glfwRawMouseMotionSupported())
        {
            Logger::Instance().Info("GLFW Window : raw mouse motion supported.");
            glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        }
        else
			Logger::Instance().Warning("GLFW Window : raw mouse motion not supported.");
		_cursorDisabled = true;
	}
	else if (!hidden && _cursorDisabled)
	{
		glfwSetInputMode(_window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		if (glfwRawMouseMotionSupported())
			glfwSetInputMode(_window, GLFW_RAW_MOUSE_MOTION, GLFW_FALSE);
        _cursorDisabled = false;
	}
}

GlfwWindow::~GlfwWindow()
{
	glfwTerminate();
	//delete m_Window;
}

void GlfwWindow::OnUpdate()
{
	glfwPollEvents();

    // ImGui frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    // 1. Show the big demo window (Most of the sample code is in ImGui::ShowDemoWindow()! You can browse its code to learn more about Dear ImGui!).
        if (_show_demo_window)
            ImGui::ShowDemoWindow(&_show_demo_window);

  //  // 2. Show a simple window that we create ourselves. We use a Begin/End pair to create a named window.
  //  {
  //      static float f = 0.0f;
  //      static int counter = 0;

  //      ImGui::Begin("Hello, world!");                          // Create a window called "Hello, world!" and append into it.

  //      ImGui::Text("This is some useful text.");               // Display some text (you can use a format strings too)
  //      ImGui::Checkbox("Demo Window", &_show_demo_window);      // Edit bools storing our window open/close state
  //      ImGui::Checkbox("Another Window", &_show_another_window);

  //      ImGui::SliderFloat("float", &f, 0.0f, 1.0f);            // Edit 1 float using a slider from 0.0f to 1.0f
  //      ImGui::ColorEdit3("clear color", (float*)&_clear_color); // Edit 3 floats representing a 

  //      if (ImGui::Button("Button"))                            // Buttons return true when clicked (most widgets return true when edited/activated)
  //          counter++;
  //      ImGui::SameLine();
  //      ImGui::Text("counter = %d", counter);

		//ImGuiIO& io = ImGui::GetIO();
  //      ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / io.Framerate, io.Framerate);
  //      ImGui::End();
  //  }

  //  // 3. Show another simple window.
  //  if (_show_another_window)
  //  {
  //      ImGui::Begin("Another Window", &_show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
  //      ImGui::Text("Hello from another window!");
  //      if (ImGui::Button("Close Me"))
  //          _show_another_window = false;
  //      ImGui::End();
  //  }

    // Rendering
    ImGui::Render();
       ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	// Swap buffers
	glfwSwapBuffers(_window);
}

GLFWwindow* GlfwWindow::GetWindow() const
{
	return _window;
}

glm::ivec2 GlfwWindow::GetMousePosition()
{
	double x_pos, y_pos;
	glfwGetCursorPos(_window, &x_pos, &y_pos);

	// TODO: check if the values are correct
	glm::ivec2 pos(x_pos, y_pos);
	return pos;
}

glm::ivec2 GlfwWindow::GetSize()
{
	return glm::ivec2(_settings.width, _settings.height);
}

bool GlfwWindow::IsOpen()
{
	return !glfwWindowShouldClose(_window);
}

/*void GLFWWindow::Sleep(float seconds)
{
	sf::sleep(sf::seconds(seconds));
}*/

}