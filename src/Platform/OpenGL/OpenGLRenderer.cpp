#pragma once
#include "Platform/OpenGL/OpenGLRenderer.h"

namespace Pine {
	
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
			offset += mesh.m_positions.size() * sizeof(float) * 3;

			for (unsigned int i = 0; i < mesh.m_positions.size(); i++)
			{
				data.push_back(mesh.m_positions[i].x);
				data.push_back(mesh.m_positions[i].y);
				data.push_back(mesh.m_positions[i].z);
			}
		}
		if (mesh.m_texCoords.size() > 0 && shader.GetAttributeLocation("texCoord", loc))
		{
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += mesh.m_texCoords.size() * sizeof(float) * 2;

			for (unsigned int i = 0; i < mesh.m_texCoords.size(); i++)
			{
				data.push_back(mesh.m_texCoords[i].x);
				data.push_back(mesh.m_texCoords[i].y);
			}
		}
		if (mesh.m_normals.size() > 0 && shader.GetAttributeLocation("normal", loc))
		{
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += mesh.m_normals.size() * sizeof(float) * 3;

			for (unsigned int i = 0; i < mesh.m_normals.size(); i++)
			{
				data.push_back(mesh.m_normals[i].x);
				data.push_back(mesh.m_normals[i].y);
				data.push_back(mesh.m_normals[i].z);
			}
		}
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

		// only fill the index buffer if the index array is non-empty.
		if (mesh.m_indices.size() > 0)
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh._EB);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.m_indices.size() * sizeof(unsigned int), &mesh.m_indices[0], GL_STATIC_DRAW);
		}

		glBindVertexArray(0);

		mesh._buffered = true;
	}

	OpenGLRenderer::OpenGLRenderer()
	{
		//s_Instance = this;
		m_rendererAPI = GRAPHICS_API::OPENGL_API;

		_camera = new Camera();

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

		if (mesh.m_indices.size() > 0)
			glDrawElementsBaseVertex(GL_TRIANGLES, mesh.m_indices.size(), GL_UNSIGNED_INT, 0, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, mesh.m_positions.size());

		glBindVertexArray(0);
	}

}
