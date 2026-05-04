#include "NodeEditor.h"
#define BASE_NODE_POS_X 20
#define BASE_NODE_POS_Y 440
#define MATERIAL_NODE_POS_X 450
#define MATERIAL_NODE_POS_Y 690

namespace pine
{
	void NodeEditor::NodeEditorInitialize()
	{
		ImNodesIO& io = ImNodes::GetIO();
		io.LinkDetachWithModifierClick.Modifier = &ImGui::GetIO().KeyCtrl;
	}

	bool NodeEditor::GetFirstOutgoingNodeValue(int nodeId, float &outValue) const
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

	void NodeEditor::CreateMaterialComponentNode(TextureType type, Material& material, UiNode& ui_node)
	{
		ImVec2 position;
		UiNode component_node;
		switch (type)
		{
		case TEX_TYPE_BASE: position = ImVec2(BASE_NODE_POS_X + 200, BASE_NODE_POS_Y); break;
		case TEX_TYPE_NORMAL: position = ImVec2(BASE_NODE_POS_X, BASE_NODE_POS_Y); break;
		case TEX_TYPE_METALLIC: position = ImVec2(BASE_NODE_POS_X, BASE_NODE_POS_Y + 200); break;
		case TEX_TYPE_ROUGHNESS: position = ImVec2(BASE_NODE_POS_X, BASE_NODE_POS_Y + 400); break;
		case TEX_TYPE_AO: position = ImVec2(BASE_NODE_POS_X + 200, BASE_NODE_POS_Y + 200); break;
		case TEX_TYPE_HEIGHT: position = ImVec2(BASE_NODE_POS_X + 200, BASE_NODE_POS_Y + 400); break;
		}

		component_node.type = UiNodeType::image;
		component_node.imageTexturePath = "";
		component_node.texture = material.m_textures[type];
		component_node.id = graph_.insert_node(Node(NodeType::image, component_node.texture->GetGLHandle()));

		nodes_.push_back(component_node);
		ImNodes::SetNodeScreenSpacePos(component_node.id, position);
		switch (type)
		{
		case TEX_TYPE_BASE: graph_.insert_edge(ui_node.ui.material.input1, component_node.id); break;
		case TEX_TYPE_NORMAL: graph_.insert_edge(ui_node.ui.material.input2, component_node.id); break;
		case TEX_TYPE_METALLIC: graph_.insert_edge(ui_node.ui.material.input3, component_node.id); break;
		case TEX_TYPE_ROUGHNESS: graph_.insert_edge(ui_node.ui.material.input4, component_node.id); break;
		case TEX_TYPE_AO: graph_.insert_edge(ui_node.ui.material.input5, component_node.id); break;
		case TEX_TYPE_HEIGHT: graph_.insert_edge(ui_node.ui.material.input6, component_node.id); break;
		}
	}

