#pragma once
#include "Platform/OpenGL/OpenGLRenderer.h"

#include <GL/glew.h>

namespace Pine {
	
	void OpenGLRenderer::DrawIndexed(/*const IndexedModel& model*/)
	{

	}

	void OpenGLRenderer::BufferMesh(Mesh& mesh, Shader& shader)
	{
		glGenVertexArrays(1, &mesh.m_VA);
		glBindVertexArray(mesh.m_VA);

		glGenBuffers(1, &mesh.m_VB);

		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_VB);
		size_t offset = 0;
		std::vector<float> data;
		unsigned int loc;

		if (shader.GetAttributeLocation("position", loc)) {
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += mesh.Positions.size() * sizeof(float) * 3;

			for (int i = 0; i < mesh.Positions.size(); i++)
			{
				data.push_back(mesh.Positions[i].x);
				data.push_back(mesh.Positions[i].y);
				data.push_back(mesh.Positions[i].z);
			}
		}
		if (mesh.TexCoords.size() > 0 && shader.GetAttributeLocation("texCoord", loc))
		{
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 2, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += mesh.TexCoords.size() * sizeof(float) * 2;

			for (int i = 0; i < mesh.TexCoords.size(); i++)
			{
				data.push_back(mesh.TexCoords[i].x);
				data.push_back(mesh.TexCoords[i].y);
			}
		}
		if (mesh.Normals.size() > 0 && shader.GetAttributeLocation("normal", loc))
		{
			glEnableVertexAttribArray(loc);
			glVertexAttribPointer(loc, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)offset);
			offset += mesh.Normals.size() * sizeof(float) * 3;

			for (int i = 0; i < mesh.Normals.size(); i++)
			{
				data.push_back(mesh.Normals[i].x);
				data.push_back(mesh.Normals[i].y);
				data.push_back(mesh.Normals[i].z);
			}
		}
		glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), &data[0], GL_STATIC_DRAW);

		// only fill the index buffer if the index array is non-empty.
		if (mesh.Indices.size() > 0)
		{
			glGenBuffers(1, &mesh.m_EB);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_EB);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh.Indices.size() * sizeof(unsigned int), &mesh.Indices[0], GL_STATIC_DRAW);
		}

		glBindVertexArray(0);

		mesh.m_Buffered = true;
	}

	OpenGLRenderer::OpenGLRenderer()
	{
		//s_Instance = this;

		m_Camera = new Camera();

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
		if (!mesh.m_Buffered) {
			BufferMesh(mesh, *mat.m_Shader);
		}

		mat.m_Shader->Bind();

		//here enable texturing unit
		if (mat.m_Texture != nullptr)
			mat.m_Texture->Bind();

		glBindVertexArray(mesh.m_VA);

		if (mesh.Indices.size() > 0)
			glDrawElementsBaseVertex(GL_TRIANGLES, mesh.Indices.size(), GL_UNSIGNED_INT, 0, 0);
		else
			glDrawArrays(GL_TRIANGLES, 0, mesh.Positions.size());

		glBindVertexArray(0);
	}

}