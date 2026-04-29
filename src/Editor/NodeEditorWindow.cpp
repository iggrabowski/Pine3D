#include "NodeEditorWindow.h"

namespace pine {
	NodeEditorWindow::NodeEditorWindow()
	{
        Init();
	}

	void NodeEditorWindow::Show(bool p_open, int height)
	{
        ImGuiViewport* main_viewport = ImGui::GetMainViewport();
        if (main_viewport)
        {
            ImGui::SetNextWindowPos(ImVec2(main_viewport->WorkPos.x,height), ImGuiCond_Always);
            //ImGui::SetNextWindowViewport(main_viewport->ID);
        }
        NodeEditorShowColor();
	}

	void NodeEditorWindow::Init()
	{
    ImNodes::CreateContext();
    NodeEditorInitialize();

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    ImNodes::StyleColorsDark();
	}
}