	void NodeEditor::AddMaterialNodes(Material* material, ImVec2 pos)
	{
		if (!nodes_.empty())
		{
			std::unordered_set<int> ids_to_erase;
			for (const UiNode& n : nodes_)
			{
				ids_to_erase.insert(n.id);
				switch (n.type)
				{
				case UiNodeType::add:
					ids_to_erase.insert(n.ui.add.lhs);
					ids_to_erase.insert(n.ui.add.rhs);
					break;
				case UiNodeType::multiply:
					ids_to_erase.insert(n.ui.multiply.lhs);
					ids_to_erase.insert(n.ui.multiply.rhs);
					break;
				case UiNodeType::output:
					ids_to_erase.insert(n.ui.output.r);
					ids_to_erase.insert(n.ui.output.g);
					ids_to_erase.insert(n.ui.output.b);
					break;
				case UiNodeType::sine:
					ids_to_erase.insert(n.ui.sine.input);
					break;
				case UiNodeType::material:
					ids_to_erase.insert(n.ui.material.input1);
					ids_to_erase.insert(n.ui.material.input2);
					ids_to_erase.insert(n.ui.material.input3);
					ids_to_erase.insert(n.ui.material.input4);
					ids_to_erase.insert(n.ui.material.input5);
					ids_to_erase.insert(n.ui.material.input6);
					break;
				case UiNodeType::image:
					// image nodes have no internal child nodes in the graph (only the node id)
					break;
				case UiNodeType::time:
					// time node has only the op node id
					break;
				}
			}

			// Erase unique graph nodes
			for (int id : ids_to_erase)
			{
				graph_.erase_node(id);
			}
			// Clear UI list and reset root
			nodes_.clear();
			root_node_id_ = -1;
		}

		Texture* pointer = nullptr;
		for (auto texture : material->m_textures)
		{
			if (texture != nullptr) pointer = texture;
		}
		if (pointer == nullptr) return;

		// TODO: is the material node created every time?
		const Node value(NodeType::value, 0.f);
		const Node out(NodeType::output);
				
		UiNode ui_node;
		ui_node.type = UiNodeType::material;
		ui_node.ui.material.input1 = graph_.insert_node(value);
		ui_node.ui.material.input2 = graph_.insert_node(value);
		ui_node.ui.material.input3 = graph_.insert_node(value);
		ui_node.ui.material.input4 = graph_.insert_node(value);
		ui_node.ui.material.input5 = graph_.insert_node(value);
		ui_node.ui.material.input6 = graph_.insert_node(value);
		ui_node.material = material;
		ui_node.id = graph_.insert_node(out);
				
		graph_.insert_edge(ui_node.id, ui_node.ui.material.input1);
		graph_.insert_edge(ui_node.id, ui_node.ui.material.input2);
		graph_.insert_edge(ui_node.id, ui_node.ui.material.input3);
		graph_.insert_edge(ui_node.id, ui_node.ui.material.input4);
		graph_.insert_edge(ui_node.id, ui_node.ui.material.input5);
		graph_.insert_edge(ui_node.id, ui_node.ui.material.input6);
		nodes_.push_back(ui_node);
		ImNodes::SetNodeScreenSpacePos(ui_node.id, ImVec2(BASE_NODE_POS_X + 430, BASE_NODE_POS_Y + 250));
		root_node_id_ = ui_node.id;

		if (material->m_textures[pine::TEX_TYPE_BASE]) {
			CreateMaterialComponentNode(pine::TEX_TYPE_BASE, *material, ui_node);
		}

		if (material->m_textures[pine::TEX_TYPE_NORMAL])
		{
			CreateMaterialComponentNode(pine::TEX_TYPE_NORMAL, *material, ui_node);
		}

		if (material->m_textures[pine::TEX_TYPE_METALLIC])
		{
			CreateMaterialComponentNode(pine::TEX_TYPE_METALLIC, *material, ui_node);
		}

		if (material->m_textures[pine::TEX_TYPE_ROUGHNESS])
		{
			CreateMaterialComponentNode(pine::TEX_TYPE_ROUGHNESS, *material, ui_node);
		}

		if (material->m_textures[pine::TEX_TYPE_AO])
		{
			CreateMaterialComponentNode(pine::TEX_TYPE_AO, *material, ui_node);
		}
		
		if	(material->m_textures[pine::TEX_TYPE_HEIGHT])
		{
			CreateMaterialComponentNode(pine::TEX_TYPE_HEIGHT, *material, ui_node);
		}
	}

