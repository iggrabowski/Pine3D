#pragma once
#include "Core/InputHandler.h"
#include "Core/Application.h"
//#include <stdio.h>

namespace Pine {

    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        //--------------CONTROLS--------------//
        //std::cout << "Button " << key << " pressed" << std::endl;
        for (const auto& i : inputHandler->GetListeners()) {
            if (action == GLFW_RELEASE) {
                i->OnInputAction(InputType::KEYBOARD, (KeyCode)key, KeyAction::KEY_RELEASE);
            }
            else if (action == GLFW_PRESS)
                i->OnInputAction(InputType::KEYBOARD, (KeyCode)key, KeyAction::KEY_PRESS);
            //else if (GLFW_REPEAT)
            //    i->first->OnInput(i->second, KeyAction::KEY_REPEAT);
        }
    }

    void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
        //--------------CONTROLS--------------//
        //std::cout << "Button " << key << " pressed" << std::endl;
        for (const auto& i : inputHandler->GetListeners()) {
            if (action == GLFW_RELEASE) {
                i->OnInputAction(InputType::MOUSE, (MouseButtons)button, KeyAction::KEY_RELEASE);
            }
            else if (action == GLFW_PRESS)
                i->OnInputAction(InputType::MOUSE, (MouseButtons)button, KeyAction::KEY_PRESS);
            //else if (GLFW_REPEAT)
            //    i->first->OnInput(i->second, KeyAction::KEY_REPEAT);
        }
    }

    InputHandler::InputHandler()
    {
        //this->alreadyScrolled = false;
        _zoomPerScroll = 0.2f;
        _moveSpeed = 0.2f;
        _directionSpeedX = 0.1f;
        _directionSpeedY = 0.1f;
    }

	UniquePtr<InputHandler> InputHandler::Init()
	{
        return MakeUnique<InputHandler>();
	}

    void InputHandler::OnUpdate()
    {
        if (!_initialized) {
            glfwSetKeyCallback(window->GetWindow(), KeyCallback);
            glfwSetMouseButtonCallback(window->GetWindow(), MouseButtonCallback);
            _initialized = true;
        }
        glfwPollEvents();
    }

    void InputHandler::Zoom(int delta)
    {
        Camera& camera = renderer->GetRenderCamera();
        glm::vec3 pos = camera.GetPos();
        glm::vec3 dir = camera.GetDirection();

        //move in camera direction
        camera.SetPos(pos + dir * _zoomPerScroll * (float)delta);
    }

    void InputHandler::ChangeDirection(int x, int y)
    {
        //Camera& camera = renderer->GetRenderCamera();
        //glm::vec3 dir = camera.GetDirection();
        //glm::vec2 deltaDir(x * m_directionSpeedX, y * m_directionSpeedY);
        //glm::vec3 vec3(dir.x, dir.y, dir.z);

        //vec3 = Rotate<glm::vec3>(vec3, deltaDir.x, camera.up);
        ////@bug when trying to rotate more than up or down camera flickers
        //vec3 = Rotate<glm::vec3>(vec3, deltaDir.y, Cross(dir, camera.up));
        //        
        //camera.SetDirection(vec3);
    }

    void InputHandler::AddListener(InputListener* listener)
    {
        auto i = std::find(_listeners.begin(), _listeners.end(), listener);
        if (i == _listeners.end())
            _listeners.push_back(listener);
        else {};
            // Listener already registered
    }

    void InputHandler::RemoveListener(InputListener* listener)
    {
        auto i = std::find(_listeners.begin(), _listeners.end(), listener);
        if (i != _listeners.end())
            _listeners.erase(i);
    }

    bool InputHandler::IsKeyPressed(KeyCode keyCode)
    {
        int state = glfwGetKey(window->GetWindow(), keyCode);

        if (state == GLFW_PRESS) {
            return true;
        }

        return false;
    }

    bool InputHandler::IsMouseButtonPressed(MouseButtons mouseCode)
    {
        if (glfwGetMouseButton(window->GetWindow(), GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            return true;
        }
        return false;
    }

}