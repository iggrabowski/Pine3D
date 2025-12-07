#pragma once
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Core/Application.h"

namespace pine {
	
	void OpenGLRenderer::DrawIndexed(/*const IndexedModel& model*/)
	{

	}

	void OpenGLRenderer::BufferMesh(MeshData& mesh, Shader& shader)
	{
		// TODO: check if this works correctly with different shaders _VA conflicts with method in InitMesh()
		glGenVertexArrays(1, &mesh._VA);
		glBindVertexArray(mesh._VA);

		glGenBuffers(1, &mesh._VB);
		glGenBuffers(1, &mesh._EB);

		glBindBuffer(GL_ARRAY_BUFFER, mesh._VB);
		size_t offset = 0;
		std::vector<float> data;
		unsigned int loc;

		if (shader.GetAttributeLocation("position", loc)) {
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += mesh.m_Positions.size() * sizeof(float) * 3;

			for (unsigned int i = 0; i < mesh.m_Positions.size(); i++)
			{
				data.push_back(mesh.m_Positions[i].x);
				data.push_back(mesh.m_Positions[i].y);
				data.push_back(mesh.m_Positions[i].z);
			}
		}
		if (mesh.m_TexCoords.size() > 0 && shader.GetAttributeLocation("texCoord", loc))
		{
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += mesh.m_TexCoords.size() * sizeof(float) * 2;

			for (unsigned int i = 0; i < mesh.m_TexCoords.size(); i++)
			{
				data.push_back(mesh.m_TexCoords[i].x);
				data.push_back(mesh.m_TexCoords[i].y);
			}
		}
		if (mesh.m_Normals.size() > 0 && shader.GetAttributeLocation("normal", loc))
		{
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += mesh.m_Normals.size() * sizeof(float) * 3;

			for (unsigned int i = 0; i < mesh.m_Normals.size(); i++)
			{
				data.push_back(mesh.m_Normals[i].x);
				data.push_back(mesh.m_Normals[i].y);
				data.push_back(mesh.m_Normals[i].z);
			}
		}
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

		// only fill the index buffer if the index array is non-empty.
		if (mesh.m_Indices.size() > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh._EB);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.m_Indices.size() * sizeof(unsigned int), &mesh.m_Indices[0], GL_STATIC_DRAW);
		}

		glBindVertexArray(0);

		mesh._buffered = true;
	}

	OpenGLRenderer::OpenGLRenderer()
	{
		//s_Instance = this;
		m_rendererAPI = GRAPHICS_API::OPENGL_API;

		//if in editor
		_camera = Application::editor->GetCamera();

		//_camera = new Camera();

		glewInit();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}

	/*void OpenGLRenderer::Init()
	{
		glewInit();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}*/

	void OpenGLRenderer::Clear()
	{
		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::Draw(MeshRenderer* mr)
	{
		Model* model = mr->GetModel();
		if (!model->mesh._buffered) {
			// TODO: this is wrong, needs seperate mesh/shader
			// BufferMesh(model.mesh, *mat.m_Shader);
		}
		
		// bind VAO once for the mesh data
		glBindVertexArray(model->mesh.m_vertexArrayObject); // DIFFERENT FROM _VA BUFFERS

		glm::mat4 umodel = mr->GetTransform().GetModel();
		glm::mat4 mvp = Application::renderer->GetRenderCamera().GetViewProjection() * umodel;
		glm::vec3 camPos = Application::renderer->GetRenderCamera().GetPos();
		glm::vec3 lightDir = glm::vec3(-0.5f, -1.0f, -0.5f); // hard coded for now TODO: add light objects
		glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

		// TODO : check if window open cause of crashes
		// If model defines BasicMesh ranges, draw each range separately.
		if (!model->b_meshes.empty())
		{
			for (const BasicMesh& bm : model->b_meshes)
			{
				// TODO: check if shader/texture exists
				// bind shader/texture (existing code assumes 'mat' is set up)
				Shader* shader = model->materials[bm.materialIndex]->m_Shader;
				shader->Bind();
				//material->m_Shader->SetUniform("Model", model);
				shader->SetUniform("MVP", mvp); // TODO: build on uniform system to find needed uniforms from shader
				shader->SetUniform("Model", umodel);
				shader->SetUniform("u_cameraPosition", camPos);
				shader->SetUniform("u_lightDir", lightDir);
				shader->SetUniform("u_lightColor", lightColor);
				shader->SetUniform("u_roughness", model->materials[bm.materialIndex]->m_roughness);

				// Bind albedo (base) to texture unit 0
				auto* albedoTex = model->materials[bm.materialIndex]->m_Textures[TEX_TYPE_BASE];
				if (albedoTex) {
					albedoTex->Bind(0);
					shader->SetUniformTextureSampler2D("u_albedoMap", 0);
				}

				// Bind normal map to texture unit 1
				auto* normalTex = model->materials[bm.materialIndex]->m_Textures[TEX_TYPE_NORMAL];
				if (normalTex) {
					normalTex->Bind(1);
					shader->SetUniformTextureSampler2D("u_normalMap", 1);
				}

				// TODO: bind other textures (metallic, roughness, ao, etc.)

				// If the mesh has an index buffer, use glDrawElementsBaseVertex with the BaseIndex offset.
				if (!model->mesh.m_Indices.empty())
				{
					glDrawElementsBaseVertex(GL_TRIANGLES,
						static_cast<GLsizei>(bm.numIndices),
						GL_UNSIGNED_INT,
						(void*)(sizeof(unsigned int) * bm.baseIndex),
						static_cast<GLint>(bm.baseVertex));
				}
				else
				{
					// No index buffer: draw arrays starting at BaseVertex for NumIndices vertices.
					glDrawArrays(GL_TRIANGLES,
						static_cast<GLint>(bm.baseVertex),
						static_cast<GLsizei>(bm.numIndices));
				}
			}
		}
		else
		{
			// Fallback: draw entire mesh if no BasicMesh info available.
			if (!model->mesh.m_Indices.empty())
				glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(model->mesh.m_Indices.size()), GL_UNSIGNED_INT, 0);
			else
				glDrawArrays(GL_TRIANGLES, 0, static_cast<GLsizei>(model->mesh.m_Positions.size()));
		}

		glBindVertexArray(0);
	}

}
