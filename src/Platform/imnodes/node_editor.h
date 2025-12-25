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

// TODO: can abstract this (gettime)
//#include "GLFW/glfw3.h"
#include <Runtime/Components/Image.h>
#include <Runtime/Components/Texture.h>
#include <string>

namespace example
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
class ColorNodeEditor
{
public:
    ColorNodeEditor()
        : graph_(), nodes_(), root_node_id_(-1),
          minimap_location_(ImNodesMiniMapLocation_BottomRight)
    {
    }
    bool GetFirstOutgoingNodeValue(int nodeId, float &outValue) const
   {
        for (const auto &edge : graph_.edges())
        {
            if (edge.from == nodeId)
            {
                outValue = graph_.node(edge.to).value;
                return true;
            }
        }
        return false;
    }
    // Adds a new image node and takes ownership of the provided texture pointer.
    // - texture: pointer to a pine::Texture already created (may be nullptr).
    //            This object will be deleted when the node is removed.
    // - path: optional file path to record on the node (informational).
    // - pos: optional screen-space position; if pos.x < 0 the current mouse position is used.
    void AddMaterialNodes(pine::Material* material,  ImVec2 pos = ImVec2(-1.0f, -1.0f))
    {
		// check if there are textures in the material
		pine::Texture* pointer = nullptr;
        for (auto texture : material->m_textures)
        {
            if (texture != nullptr) pointer = texture;
        }
        if (pointer == nullptr) return;

        // depending on texture type the node will be placed accordingly, after that they all connect to a material node
        // create mat node first
        const Node value(NodeType::value, 0.f);
		const Node out(NodeType::output);
				
		UiNode ui_node;
		ui_node.type = UiNodeType::material;
		ui_node.ui.material.input1 = graph_.insert_node(value);
		ui_node.ui.material.input2 = graph_.insert_node(value);
		ui_node.ui.material.input3 = graph_.insert_node(value);
		ui_node.id = graph_.insert_node(out);
				
		graph_.insert_edge(ui_node.id, ui_node.ui.material.input1);
		graph_.insert_edge(ui_node.id, ui_node.ui.material.input2);
		graph_.insert_edge(ui_node.id, ui_node.ui.material.input3);
				
        nodes_.push_back(ui_node);
		ImNodes::SetNodeScreenSpacePos(ui_node.id, ImVec2(371,541));
		root_node_id_ = ui_node.id;
		// then create base texture node
        UiNode base_tex_node;
        base_tex_node.type = UiNodeType::image;
        base_tex_node.imageTexturePath = "";
        base_tex_node.texture = material->m_textures[pine::TEX_TYPE_BASE];
        // create graph id for image node as NodeType::image so its type is different from plain value nodes
        base_tex_node.id = graph_.insert_node(Node(NodeType::image, base_tex_node.texture->GetGLHandle()));

        nodes_.push_back(base_tex_node);
        ImNodes::SetNodeScreenSpacePos(base_tex_node.id, ImVec2(171,341));

		// then create normal texture node
        UiNode normal_tex_node;
        // use an image node type for the graph id also
        normal_tex_node.type = UiNodeType::image;
        normal_tex_node.imageTexturePath = "";
        normal_tex_node.texture = material->m_textures[pine::TEX_TYPE_NORMAL];
        normal_tex_node.id = graph_.insert_node(Node(NodeType::image,  normal_tex_node.texture->GetGLHandle()));

        nodes_.push_back(normal_tex_node);
        ImNodes::SetNodeScreenSpacePos(normal_tex_node.id, ImVec2(171,541));
		
		graph_.insert_edge( ui_node.ui.material.input1, base_tex_node.id);
		graph_.insert_edge( ui_node.ui.material.input2, normal_tex_node.id);
    }

    void show()
    {
        // Update timer context
        //current_time_seconds = glfwGetTime();

        auto flags = ImGuiWindowFlags_MenuBar;

        // The node editor window
        ImGui::Begin("color node editor", nullptr, flags);

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("Mini-map"))
            {
                const char* names[] = {
                    "Top Left",
                    "Top Right",
                    "Bottom Left",
                    "Bottom Right",
                };
                int locations[] = {
                    ImNodesMiniMapLocation_TopLeft,
                    ImNodesMiniMapLocation_TopRight,
                    ImNodesMiniMapLocation_BottomLeft,
                    ImNodesMiniMapLocation_BottomRight,
                };

                for (int i = 0; i < 4; i++)
                {
                    bool selected = minimap_location_ == locations[i];
                    if (ImGui::MenuItem(names[i], NULL, &selected))
                        minimap_location_ = locations[i];
                }
                ImGui::EndMenu();
            }

