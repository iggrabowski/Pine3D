#pragma once
#include "Core/Application.h"
//#include "Platform/OpenGL/OpenGLRenderer.h"

#include <iostream>

int main(int argc, char** argv)
{
	/* INITIATE THE APPLICATION */
	Pine::Init();

	/* ADD OBJECTS TO THE SCENE */
	Pine::scene->CreatePlane(20.0, 20.0, Pine::Vec3(0.0, -5.0, 0.0));
	Pine::scene->CreateCube(2.0, 2.0, 2.0, Pine::Vec3(0.0, 0.0, 0.0));

	//MAIN LOOP
	while (Pine::window->GetIsActive()) {
		Pine::UpdateFrame();
	}

	return 0;
}
