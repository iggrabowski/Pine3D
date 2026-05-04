#pragma once
#include "Runtime/Components/Material.h"
#include <imgui.h>
#include "Platform/imnodes/imnodes.h"
#include "graph.h"

#include "imnodes.h"
#include <imgui.h>

//#include <SDL2/SDL_timer.h>
#include <algorithm>
#include <cassert>
#include <chrono>
#include <cmath>
#include <vector>
#include <unordered_set>

// TODO: can abstract this (gettime)
//#include "GLFW/glfw3.h"
#include <Runtime/Components/Image.h>
#include <Runtime/Components/Texture.h>
#include <string>

namespace pine
{

enum class NodeType
{
    add,
    multiply,
    output,
    sine,
    time,
    value,
    image,    // added: differentiate image-node graph ids from value nodes
    material
};

struct Node
{
    NodeType type;
    float    value;

    explicit Node(const NodeType t) : type(t), value(0.f) {}

    Node(const NodeType t, const float v) : type(t), value(v) {}
};
class NodeEditor
{
public:
    NodeEditor()
        : graph_(), nodes_(), root_node_id_(-1),
          minimap_location_(ImNodesMiniMapLocation_BottomRight)
    {
    }

	void NodeEditorInitialize();
    bool GetFirstOutgoingNodeValue(int nodeId, float& outValue) const;
   
    // Adds a new image node and takes ownership of the provided texture pointer.
    // - texture: pointer to a pine::Texture already created (may be nullptr).
    //            This object will be deleted when the node is removed.
    // - path: optional file path to record on the node (informational).
    // - pos: optional screen-space position; if pos.x < 0 the current mouse position is used.
    void AddMaterialNodes(pine::Material* material, ImVec2 pos = ImVec2(-1.0f, -1.0f));
	int GetWidth() const { return _windowHeight; }

    void Show();
    

private:
    enum class UiNodeType
    {
        add,
        multiply,
        output,
        sine,
        time,
        image,
        material
    };

    struct UiNode
    {
        UiNodeType type;
        // The identifying id of the ui node. For add, multiply, sine, and time
        // this is the "operation" node id. The additional input nodes are
        // stored in the structs.
        int id;

        union
        {
            struct
            {
                int lhs, rhs;
            } add;

            struct
            {
                int lhs, rhs;
            } multiply;

            struct
            {
                int r, g, b;
            } output;

            struct
            {
                int input;
            } sine;

            struct
            {
                int input1, input2, input3, input4;
            } material;
        } ui;
        // image node data (kept outside the union)
        std::string imageTexturePath;
        pine::Texture* texture = nullptr;
		pine::Material* material = nullptr;
    };

    example::Graph<Node>            graph_;
    std::vector<UiNode>    nodes_;
    int                    root_node_id_;
    ImNodesMiniMapLocation minimap_location_;
    int                    _windowHeight;
};

} // namespace pine