            if (ImGui::BeginMenu("Style"))
            {
                if (ImGui::MenuItem("Classic"))
                {
                    ImGui::StyleColorsClassic();
                    ImNodes::StyleColorsClassic();
                }
                if (ImGui::MenuItem("Dark"))
                {
                    ImGui::StyleColorsDark();
                    ImNodes::StyleColorsDark();
                }
                if (ImGui::MenuItem("Light"))
                {
                    ImGui::StyleColorsLight();
                    ImNodes::StyleColorsLight();
                }
                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::TextUnformatted("Edit the color of the output color window using nodes.");
        ImGui::Columns(2);
        ImGui::TextUnformatted("A -- add node");
        ImGui::TextUnformatted("X -- delete selected node or link");
        ImGui::NextColumn();
        //if (ImGui::Checkbox("emulate_three_button_mouse", &emulate_three_button_mouse))
        //{
        //    ImNodes::GetIO().EmulateThreeButtonMouse.Modifier =
        //        emulate_three_button_mouse ? &ImGui::GetIO().KeyAlt : NULL;
        //}
        ImGui::Columns(1);

        ImNodes::BeginNodeEditor();

        // Handle new nodes
        // These are driven by the user, so we place this code before rendering the nodes
        {
            const bool open_popup = ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
                                    ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(ImGuiKey_A);

            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(8.f, 8.f));
            if (!ImGui::IsAnyItemHovered() && open_popup)
            {
                ImGui::OpenPopup("add node");
            }

            if (ImGui::BeginPopup("add node"))
            {
                const ImVec2 click_pos = ImGui::GetMousePosOnOpeningCurrentPopup();

                if (ImGui::MenuItem("add"))
                {
                    const Node value(NodeType::value, 0.f);
                    const Node op(NodeType::add);

                    UiNode ui_node;
                    ui_node.type = UiNodeType::add;
                    ui_node.ui.add.lhs = graph_.insert_node(value);
                    ui_node.ui.add.rhs = graph_.insert_node(value);
                    ui_node.id = graph_.insert_node(op);

                    graph_.insert_edge(ui_node.id, ui_node.ui.add.lhs);
                    graph_.insert_edge(ui_node.id, ui_node.ui.add.rhs);

                    nodes_.push_back(ui_node);
                    ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
                }

                if (ImGui::MenuItem("multiply"))
                {
                    const Node value(NodeType::value, 0.f);
                    const Node op(NodeType::multiply);

                    UiNode ui_node;
                    ui_node.type = UiNodeType::multiply;
                    ui_node.ui.multiply.lhs = graph_.insert_node(value);
                    ui_node.ui.multiply.rhs = graph_.insert_node(value);
                    ui_node.id = graph_.insert_node(op);

                    graph_.insert_edge(ui_node.id, ui_node.ui.multiply.lhs);
                    graph_.insert_edge(ui_node.id, ui_node.ui.multiply.rhs);

                    nodes_.push_back(ui_node);
                    ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
                }

                if (ImGui::MenuItem("output") && root_node_id_ == -1)
                {
                    const Node value(NodeType::value, 0.f);
                    const Node out(NodeType::output);

                    UiNode ui_node;
                    ui_node.type = UiNodeType::output;
                    ui_node.ui.output.r = graph_.insert_node(value);
                    ui_node.ui.output.g = graph_.insert_node(value);
                    ui_node.ui.output.b = graph_.insert_node(value);
                    ui_node.id = graph_.insert_node(out);

                    graph_.insert_edge(ui_node.id, ui_node.ui.output.r);
                    graph_.insert_edge(ui_node.id, ui_node.ui.output.g);
                    graph_.insert_edge(ui_node.id, ui_node.ui.output.b);

                    nodes_.push_back(ui_node);
                    ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
                    root_node_id_ = ui_node.id;
                }

                if (ImGui::MenuItem("sine"))
                {
                    const Node value(NodeType::value, 0.f);
                    const Node op(NodeType::sine);

                    UiNode ui_node;
                    ui_node.type = UiNodeType::sine;
                    ui_node.ui.sine.input = graph_.insert_node(value);
                    ui_node.id = graph_.insert_node(op);

                    graph_.insert_edge(ui_node.id, ui_node.ui.sine.input);

                    nodes_.push_back(ui_node);
                    ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
                }

                if (ImGui::MenuItem("time"))
                {
                    UiNode ui_node;
                    ui_node.type = UiNodeType::time;
                    ui_node.id = graph_.insert_node(Node(NodeType::time));

                    nodes_.push_back(ui_node);
                    ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
                }

                if (ImGui::MenuItem("image"))
                {
                    // create a lightweight value node in the graph as an id anchor
                    UiNode ui_node;
                    ui_node.type = UiNodeType::image;
                    ui_node.imageTexturePath = "";
                    ui_node.texture = nullptr;
                    // create graph id with NodeType::image so linking logic treats output port type different from plain value nodes
                    ui_node.id = graph_.insert_node(Node(NodeType::image));

                    nodes_.push_back(ui_node);
                    ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
                }
                if (ImGui::MenuItem("material") && root_node_id_ == -1)
				{
				const Node value(NodeType::value, 0.f);
				const Node out(NodeType::output);
				
				UiNode ui_node;
				ui_node.type = UiNodeType::material;
				ui_node.ui.material.input1 = graph_.insert_node(value);
				ui_node.ui.material.input2 = graph_.insert_node(value);
				ui_node.ui.material.input3 = graph_.insert_node(value);
				ui_node.id = graph_.insert_node(out);
				
				graph_.insert_edge(ui_node.id, ui_node.ui.material.input1);
				graph_.insert_edge(ui_node.id, ui_node.ui.material.input2);
				graph_.insert_edge(ui_node.id, ui_node.ui.material.input3);
				
				nodes_.push_back(ui_node);
				ImNodes::SetNodeScreenSpacePos(ui_node.id, click_pos);
				root_node_id_ = ui_node.id;
				}
                ImGui::EndPopup();
            }
            ImGui::PopStyleVar();
        }

