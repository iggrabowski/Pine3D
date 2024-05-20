#pragma once
#include "Core/InputHandler.h"
#include "Core/Application.h"
#include <stdio.h>

namespace Pine {

    void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
        //--------------CONTROLS--------------//
        //std::cout << "Button " << key << " pressed" << std::endl;
        for (const auto& i : inputHandler->m_Listeners) {
            if (action == GLFW_RELEASE) {
                i->OnInput(InputType::Keyboard, (KeyCode)key, KeyAction::KEY_RELEASE);
            }
            else if (action == GLFW_PRESS)
                i->OnInput(InputType::Keyboard, (KeyCode)key, KeyAction::KEY_PRESS);
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

    void InputHandler::MoveLeft()
    {
        glm::vec3 moveDir = -glm::normalize(
            Cross(renderer->GetRenderCamera().GetDirection(), renderer->GetRenderCamera().up)
        );
        MoveInDirection(moveDir);
    }

    void InputHandler::MoveRight()
    {
        glm::vec3 moveDir = glm::normalize(
            Cross(renderer->GetRenderCamera().GetDirection(), renderer->GetRenderCamera().up)
        );
        MoveInDirection(moveDir);
    }

    void InputHandler::MoveUp()
    {
        MoveInDirection(renderer->GetRenderCamera().up);
    }

    void InputHandler::MoveDown()
    {
        MoveInDirection(-renderer->GetRenderCamera().up);
    }

    void InputHandler::AddListener(InputListener* listener)
    {
        auto i = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
        if (i == m_Listeners.end())
            m_Listeners.push_back(listener);
        else {};
            // Listener already registered
    }

    void InputHandler::RemoveListener(InputListener* listener)
    {
        auto i = std::find(m_Listeners.begin(), m_Listeners.end(), listener);
        if (i != m_Listeners.end())
            m_Listeners.erase(i);
    }

    void InputHandler::MoveInDirection(glm::vec3 direction)
    {
        Camera& camera = renderer->GetRenderCamera();
        glm::vec3 pos = camera.GetPos();

        camera.SetPos(pos + direction * _moveSpeed);
    }

}