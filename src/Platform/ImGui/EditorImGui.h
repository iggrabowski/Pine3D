#pragma once
#include <Editor/EditorGUI.h>
#include <imgui.h>

namespace pine {

	class EditorImGui : EditorGUI {

	public:
		EditorImGui();

		// Draws a sample/template ImGui window
		void ShowSampleWindow();
	};

}