	void NodeEditor::Show()
	{
		
		//current_time_seconds = glfwGetTime();

		auto flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove;

		// The node editor window
		ImGui::Begin("node editor", nullptr, flags);

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
		// slider section goes here
		if (root_node_id_ != -1) {
			UiNode* root_ui_node = nullptr;
			for (auto& node : nodes_)
			{
				if (node.id == root_node_id_)
				{
					root_ui_node = &node;
					break;
				}
			}

			if (root_ui_node->material != nullptr)
			{

				static bool enable_normal_map = true;
				static bool enable_fixed_metalness = false;
				//static float fixed_metalness = 0.5f;
				static bool enable_fixed_roughness = false;
				//static float fixed_roughness = 0.5f;

				if (ImGui::CollapsingHeader("Material Properties (Mockup)", ImGuiTreeNodeFlags_DefaultOpen))
				{
					ImGui::Checkbox("Enable normal map", &enable_normal_map);
					root_ui_node->material->m_enableNormalMap = enable_normal_map;
					ImGui::Checkbox("Enable fixed metalness", &enable_fixed_metalness);
					root_ui_node->material->m_enableMetallicMap =! enable_fixed_metalness;
					ImGui::BeginDisabled(!enable_fixed_metalness);
					ImGui::SliderFloat("Metalness", &root_ui_node->material->m_metallic, 0.02f, 1.0f, "%.2f");
					ImGui::EndDisabled();

					ImGui::Separator();

					ImGui::Checkbox("Enable fixed roughness", &enable_fixed_roughness);
					root_ui_node->material->m_enableRoughnessMap =! enable_fixed_roughness;
					ImGui::BeginDisabled(!enable_fixed_roughness);
					ImGui::SliderFloat("Roughness", &root_ui_node->material->m_roughness, 0.02f, 1.0f, "%.2f");
					ImGui::EndDisabled();
				}
			}
		}
		ImGui::Columns(1);
		ImGui::TextUnformatted("Controls: ");
		//ImGui::NextColumn();
		ImGui::TextUnformatted("W -- Zoom in");
		ImGui::TextUnformatted("S -- Zoom out");
		ImGui::TextUnformatted("F1,F2,F3 -- Lighting presets");
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
			const bool open_popup = //ImGui::IsWindowFocused(ImGuiFocusedFlags_RootAndChildWindows) &&
				false;//ImNodes::IsEditorHovered() && ImGui::IsKeyReleased(ImGuiKey_A);

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
				 ui_node.ui.material.input4 = graph_.insert_node(value);
				 ui_node.ui.material.input5 = graph_.insert_node(value);
				 ui_node.ui.material.input6 = graph_.insert_node(value);
				 ui_node.id = graph_.insert_node(out);
					
					graph_.insert_edge(ui_node.id, ui_node.ui.material.input1);
					graph_.insert_edge(ui_node.id, ui_node.ui.material.input2);
					graph_.insert_edge(ui_node.id, ui_node.ui.material.input3);
					graph_.insert_edge(ui_node.id, ui_node.ui.material.input4);
					graph_.insert_edge(ui_node.id, ui_node.ui.material.input5);
					graph_.insert_edge(ui_node.id, ui_node.ui.material.input6);
					
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

						//ImGui::SameLine();
						//if (ImGui::Button(("Load##img" + std::to_string(node.id)).c_str()))
						//{
						//    //if (!node.imageTexturePath.empty())
						//    //{
						//    //    pine::Image img;
						//    //    if (img.Create(node.imageTexturePath.c_str()))
						//    //    {
						//    //        // free previous texture if any
						//    //        if (node.texture)
						//    //        {
						//    //            delete node.texture;
						//    //            node.texture = nullptr;
						//    //        }
						//    //        node.texture = new pine::Texture(GL_TEXTURE_2D);
						//    //        node.texture->LoadFromImage(img);
						//    //    }
						//    //}
						//}
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
					GetFirstOutgoingNodeValue(node.ui.material.input4, out);
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

					ImGui::Spacing();

					{
						ImNodes::BeginInputAttribute(node.ui.material.input4);
						const float label_width = ImGui::CalcTextSize("Roughness Map").x;
						ImGui::TextUnformatted("Roghness Map");
						if (graph_.num_edges_from_node(node.ui.material.input4) == 0ull)
						{
							ImGui::SameLine();
							ImGui::PushItemWidth(node_width - label_width);
							ImGui::DragFloat(
								"##hidelabel", &graph_.node(node.ui.material.input4).value, 0.01f, 0.f, 1.0f);
							ImGui::PopItemWidth();
						}
						ImNodes::EndInputAttribute();
					}

					ImGui::Spacing();

					{
						ImNodes::BeginInputAttribute(node.ui.material.input5);
						ImGui::TextUnformatted("AO Map");
						ImNodes::EndInputAttribute();
					}

					ImGui::Spacing();
					{
						ImNodes::BeginInputAttribute(node.ui.material.input6);
						ImGui::TextUnformatted("Height Map");
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
			if (false/*num_selected > 0 && ImGui::IsKeyReleased(ImGuiKey_X)*/)
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
			if (false/*num_selected > 0 && ImGui::IsKeyReleased(ImGuiKey_X)*/)
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
						graph_.erase_node(iter->ui.material.input4);
						root_node_id_ = -1;
						break;
					default:
						break;
					}
					nodes_.erase(iter);
				}
			}
		}
		_windowHeight = ImGui::GetWindowSize().x;
		ImGui::End();

		// The color output window

		//const ImU32 color =
		//    root_node_id_ != -1 ? evaluate(graph_, root_node_id_) : IM_COL32(255, 20, 147, 255);
		//ImGui::PushStyleColor(ImGuiCol_WindowBg, color);
		//ImGui::Begin("output color");
		//ImGui::End();
		//ImGui::PopStyleColor();

	}

	NodeEditor color_editor;

} // namespace pine
