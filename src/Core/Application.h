#pragma once
//#include "Core/Window.h"
#include "Runtime/Renderer/Renderer.h"
#include "Runtime/Scene/SceneObject.h"
#include "Input/InputHandler.h"
#include "Runtime/Lighting/Light.h"
//#include "Runtime/Components/MeshRenderer.h"
//#include "Utils/Utils.h"
#include "Runtime/Components/Polygon.h"
#include "Editor/Editor.h"
#include "Utils/Logger.h"

#define SINGLE_MESH_MODE

namespace pine {

	class Application {

	public:
		Application() = default;
		static int Run();
		static void Update_Frame();
		static void Init();
		static void Startup();

		static inline std::unique_ptr<Editor> editor = nullptr;
		static inline std::unique_ptr<GlfwWindow> window = nullptr; //for now only GLFW window implementation
		static inline std::unique_ptr<Renderer> renderer = nullptr;
		static inline std::unique_ptr<InputHandler> inputHandler = nullptr;
		static inline std::vector<std::unique_ptr<SceneObject>> sceneObjects;
		static inline std::vector<Material> materials;
		static inline std::vector<Image> images;
		static inline std::vector<Texture> textures;
		static inline std::vector<Light> lights;
		static inline std::vector<std::vector<Light>> lightPresets;
		//static inline std::unique_ptr<Logger> logger = nullptr;

		// The single mesh version of the app
		static inline MeshRenderer mr;
		static inline int activeLightPresetIndex = 0;
	};

}