        for (UiNode& node : nodes_)
        {
            switch (node.type)
            {
            case UiNodeType::add:
            {
                const float node_width = 100.f;
                ImNodes::BeginNode(node.id);

                ImNodes::BeginNodeTitleBar();
                ImGui::TextUnformatted("add");
                ImNodes::EndNodeTitleBar();
                {
                    ImNodes::BeginInputAttribute(node.ui.add.lhs);
                    const float label_width = ImGui::CalcTextSize("left").x;
                    ImGui::TextUnformatted("left");
                    if (graph_.num_edges_from_node(node.ui.add.lhs) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat("##hidelabel", &graph_.node(node.ui.add.lhs).value, 0.01f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                {
                    ImNodes::BeginInputAttribute(node.ui.add.rhs);
                    const float label_width = ImGui::CalcTextSize("right").x;
                    ImGui::TextUnformatted("right");
                    if (graph_.num_edges_from_node(node.ui.add.rhs) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat("##hidelabel", &graph_.node(node.ui.add.rhs).value, 0.01f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                ImGui::Spacing();

                {
                    ImNodes::BeginOutputAttribute(node.id);
                    const float label_width = ImGui::CalcTextSize("result").x;
                    ImGui::Indent(node_width - label_width);
                    ImGui::TextUnformatted("result");
                    ImNodes::EndOutputAttribute();
                }

                ImNodes::EndNode();
            }
            break;
            case UiNodeType::multiply:
            {
                const float node_width = 100.0f;
                ImNodes::BeginNode(node.id);

                ImNodes::BeginNodeTitleBar();
                ImGui::TextUnformatted("multiply");
                ImNodes::EndNodeTitleBar();

                {
                    ImNodes::BeginInputAttribute(node.ui.multiply.lhs);
                    const float label_width = ImGui::CalcTextSize("left").x;
                    ImGui::TextUnformatted("left");
                    if (graph_.num_edges_from_node(node.ui.multiply.lhs) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat(
                            "##hidelabel", &graph_.node(node.ui.multiply.lhs).value, 0.01f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                {
                    ImNodes::BeginInputAttribute(node.ui.multiply.rhs);
                    const float label_width = ImGui::CalcTextSize("right").x;
                    ImGui::TextUnformatted("right");
                    if (graph_.num_edges_from_node(node.ui.multiply.rhs) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat(
                            "##hidelabel", &graph_.node(node.ui.multiply.rhs).value, 0.01f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                ImGui::Spacing();

                {
                    ImNodes::BeginOutputAttribute(node.id);
                    const float label_width = ImGui::CalcTextSize("result").x;
                    ImGui::Indent(node_width - label_width);
                    ImGui::TextUnformatted("result");
                    ImNodes::EndOutputAttribute();
                }

                ImNodes::EndNode();
            }
            break;
            case UiNodeType::output:
            {
                const float node_width = 100.0f;
                ImNodes::PushColorStyle(ImNodesCol_TitleBar, IM_COL32(11, 109, 191, 255));
                ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, IM_COL32(45, 126, 194, 255));
                ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, IM_COL32(81, 148, 204, 255));
                ImNodes::BeginNode(node.id);

                ImNodes::BeginNodeTitleBar();
                ImGui::TextUnformatted("output");
                ImNodes::EndNodeTitleBar();

                ImGui::Dummy(ImVec2(node_width, 0.f));
                {
                    ImNodes::BeginInputAttribute(node.ui.output.r);
                    const float label_width = ImGui::CalcTextSize("r").x;
                    ImGui::TextUnformatted("r");
                    if (graph_.num_edges_from_node(node.ui.output.r) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat(
                            "##hidelabel", &graph_.node(node.ui.output.r).value, 0.01f, 0.f, 1.0f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                ImGui::Spacing();

                {
                    ImNodes::BeginInputAttribute(node.ui.output.g);
                    const float label_width = ImGui::CalcTextSize("g").x;
                    ImGui::TextUnformatted("g");
                    if (graph_.num_edges_from_node(node.ui.output.g) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat(
                            "##hidelabel", &graph_.node(node.ui.output.g).value, 0.01f, 0.f, 1.f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                ImGui::Spacing();

                {
                    ImNodes::BeginInputAttribute(node.ui.output.b);
                    const float label_width = ImGui::CalcTextSize("b").x;
                    ImGui::TextUnformatted("b");
                    if (graph_.num_edges_from_node(node.ui.output.b) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat(
                            "##hidelabel", &graph_.node(node.ui.output.b).value, 0.01f, 0.f, 1.0f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }
                ImNodes::EndNode();
                ImNodes::PopColorStyle();
                ImNodes::PopColorStyle();
                ImNodes::PopColorStyle();
            }
            break;
            case UiNodeType::sine:
            {
                const float node_width = 100.0f;
                ImNodes::BeginNode(node.id);

                ImNodes::BeginNodeTitleBar();
                ImGui::TextUnformatted("sine");
                ImNodes::EndNodeTitleBar();

                {
                    ImNodes::BeginInputAttribute(node.ui.sine.input);
                    const float label_width = ImGui::CalcTextSize("number").x;
                    ImGui::TextUnformatted("number");
                    if (graph_.num_edges_from_node(node.ui.sine.input) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat(
                            "##hidelabel",
                            &graph_.node(node.ui.sine.input).value,
                            0.01f,
                            0.f,
                            1.0f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                ImGui::Spacing();

                {
                    ImNodes::BeginOutputAttribute(node.id);
                    const float label_width = ImGui::CalcTextSize("output").x;
                    ImGui::Indent(node_width - label_width);
                    ImGui::TextUnformatted("output");
                    ImNodes::EndOutputAttribute();
                }

                ImNodes::EndNode();
            }
            break;
            case UiNodeType::image:
            {
                const float node_width = 250.0f;
                ImNodes::BeginNode(node.id);

                ImNodes::BeginNodeTitleBar();
                ImGui::TextUnformatted("image");
                ImNodes::EndNodeTitleBar();

                // Content: input for path and thumbnail + load button
                {
                    // Unique labels per node using id
                    char pathBuf[512] = {0};
                    if (!node.imageTexturePath.empty())
                        std::snprintf(pathBuf, sizeof(pathBuf), "%s", node.imageTexturePath.c_str());

                    ImGui::PushItemWidth(node_width);
                    //if (ImGui::InputText(("Path##img" + std::to_string(node.id)).c_str(), pathBuf, sizeof(pathBuf)))
                    //{ /* intentionally commented: path editing via UI disabled */ }
                    ImGui::PopItemWidth();

                    ImGui::SameLine();
                    if (ImGui::Button(("Load##img" + std::to_string(node.id)).c_str()))
                    {
                        //if (!node.imageTexturePath.empty())
                        //{
                        //    pine::Image img;
                        //    if (img.Create(node.imageTexturePath.c_str()))
                        //    {
                        //        // free previous texture if any
                        //        if (node.texture)
                        //        {
                        //            delete node.texture;
                        //            node.texture = nullptr;
                        //        }
                        //        node.texture = new pine::Texture(GL_TEXTURE_2D);
                        //        node.texture->LoadFromImage(img);
                        //    }
                        //}
                    }
                }

                ImGui::Spacing();
                // show thumbnail if texture present
                if (node.texture)
                {
                    ImTextureID texId = (ImTextureID)(intptr_t)node.texture->GetGLHandle();
                    ImGui::Image(texId, ImVec2(128, 128));
                }

                // Add an output attribute on the right side so this image node can be linked like add/multiply
                {
                    ImNodes::BeginOutputAttribute(node.id);
                    const float label_width = ImGui::CalcTextSize("out").x;
                    ImGui::Indent(node_width - 5*label_width);
                    ImGui::TextUnformatted("out");
                    ImNodes::EndOutputAttribute();
                }

                ImNodes::EndNode();
            }
            break;
            case UiNodeType::time:
            {
                ImNodes::BeginNode(node.id);

                ImNodes::BeginNodeTitleBar();
                ImGui::TextUnformatted("time");
                ImNodes::EndNodeTitleBar();

                ImNodes::BeginOutputAttribute(node.id);
                ImGui::Text("output");
                ImNodes::EndOutputAttribute();

                ImNodes::EndNode();
            }
            break;
            case UiNodeType::material:
            {
				float out = 0.f;
                GetFirstOutgoingNodeValue(node.ui.material.input1, out);
                GetFirstOutgoingNodeValue(node.ui.material.input2, out);
                GetFirstOutgoingNodeValue(node.ui.material.input3, out);
                const float node_width = 100.0f;
                ImNodes::PushColorStyle(ImNodesCol_TitleBar, IM_COL32(11, 109, 191, 255));
                ImNodes::PushColorStyle(ImNodesCol_TitleBarHovered, IM_COL32(45, 126, 194, 255));
                ImNodes::PushColorStyle(ImNodesCol_TitleBarSelected, IM_COL32(81, 148, 204, 255));
                ImNodes::BeginNode(node.id);

                ImNodes::BeginNodeTitleBar();
                ImGui::TextUnformatted("material");
                ImNodes::EndNodeTitleBar();

                ImGui::Dummy(ImVec2(node_width, 0.f));
                {
                    ImNodes::BeginInputAttribute(node.ui.material.input1);
                    const float label_width = ImGui::CalcTextSize("Base Color").x;
                    ImGui::TextUnformatted("Base Color");

                    if (graph_.num_edges_from_node(node.ui.material.input1) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat(
                            "##hidelabel", &graph_.node(node.ui.material.input1).value, 0.01f, 0.f, 1.0f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                ImGui::Spacing();

                {
                    ImNodes::BeginInputAttribute(node.ui.material.input2);
                    const float label_width = ImGui::CalcTextSize("Normal Map").x;
                    ImGui::TextUnformatted("Normal Map");
                    if (graph_.num_edges_from_node(node.ui.material.input2) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat(
                            "##hidelabel", &graph_.node(node.ui.material.input2).value, 0.01f, 0.f, 1.0f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }

                ImGui::Spacing();

                {
                    ImNodes::BeginInputAttribute(node.ui.material.input3);
                    const float label_width = ImGui::CalcTextSize("Metalness Map").x;
                    ImGui::TextUnformatted("Metalness Map");
                    if (graph_.num_edges_from_node(node.ui.material.input3) == 0ull)
                    {
                        ImGui::SameLine();
                        ImGui::PushItemWidth(node_width - label_width);
                        ImGui::DragFloat(
                            "##hidelabel", &graph_.node(node.ui.material.input3).value, 0.01f, 0.f, 1.0f);
                        ImGui::PopItemWidth();
                    }
                    ImNodes::EndInputAttribute();
                }
                ImNodes::EndNode();
                ImNodes::PopColorStyle();
                ImNodes::PopColorStyle();
                ImNodes::PopColorStyle();
            }
            break;
            }
        }

        for (const auto& edge : graph_.edges())
        {
            // If edge doesn't start at value, then it's an internal edge, i.e.
            // an edge which links a node's operation to its input. We don't
            // want to render node internals with visible links.
			if (graph_.node(edge.from).type != NodeType::value && graph_.node(edge.from).type != NodeType::image)
                continue;

            ImNodes::Link(edge.id, edge.from, edge.to);
        }

        ImNodes::MiniMap(0.2f, minimap_location_);
        ImNodes::EndNodeEditor();

        // Handle new links
        // These are driven by Imnodes, so we place this code after EndNodeEditor().

        {
            int start_attr, end_attr;
            if (ImNodes::IsLinkCreated(&start_attr, &end_attr))
            {
                const NodeType start_type = graph_.node(start_attr).type;
                const NodeType end_type = graph_.node(end_attr).type;

                const bool valid_link = start_type != end_type;
                if (valid_link)
                {
                    // Ensure the edge is always directed from the value to
                    // whatever produces the value
                    if (start_type != NodeType::value)
                    {
                        std::swap(start_attr, end_attr);
                    }
                    graph_.insert_edge(start_attr, end_attr);
                }
            }
        }

        // Handle deleted links

        {
            int link_id;
            if (ImNodes::IsLinkDestroyed(&link_id))
            {
                graph_.erase_edge(link_id);
            }
        }

        {
            const int num_selected = ImNodes::NumSelectedLinks();
            if (num_selected > 0 && ImGui::IsKeyReleased(ImGuiKey_X))
            {
                static std::vector<int> selected_links;
                selected_links.resize(static_cast<size_t>(num_selected));
                ImNodes::GetSelectedLinks(selected_links.data());
                for (const int edge_id : selected_links)
                {
                    graph_.erase_edge(edge_id);
                }
            }
        }

        {
            const int num_selected = ImNodes::NumSelectedNodes();
            if (num_selected > 0 && ImGui::IsKeyReleased(ImGuiKey_X))
            {
                static std::vector<int> selected_nodes;
                selected_nodes.resize(static_cast<size_t>(num_selected));
                ImNodes::GetSelectedNodes(selected_nodes.data());
                for (const int node_id : selected_nodes)
                {
                    graph_.erase_node(node_id);
                    auto iter = std::find_if(
                        nodes_.begin(), nodes_.end(), [node_id](const UiNode& node) -> bool {
                            return node.id == node_id;
                        });
                    // Erase any additional internal nodes
                    switch (iter->type)
                    {
                    case UiNodeType::add:
                        graph_.erase_node(iter->ui.add.lhs);
                        graph_.erase_node(iter->ui.add.rhs);
                        break;
                    case UiNodeType::multiply:
                        graph_.erase_node(iter->ui.multiply.lhs);
                        graph_.erase_node(iter->ui.multiply.rhs);
                        break;
                    case UiNodeType::output:
                        graph_.erase_node(iter->ui.output.r);
                        graph_.erase_node(iter->ui.output.g);
                        graph_.erase_node(iter->ui.output.b);
                        root_node_id_ = -1;
                        break;
                    case UiNodeType::sine:
                        graph_.erase_node(iter->ui.sine.input);
                        break;
                    case UiNodeType::image:
                        // free GPU resource if allocated
                        if (iter->texture)
                        {
                            delete iter->texture;
                            iter->texture = nullptr;
                        }
                        break;
                    case UiNodeType::material:
                        graph_.erase_node(iter->ui.material.input1);
                        graph_.erase_node(iter->ui.material.input2);
                        graph_.erase_node(iter->ui.material.input3);
                        root_node_id_ = -1;
                        break;
                    default:
                        break;
                    }
                    nodes_.erase(iter);
                }
            }
        }

        ImGui::End();

        // The color output window

        //const ImU32 color =
        //    root_node_id_ != -1 ? evaluate(graph_, root_node_id_) : IM_COL32(255, 20, 147, 255);
        //ImGui::PushStyleColor(ImGuiCol_WindowBg, color);
        //ImGui::Begin("output color");
        //ImGui::End();
        //ImGui::PopStyleColor();
    }

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
                int input1, input2, input3;
            } material;
        } ui;
        // image node data (kept outside the union)
        std::string imageTexturePath;
        pine::Texture* texture = nullptr;
    };

    Graph<Node>            graph_;
    std::vector<UiNode>    nodes_;
    int                    root_node_id_;
    ImNodesMiniMapLocation minimap_location_;
};

extern ColorNodeEditor color_editor;

void NodeEditorInitializeHello();
void NodeEditorShowHello();
void NodeEditorShutdownHello();
void NodeEditorInitializeColor();
void NodeEditorShowColor();
void NodeEditorShutdownColor();
void NodeEditorInitializeMulti();
void NodeEditorShowMulti();
void NodeEditorShutdownMulti();
void NodeEditorInitializeSave();
void NodeEditorShowSave();
void NodeEditorShutdownSave();
} // namespace example