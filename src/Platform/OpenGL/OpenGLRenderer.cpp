#pragma once
#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Core/Application.h"
static const GLenum skyboxFaceTypes[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
								  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
								  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
								  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
								  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
								  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };
namespace pine {
	
	void OpenGLRenderer::DrawIndexed(/*const IndexedModel& model*/)
	{

	}

	void OpenGLRenderer::InitSkybox()
	{
		glGenVertexArrays(1, &_skyboxCubeVAO);
		glBindVertexArray(_skyboxCubeVAO);

		GLuint skyboxVBO = 0;
		glGenBuffers(1, &skyboxVBO);
		glBindBuffer(GL_ARRAY_BUFFER, skyboxVBO);

		// 36 vertices, 3 components each
		static const float skyboxVertices[] = {
			// positions
			-1.0f,  1.0f, -1.0f,
			-1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f, -1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,

			-1.0f, -1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f,
			-1.0f, -1.0f,  1.0f,

			-1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f, -1.0f,
			 1.0f,  1.0f,  1.0f,
			 1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f,  1.0f,
			-1.0f,  1.0f, -1.0f,

			-1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f, -1.0f,
			 1.0f, -1.0f, -1.0f,
			-1.0f, -1.0f,  1.0f,
			 1.0f, -1.0f,  1.0f
		};

		glBufferData(GL_ARRAY_BUFFER, sizeof(skyboxVertices), skyboxVertices, GL_STATIC_DRAW);
		// position attribute (location = 0 in shader)
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);

