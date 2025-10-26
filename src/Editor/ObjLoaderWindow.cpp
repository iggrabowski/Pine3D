#include "ObjLoaderWindow.h"
#include "imgui.h"
#include "Utils/Logger.h"
#include <algorithm>
#include <iostream>

namespace pine {

    ObjLoaderWindow::ObjLoaderWindow(const std::string& startDir)
    {
        if (!startDir.empty())
            CurrentDir = std::filesystem::path(startDir);
        else
            CurrentDir = std::filesystem::current_path();

		Logger::Instance().Info("ObjLoaderWindow: Starting directory set to " + CurrentDir.string());
        RefreshDirectory();
    }

    void ObjLoaderWindow::Open(const std::string& startDir)
    {
        if (!startDir.empty())
            CurrentDir = std::filesystem::path(startDir);

		Logger::Instance().Info("ObjLoaderWindow: Opening directory " + CurrentDir.string());
        RefreshDirectory();
    }

    void ObjLoaderWindow::RefreshDirectory()
    {
        Entries.clear();
        try
        {
            if (!std::filesystem::exists(CurrentDir))
                CurrentDir = std::filesystem::current_path();

            for (auto& entry : std::filesystem::directory_iterator(CurrentDir))
                Entries.push_back(entry);

            // Sort: directories first, then files (alphabetical)
            std::sort(Entries.begin(), Entries.end(), [](const auto& a, const auto& b) {
                if (a.is_directory() != b.is_directory()) return a.is_directory() > b.is_directory();
                return a.path().filename().string() < b.path().filename().string();
                });
        }
        catch (const std::exception& e)
        {
            // Non-fatal: show nothing if listing fails
            Entries.clear();
            Logger::Instance().Error("ObjLoaderWindow: RefreshDirectory error: " + std::string(e.what()));
        }
    }

    void ObjLoaderWindow::Show(bool p_open)
    {
        if (!p_open)
        {
            bool open = true;
            p_open = &open;
        }

        if (!ImGui::Begin("Load OBJ", &p_open, false))
        {
            ImGui::End();
            return;
        }

        // Top controls: path edit, Up, Refresh
        ImGui::PushID("ObjLoaderControls");
        ImGui::InputText("Path", PathEditBuf, IM_ARRAYSIZE(PathEditBuf));
        ImGui::SameLine();
        if (ImGui::Button("Go"))
        {
            try { CurrentDir = std::filesystem::path(PathEditBuf); RefreshDirectory(); }
            catch (...) {}
        }
        ImGui::SameLine();
        if (ImGui::Button("Up"))
        {
            if (CurrentDir.has_parent_path())
                CurrentDir = CurrentDir.parent_path();
            std::snprintf(PathEditBuf, sizeof(PathEditBuf), "%s", CurrentDir.string().c_str());
            RefreshDirectory();
        }
        ImGui::SameLine();
        if (ImGui::Button("Refresh"))
        {
            RefreshDirectory();
        }
        ImGui::PopID();

        // Filter toggle
        ImGui::Checkbox("Show only .obj", &FilterObjFiles);

        ImGui::Separator();

        // Directory / files list
        ImGui::BeginChild("FileList", ImVec2(0, -ImGui::GetFrameHeightWithSpacing() * 2));

        const float spacing = ImGui::GetStyle().ItemSpacing.y;
        for (const auto& entry : Entries)
        {
            const auto& p = entry.path();
            const std::string filename = p.filename().string();
            if (entry.is_directory())
            {
                ImGui::PushStyleColor(ImGuiCol_Text, ImVec4(0.6f, 0.9f, 1.0f, 1.0f));
                if (ImGui::Selectable((std::string("[DIR] ") + filename).c_str(), false))
                {
                    // single click navigates
                    CurrentDir = p;
                    std::snprintf(PathEditBuf, sizeof(PathEditBuf), "%s", CurrentDir.string().c_str());
                    RefreshDirectory();
                    // reset selection
                    SelectedPath.clear();
                }
                ImGui::PopStyleColor();
            }
            else
            {
                // apply .obj filter if requested
                if (FilterObjFiles)
                {
                    auto ext = p.extension().string();
                    std::transform(ext.begin(), ext.end(), ext.begin(), ::tolower);
                    if (ext != ".obj") continue;
                }

                const bool selected = (SelectedPath == p.string());
                if (ImGui::Selectable(filename.c_str(), selected))
                {
                    SelectedPath = p.string();
                }

                // double-click to load quickly
                if (ImGui::IsItemHovered() && ImGui::IsMouseDoubleClicked(0))
                {
                    SelectedPath = p.string();
                    if (OnLoad) OnLoad(SelectedPath);
                }
            }
        }

        ImGui::EndChild();

        // Bottom: selected file name + Load/Cancel
        ImGui::Separator();
        ImGui::TextUnformatted("Selected: ");
        ImGui::SameLine();
        ImGui::TextWrapped("%s", SelectedPath.empty() ? "<none>" : SelectedPath.c_str());

        ImGui::SameLine(ImGui::GetWindowWidth() - 220);
        if (ImGui::Button("Load", ImVec2(100, 0)))
        {
            if (!SelectedPath.empty() && OnLoad)
                OnLoad(SelectedPath);
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel", ImVec2(100, 0)))
        {
            p_open = false;
        }

        ImGui::End();
    }
} //namespace