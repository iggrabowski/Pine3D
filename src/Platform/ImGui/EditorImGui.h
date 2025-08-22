#pragma once
#include <Editor/EditorGUI.h>

namespace pine {

	class EditorImGui : public EditorGUI {

	public:
		EditorImGui();
		void Startup() override;

		// Draws a sample/template ImGui window
	private:
		void ShowSampleWindow();
	};

}
