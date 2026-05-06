#include "NodeEditorWindow.h"
#include <algorithm>

namespace pine {

	NodeEditorWindow::NodeEditorWindow()
	{
		Init();
	}

	void NodeEditorWindow::Show(bool p_open, int objLoaderHeight)
	{
		ImGuiViewport* main_viewport = ImGui::GetMainViewport();
		if (main_viewport)
		{
			float remainingHeight = main_viewport->WorkSize.y - objLoaderHeight;

			ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x, main_viewport->WorkPos.y + objLoaderHeight), ImGuiCond_Always);
			_width = std::min<float>(_width, static_cast<int>(main_viewport->WorkSize.x));
			ImGui::SetNextWindowSize(ImVec2(_width, remainingHeight), ImGuiCond_Always);
		}
		_nodeEditor.Show();
		_width = _nodeEditor.GetWidth();
	}

	void NodeEditorWindow::Init()
	{
		ImNodes::CreateContext();
		_nodeEditor.NodeEditorInitialize();

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		ImNodes::StyleColorsDark();
	}
}