		// unbind VBO/VAO until use
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);

		// Create cubemap texture
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &_skyboxTextureObj);
		
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_BASE_LEVEL, 0);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_MAX_LEVEL, 0);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTextureStorage2D(_skyboxTextureObj, 1, GL_RGB32F,
			_skybox->GetCubemapTextures()[0].GetWidth(), _skybox->GetCubemapTextures()[0].GetHeight());

		for (int i = 0; i < 6; ++i) {
			const void* pSrc = _skybox->GetCubemapTextures()[i].GetPixels();
			glTextureSubImage3D(_skyboxTextureObj,
				0,      // mipmap level
				0,      // xOffset
				0,      // yOffset
				i,      // zOffset (layer in the case of a cubemap)
				_skybox->GetCubemapTextures()[i].GetWidth(), _skybox->GetCubemapTextures()[i].GetHeight(),   // 2D image dimensions
				1,          // depth
				GL_RGB,     // format
				GL_FLOAT,   // data type
				pSrc);
		}
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	}

	void OpenGLRenderer::GenerateIrradianceMap()
	{
		// Create irradiance cubemap
		glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &_irradianceMapTextureObj);
		int irradianceSize = 32; // low-res convolution target
		glTextureStorage2D(_irradianceMapTextureObj, 1, GL_RGB16F, irradianceSize, irradianceSize);

		glTextureParameteri(_irradianceMapTextureObj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_irradianceMapTextureObj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_irradianceMapTextureObj, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_irradianceMapTextureObj, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTextureParameteri(_irradianceMapTextureObj, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		// Create framebuffer + renderbuffer
		GLuint captureFBO = 0;
		GLuint captureRBO = 0;
		glGenFramebuffers(1, &captureFBO);
		glGenRenderbuffers(1, &captureRBO);

		glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
		glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, irradianceSize, irradianceSize);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

		glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);
		glm::mat4 captureViews[] =
		{
			glm::lookAt(glm::vec3(0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
		};

		Shader* convShader = Shader::LoadShaders("../res/shaders/skybox_irradiance_conv");
		convShader->Bind();
		convShader->SetUniformTextureSampler2D("environmentMap", 0);
		convShader->SetUniform("u_Projection", captureProjection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureObj);

		GLint view[4];
		glGetIntegerv(GL_VIEWPORT, view);
		glViewport(0, 0, irradianceSize, irradianceSize);
		glBindVertexArray(_skyboxCubeVAO);
		for (unsigned int i = 0; i < 6; ++i)
		{
			convShader->SetUniform("u_View", captureViews[i]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, _irradianceMapTextureObj, 0);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}

		glBindVertexArray(0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &captureFBO);
		glDeleteRenderbuffers(1, &captureRBO);
	
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glViewport(view[0], view[1], view[2], view[3]);
		
		delete convShader;
	}

	void OpenGLRenderer::BufferModelMesh(MeshRenderer* mr)
	{
		MeshData& mesh = mr->GetModel()->mesh;

		glGenVertexArrays(1, &mesh.m_vertexArrayObject);
		glBindVertexArray(mesh.m_vertexArrayObject);

		glGenBuffers(NUM_BUFFERS, mesh.m_vertexArrayBuffers);

		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertexArrayBuffers[POSITION_VB]);
		size_t offset = 0;
		std::vector<float> data;
		unsigned int loc;

		// TODO: maybe list the attributes somewhere
		if ((loc = mr->GetAttributeLocation("position") >= 0)) {
			glEnableVertexAttribArray(loc);
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_Positions[0]) * mesh.m_Positions.size(), &mesh.m_Positions[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(POSITION_LOCATION);
			glVertexAttribPointer(POSITION_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);

		}
		if (!mesh.m_TexCoords.empty() && (loc = mr->GetAttributeLocation("texCoord") >= 0))
		{
			glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertexArrayBuffers[TEXCOORD_VB]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_TexCoords[0]) * mesh.m_TexCoords.size(), &mesh.m_TexCoords[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TEX_COORD_LOCATION);
			glVertexAttribPointer(TEX_COORD_LOCATION, 2, GL_FLOAT, GL_FALSE, 0, 0);
		}
		if (!mesh.m_Normals.empty() && (loc = mr->GetAttributeLocation("normal") >= 0))
		{
			glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertexArrayBuffers[NORMAL_VB]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_Normals[0]) * mesh.m_Normals.size(), &mesh.m_Normals[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(NORMAL_LOCATION);
			glVertexAttribPointer(NORMAL_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (!mesh.m_Tangents.empty() && (loc = mr->GetAttributeLocation("tangent") >= 0))
		{
			glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertexArrayBuffers[TANGENT_VB]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_Tangents[0]) * mesh.m_Tangents.size(), &mesh.m_Tangents[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(TANGENT_LOCATION);
			glVertexAttribPointer(TANGENT_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		if (!mesh.m_Bitangents.empty() && (loc = mr->GetAttributeLocation("bitangent") >= 0))
		{
			glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertexArrayBuffers[BITANGENT_VB]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_Bitangents[0]) * mesh.m_Bitangents.size(), &mesh.m_Bitangents[0], GL_STATIC_DRAW);
			glEnableVertexAttribArray(BITANGENT_LOCATION);
			glVertexAttribPointer(BITANGENT_LOCATION, 3, GL_FLOAT, GL_FALSE, 0, 0);
		}

		// only fill the index buffer if the index array is non-empty.
		if (!mesh.m_Indices.empty() && (loc = mr->GetAttributeLocation("bitangent") >= 0))
		{
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_vertexArrayBuffers[INDEX_VB]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.m_Indices[0]) * mesh.m_Indices.size(), &mesh.m_Indices[0], GL_STATIC_DRAW);
		}

		glBindVertexArray(0);

		mesh._buffered = true;
	}

	OpenGLRenderer::OpenGLRenderer()
	{
		//s_Instance = this;
		m_rendererAPI = GraphicsApi::OPENGL_API;

		//if in editor
		_camera = Application::editor->GetCamera();

		//_camera = new Camera();

		glewInit();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
	}

	void OpenGLRenderer::OnUpdate()
	{
		Clear();

		DrawSkybox();
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

	void OpenGLRenderer::DrawSkybox()
	{
		GLint prevDepthFunc = 0;
		glGetIntegerv(GL_DEPTH_FUNC, &prevDepthFunc);
		GLboolean prevDepthMask = GL_FALSE;
		glGetBooleanv(GL_DEPTH_WRITEMASK, &prevDepthMask);

		glDepthFunc(GL_LEQUAL);
		glDepthMask(GL_FALSE);

		// Bind skybox shader (replace with your actual shader instance)
		// The shader must sample a samplerCube uniform and use view/proj where view has no translation.
		Shader* skyboxShader = _skybox->GetShader();
		if (skyboxShader) {
			skyboxShader->Bind();

			glm::mat4 view = Application::renderer->GetRenderCamera().GetViewMatrix();        // view matrix (camera)
			glm::mat4 proj = Application::renderer->GetRenderCamera().GetProjectionMatrix(); // projection matrix
			glm::mat4 viewNoTranslation = glm::mat4(glm::mat3(view)); // strip translation

			skyboxShader->SetUniform("u_View", viewNoTranslation);
			skyboxShader->SetUniform("u_Projection", proj);

			// Bind cubemap texture to unit 0 and point shader sampler to unit 0.
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureObj);
			// Use your shader helper to set an int sampler uniform; fallback to glUniform1i if necessary:
			skyboxShader->SetUniformTextureSampler2D("u_Skybox", 0); // or SetUniform("u_skybox", 0)
		}

		// Draw a unit cube (36 verts). Create and keep a VAO/VBO for this cube in InitSkybox.
		// _skyboxCubeVAO is expected to be created earlier in InitSkybox.
		glBindVertexArray(_skyboxCubeVAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		glBindVertexArray(0);

		// Unbind texture unit for cleanliness
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

		// Restore depth state
		glDepthMask(prevDepthMask);
		glDepthFunc(prevDepthFunc);
	}

	void OpenGLRenderer::Startup()
	{
		_skybox = std::make_unique<Skybox>();
		InitSkybox();
		GenerateIrradianceMap();
		//_skyboxTextureObj = _irradianceMapTextureObj;
	}

	void OpenGLRenderer::Draw(MeshRenderer* mr)
	{
		// TODO: Draw can be abstracted
		Model3D* model = mr->GetModel();
		if (!model->mesh._buffered) {
			// TODO: this is wrong, needs seperate mesh/shader
			// BufferMesh(model.mesh, *mat.m_Shader);
		}

		UpdateRenderFlags(mr); // TODO: OPT does not need to be here every draw call

		// bind VAO once for the mesh data
		glBindVertexArray(model->mesh.m_vertexArrayObject); // DIFFERENT FROM _VA BUFFERS

		// TODO OPT: redundant operations
		glm::mat4 umodel = mr->GetTransform().GetModel();
		glm::mat4 mvp = Application::renderer.get()->GetRenderCamera().GetViewProjection() * umodel;
		glm::vec3 camPos = Application::renderer.get()->GetRenderCamera().GetPos();

		// TODO : check if window open cause of crashes
		// If model defines BasicMesh ranges, draw each range separately.
		if (!model->b_meshes.empty())
		{
			for (const BasicMesh& bm : model->b_meshes)
			{
				// bind shader/texture (existing code assumes 'mat' is set up)
				Shader* shader = model->materials[bm.materialIndex]->m_shader;
				shader->Bind();
				//material->m_Shader->SetUniform("Model", model);
				// TODO: think if shader attributes should be selected from shader data
				shader->SetUniform("MVP", mvp); // TODO: build on uniform system to find needed uniforms from shader
				shader->SetUniform("Model", umodel);
				shader->SetUniform("u_cameraPos", camPos);
				//shader->SetUniform("u_lightDir", lightDir);
				//shader->SetUniform("u_lightColor", lightColor);
				shader->SetUniform("u_roughness", model->materials[bm.materialIndex]->m_roughness);
				shader->SetUniform("u_metalness", model->materials[bm.materialIndex]->m_metallic);
				shader->SetUniform("u_renderFlags", mr->m_render_flags[bm.materialIndex]);

				// lights
				unsigned int lightCount = static_cast<unsigned int>(Application::lightPresets[Application::activeLightPresetIndex].size());
				std::vector<glm::vec3> lightDirs;
				std::vector<glm::vec3> lightColors;

				for (unsigned int i = 0; i < lightCount; i++)
				{
					lightDirs.push_back(Application::lightPresets[Application::activeLightPresetIndex][i].GetDirection());
					lightColors.push_back(Application::lightPresets[Application::activeLightPresetIndex][i].GetColor());
				}

				shader->SetUniform("u_nLights", lightCount);
				shader->SetUniformArray("u_lightDirs", lightDirs, MAX_LIGHTS);
				shader->SetUniformArray("u_lightDiffs", lightColors, MAX_LIGHTS);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_CUBE_MAP, _irradianceMapTextureObj);
				shader->SetUniformCubeSampler("u_irradianceMap", 0);

				// Bind albedo (base) to texture unit 0
				// TODO: hardcoded texture unit indexes, also make functions for redundant uniform setting
				auto* albedoTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_BASE];
				if (albedoTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::BASE_TEXTURE)) {
					albedoTex->Bind(1);
					shader->SetUniformTextureSampler2D("u_albedoMap", 1);
				}

				 //Bind normal map to texture unit 1
				auto* normalTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_NORMAL];
				if (normalTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::NORMAL_MAPS)) {
					normalTex->Bind(2);
					shader->SetUniformTextureSampler2D("u_normalMap", 2);
				}

				auto* roughnessTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_ROUGHNESS];
				if (roughnessTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::ROUGHNESS_MAPS)) {
					roughnessTex->Bind(3);
					shader->SetUniformTextureSampler2D("u_roughnessMap", 3);
				}

				auto* metalnessTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_METALLIC];
				if (metalnessTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::METALNESS_MAPS)) {
					metalnessTex->Bind(4);
					shader->SetUniformTextureSampler2D("u_metalnessMap", 4);
				}

				auto* aoTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_AO];
				if (aoTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::AO_MAPS)) {
					aoTex->Bind(5);
					shader->SetUniformTextureSampler2D("u_aoMap", 5);
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
