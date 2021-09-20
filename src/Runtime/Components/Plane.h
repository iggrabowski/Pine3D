#pragma once
#include "Runtime/Components/Mesh.h"

namespace Pine
{

    class Plane : public Mesh
    {
    public:
        Plane();
        Plane(float width, float depth);
    };

}