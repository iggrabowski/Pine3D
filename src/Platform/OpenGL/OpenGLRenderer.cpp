#pragma once
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Core/Application.h"

namespace pine {
	
	void OpenGLRenderer::DrawIndexed(/*const IndexedModel& model*/)
	{

	}

	void OpenGLRenderer::BufferMesh(Mesh& mesh, Shader& shader)
	{
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
		glClearColor(0.0f, 0.0f, 0.4f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void OpenGLRenderer::Draw(Mesh& mesh, Material& mat)
	{
		if (!mesh._buffered) {
			BufferMesh(mesh, *mat.m_Shader);
		}

		mat.m_Shader->Bind();

		// here enable texturing unit
		mat.m_Texture->Bind();

		glBindVertexArray(mesh._VA);

		if (mesh.m_Indices.size() > 0)
			glDrawElementsBaseVertex(GL_TRIANGLES, mesh.m_Indices.size(), GL_UNSIGNED_INT, 0, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, mesh.m_Positions.size());

		glBindVertexArray(0);
	}

}
