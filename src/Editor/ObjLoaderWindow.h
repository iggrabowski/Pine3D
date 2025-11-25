#pragma once

#include <string>
#include <vector>
#include <functional>
#include <filesystem>

namespace pine {
    class ObjLoaderWindow
    {
    public:
        // Callback invoked when user selects a file and presses Load (or double-clicks)
        // Provide a handler that actually loads the .obj (e.g. via Assimp or your loader).
        std::function<void(const std::string& path)> OnLoad;

        ObjLoaderWindow() = default;
        explicit ObjLoaderWindow(const std::string& startDir);

        // Call to open the dialog (sets visible and optionally starting dir).
        void Open(const std::string& startDir = "");

        // Show the ImGui window. Pass pointer to bool to control visibility (same passed to ImGui::Begin).
        void Show(bool p_open);

        // Optional: set to true to only show .obj files (default true)
        bool FilterObjFiles = true;

    private:
        void RefreshDirectory();
        std::filesystem::path CurrentDir;
        std::vector<std::filesystem::directory_entry> Entries;
        std::string SelectedPath;
        char PathEditBuf[1024];
        bool _initialLoad = true;
    };
} //namespace