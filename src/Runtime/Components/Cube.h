#pragma once
#include "Runtime/Components/Mesh.h"

namespace Pine
{

    class Cube : public Mesh
    {
    public:
        Cube();
        Cube(float width, float height, float depth);
    };

}