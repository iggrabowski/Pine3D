#pragma once
#include "Core/Controls.h"
#include "Core/Application.h"

namespace Pine {

    Controls::Controls()
    {
        //this->alreadyScrolled = false;
        m_ZoomPerScroll = 0.2;
        m_MoveSpeed = 0.2;
        m_directionSpeedX = 0.1;
        m_directionSpeedY = 0.1;
    }

	UniquePtr<Controls> Controls::Init()
	{
        return MakeUnique<Controls>();
	}

    void Controls::OnUpdate()
    {
        //do nothing
    }

    void Controls::Zoom(int delta)
    {
        Camera& camera = renderer->GetRenderCamera();
        Vec3 pos = camera.GetPos();
        Vec3 dir = camera.GetDirection();

        //move in camera direction
        camera.SetPos(pos + dir * m_ZoomPerScroll * (float)delta);
    }

    void Controls::ChangeDirection(int x, int y)
    {
        //Camera& camera = renderer->GetRenderCamera();
        //Vec3 dir = camera.GetDirection();
        //Vec2 deltaDir(x * m_directionSpeedX, y * m_directionSpeedY);
        //Vec3 vec3(dir.x, dir.y, dir.z);

        //vec3 = Rotate<Vec3>(vec3, deltaDir.x, camera.up);
        ////@bug when trying to rotate more than up or down camera flickers
        //vec3 = Rotate<Vec3>(vec3, deltaDir.y, Cross(dir, camera.up));
        //        
        //camera.SetDirection(vec3);
    }

    void Controls::MoveLeft()
    {
        Vec3 moveDir = -Normalize(
            Cross(renderer->GetRenderCamera().GetDirection(), renderer->GetRenderCamera().up)
        );
        MoveInDirection(moveDir);
    }

    void Controls::MoveRight()
    {
        Vec3 moveDir = Normalize(
            Cross(renderer->GetRenderCamera().GetDirection(), renderer->GetRenderCamera().up)
        );
        MoveInDirection(moveDir);
    }

    void Controls::MoveUp()
    {
        MoveInDirection(renderer->GetRenderCamera().up);
    }

    void Controls::MoveDown()
    {
        MoveInDirection(-renderer->GetRenderCamera().up);
    }

    void Controls::MoveInDirection(Vec3 direction)
    {
        Camera& camera = renderer->GetRenderCamera();
        Vec3 pos = camera.GetPos();

        camera.SetPos(pos + direction * m_MoveSpeed);
    }

}