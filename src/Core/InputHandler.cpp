#pragma once
#include "Core/InputHandler.h"
#include "Core/Application.h"

namespace Pine {

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
        if (::GetKeyboardState(_keyStates))
        {
            for (unsigned int i = 0; i < 256; i++)
            {
                if (_keyStates[i] & 0x80) // key down
                { 

                }
                else // key down
                { 

                }
            }
            ::memcpy(_prevKeyStates, _keyStates, sizeof(unsigned char)*256);
        }
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

    void InputHandler::MoveInDirection(glm::vec3 direction)
    {
        Camera& camera = renderer->GetRenderCamera();
        glm::vec3 pos = camera.GetPos();

        camera.SetPos(pos + direction * _moveSpeed);
    }

}