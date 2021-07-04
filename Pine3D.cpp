#pragma once
#include "Core/Application.h"
//#include "Platform/OpenGL/OpenGLRenderer.h"

#include <iostream>

int main(int argc, char** argv)
{
	/* INITIATE THE APPLICATION */
	Pine::Init();

	/* ADD DEFAULT MESH RENDERER TO THE SCENE */
	Pine::MeshRenderer mr;
	//add default Mesh renderer to the scene
	Pine::sceneObjects.push_back(&mr);


	/* ADD POLYGON TO THE SCENE */
	std::vector<Pine::Vec2> vs;
	vs.push_back(Pine::Vec2(-0.5, -0.5));
	vs.push_back(Pine::Vec2(-0.5, 0.5));
	vs.push_back(Pine::Vec2(0.5, 0.5));
	vs.push_back(Pine::Vec2(0.5, -0.5));

	Pine::Polygon pl(vs);
	Pine::sceneObjects.push_back(&pl);

	//MAIN LOOP
	while (Pine::window->GetIsActive()) {
		Pine::UpdateFrame();
	}

	return 0;
}
