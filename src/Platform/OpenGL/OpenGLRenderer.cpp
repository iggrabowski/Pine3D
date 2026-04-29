#pragma once
#include <utility>

#include "Platform/OpenGL/OpenGLRenderer.h"
#include "Core/Application.h"
namespace pine {

	static const GLenum skyboxFaceTypes[6] = { GL_TEXTURE_CUBE_MAP_POSITIVE_X,
								  GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
								  GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
								  GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
								  GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
								  GL_TEXTURE_CUBE_MAP_NEGATIVE_Z };
	static glm::mat4 captureViews[] =
		{
			glm::lookAt(glm::vec3(0.0f), glm::vec3(1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(-1.0f,  0.0f,  0.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f,  1.0f,  0.0f), glm::vec3(0.0f,  0.0f,  1.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f, -1.0f,  0.0f), glm::vec3(0.0f,  0.0f, -1.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f,  0.0f,  1.0f), glm::vec3(0.0f, -1.0f,  0.0f)),
			glm::lookAt(glm::vec3(0.0f), glm::vec3(0.0f,  0.0f, -1.0f), glm::vec3(0.0f, -1.0f,  0.0f))
		};
	
	static glm::mat4 captureProjection = glm::perspective(glm::radians(90.0f), 1.0f, 0.1f, 10.0f);

	
	void OpenGLRenderer::DrawIndexed(/*const IndexedModel& model*/)
	{

	}

	static void LogGLErrors(const std::string& context)
	{
		GLenum error;
		while ((error = glGetError()) != GL_NO_ERROR)
		{
			std::string errorString;
			switch (error)
			{
			case GL_INVALID_ENUM:                  errorString = "GL_INVALID_ENUM"; break;
			case GL_INVALID_VALUE:                 errorString = "GL_INVALID_VALUE"; break;
			case GL_INVALID_OPERATION:             errorString = "GL_INVALID_OPERATION"; break;
			case GL_STACK_OVERFLOW:                errorString = "GL_STACK_OVERFLOW"; break;
			case GL_STACK_UNDERFLOW:               errorString = "GL_STACK_UNDERFLOW"; break;
			case GL_OUT_OF_MEMORY:                 errorString = "GL_OUT_OF_MEMORY"; break;
			case GL_INVALID_FRAMEBUFFER_OPERATION: errorString = "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
			default:                               errorString = "UNKNOWN_ERROR"; break;
			}

			std::cerr << "OpenGL Error in " << context << ": " << errorString << " (" << error << ")" << std::endl;
		}
	}

	void OpenGLRenderer::InitSkybox()
	{
		glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);

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

		// determine size and mip-levels
		unsigned int faceWidth = _skybox->GetResolution();
		unsigned int faceHeight = _skybox->GetResolution();
		unsigned int maxDim = std::max(faceWidth, faceHeight);
		unsigned int maxMipLevels = static_cast<unsigned int>(std::floor(std::log2(static_cast<float>(maxDim)))) + 1;

		// allocate full mip chain
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_BASE_LEVEL, 0);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_MAX_LEVEL, static_cast<GLint>(maxMipLevels - 1));
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTextureParameteri(_skyboxTextureObj, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glTextureStorage2D(_skyboxTextureObj, static_cast<GLsizei>(maxMipLevels), GL_RGB16F, static_cast<GLint>(faceWidth),
			static_cast<GLint>(faceHeight));

		for (int i = 0; i < 6; ++i) {
			const void* pSrc = _skybox->GetCubemapTextures()[i].GetPixels();
			glTextureSubImage3D(_skyboxTextureObj,
				0,      // mipmap level
				0,      // xOffset
				0,      // yOffset
				i,      // zOffset (layer)
				static_cast<GLsizei>(faceWidth), static_cast<GLsizei>(faceHeight),   // 2D image dimensions
				1,          // depth
				GL_RGB,     // format
				GL_FLOAT,   // data type
				pSrc);
		}

		glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureObj);
		glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}

	void OpenGLRenderer::PrefilterEnvironmentMap()
	{
		constexpr GLuint prefilterSize = 256;
		glGenTextures(1, &_prefilteredMapObj);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _prefilteredMapObj);

		_prefilteredMapMaxMipLevels = static_cast<unsigned int>(std::floor(std::log2(static_cast<float>(prefilterSize)))) + 1;
		glTexStorage2D(GL_TEXTURE_CUBE_MAP, static_cast<GLsizei>(_prefilteredMapMaxMipLevels), GL_RGB16F, prefilterSize, prefilterSize);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureObj);

		glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

		GLuint captureFBO = 0;
		GLuint captureRBO = 0;
		glGenFramebuffers(1, &captureFBO);
		glGenRenderbuffers(1, &captureRBO);

		glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
		glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, prefilterSize, prefilterSize);
		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, captureRBO);

		Shader* prefilterShader = Shader::LoadShaders("../res/shaders/skybox_prefilter");
		prefilterShader->Bind();
		prefilterShader->SetUniformTextureSampler2D("u_environmentMap", 0);
		prefilterShader->SetUniform("u_projection", captureProjection);
		prefilterShader->SetUniform("u_envResolution", _skybox->GetResolution());

		GLint prevViewport[4];
		glGetIntegerv(GL_VIEWPORT, prevViewport);

		for (unsigned int mip = 0; mip < _prefilteredMapMaxMipLevels; ++mip)
		{
			GLsizei mipWidth = static_cast<GLsizei>(std::max(1u, prefilterSize >> mip));

			glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
			glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, mipWidth, mipWidth);

			glViewport(0, 0, mipWidth, mipWidth);

			float roughness = static_cast<float>(mip) / static_cast<float>(_prefilteredMapMaxMipLevels - 1);
			prefilterShader->SetUniform("u_roughness", roughness);

			glBindVertexArray(_skyboxCubeVAO);
			for (unsigned int i = 0; i < 6; ++i)
			{
				prefilterShader->SetUniform("u_view", captureViews[i]);
				glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, skyboxFaceTypes[i], _prefilteredMapObj, (GLint)mip);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glDrawArrays(GL_TRIANGLES, 0, 36);
			}
		}

		glBindVertexArray(0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);

		glDeleteFramebuffers(1, &captureFBO);
		glDeleteRenderbuffers(1, &captureRBO);

		delete prefilterShader;
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
				
		Shader* convShader = Shader::LoadShaders("../res/shaders/skybox_irradiance_conv");
		convShader->Bind();
		convShader->SetUniformTextureSampler2D("environmentMap", 0);
		convShader->SetUniform("u_projection", captureProjection);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureObj);

		GLint view[4];
		glGetIntegerv(GL_VIEWPORT, view);
		glViewport(0, 0, irradianceSize, irradianceSize);
		glBindVertexArray(_skyboxCubeVAO);
		for (unsigned int i = 0; i < 6; ++i)
		{
			convShader->SetUniform("u_view", captureViews[i]);
			glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, skyboxFaceTypes[i], _irradianceMapTextureObj, 0);
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


		for (MeshBufferDataInfo& info : meshBufferDataTypes) {
			LoadVertexAttributeArray(info, *mr);
		}

		glBindVertexArray(0);

		mesh._buffered = true;
	}

	void OpenGLRenderer::DrawBRDFLUT()
	{
		glGenTextures(1, &_brdfLUTTextureObj);

		// pre-allocate enough memory for the LUT texture.
		glBindTexture(GL_TEXTURE_2D, _brdfLUTTextureObj);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RG16F, 512, 512, 0, GL_RG, GL_FLOAT, 0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		GLuint captureFBO = 0;
		GLuint captureRBO = 0;
		glGenFramebuffers(1, &captureFBO);
		glGenRenderbuffers(1, &captureRBO);

		glBindFramebuffer(GL_FRAMEBUFFER, captureFBO);
		glBindRenderbuffer(GL_RENDERBUFFER, captureRBO);
		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, 512, 512);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, _brdfLUTTextureObj, 0);

		GLint prevViewport[4];
		glGetIntegerv(GL_VIEWPORT, prevViewport);
		glViewport(0, 0, 512, 512);
		Shader* brdfShader = Shader::LoadShaders("../res/shaders/brdf_lut_gen");
		brdfShader->Bind();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		RenderQuad();

		glBindVertexArray(0);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glDeleteFramebuffers(1, &captureFBO);
		glDeleteRenderbuffers(1, &captureRBO);
		glViewport(prevViewport[0], prevViewport[1], prevViewport[2], prevViewport[3]);
	}

	void OpenGLRenderer::RenderQuad()
	{
		static GLuint quadVAO = 0;
		static GLuint quadVBO = 0;
		if (quadVAO == 0)
		{
			float quadVertices[] = {
				-1.0f, -1.0f,
				 1.0f, -1.0f,
				-1.0f,  1.0f,

				-1.0f,  1.0f,
				 1.0f, -1.0f,
				 1.0f,  1.0f
			};

			glGenVertexArrays(1, &quadVAO);
			glGenBuffers(1, &quadVBO);
			glBindVertexArray(quadVAO);
			glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), quadVertices, GL_STATIC_DRAW);
			glEnableVertexAttribArray(0);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
			glBindVertexArray(0);
		}

		glBindVertexArray(quadVAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	}

	void OpenGLRenderer::LoadVertexAttributeArray(MeshBufferDataInfo& info, MeshRenderer& mr)
	{
		int location = -1;
		if (info.position != INDEX_VB) {
			location = mr.GetAttributeLocation(info.attributeName);
			if (location < 0 )
				return; // index does not use program attribute location
		}

		MeshData& mesh = mr.GetModel()->mesh;

		glBindBuffer(GL_ARRAY_BUFFER, mesh.m_vertexArrayBuffers[info.position]);
		GLsizei attributeSize;
		switch (info.position) {
		case POSITION_VB:
			if (mesh.m_Positions.empty()) return;
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_Positions[0]) * mesh.m_Positions.size(), &mesh.m_Positions[0], GL_STATIC_DRAW);
			attributeSize = 3;
			break;
		case TEXCOORD_VB:
			if (mesh.m_TexCoords.empty()) return;	
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_TexCoords[0]) * mesh.m_TexCoords.size(), &mesh.m_TexCoords[0], GL_STATIC_DRAW);
			attributeSize = 2;
			break;
		case NORMAL_VB:
			if (mesh.m_Normals.empty()) return;
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_Normals[0]) * mesh.m_Normals.size(), &mesh.m_Normals[0], GL_STATIC_DRAW);
			attributeSize = 3;
			break;
		case TANGENT_VB:
			if (mesh.m_Tangents.empty()) return;
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_Tangents[0]) * mesh.m_Tangents.size(), &mesh.m_Tangents[0], GL_STATIC_DRAW);
			attributeSize = 3;
			break;
		case BITANGENT_VB:
			if (mesh.m_Bitangents.empty()) return;
			glBufferData(GL_ARRAY_BUFFER, sizeof(mesh.m_Bitangents[0]) * mesh.m_Bitangents.size(), &mesh.m_Bitangents[0], GL_STATIC_DRAW);
			attributeSize = 3;
			break;
		case INDEX_VB:
			if (mesh.m_Indices.empty()) return;
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.m_vertexArrayBuffers[info.position]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(mesh.m_Indices[0]) * mesh.m_Indices.size(), &mesh.m_Indices[0], GL_STATIC_DRAW);
			return;
		default:
			return;
		}
		glEnableVertexAttribArray(location);
		glVertexAttribPointer(location, attributeSize, GL_FLOAT, GL_FALSE, 0, 0);

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

			skyboxShader->SetUniform("u_view", viewNoTranslation);
			skyboxShader->SetUniform("u_projection", proj);

			// Bind cubemap texture to unit 0 and point shader sampler to unit 0.
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, _skyboxTextureObj);
			// Use your shader helper to set an int sampler uniform; fallback to glUniform1i if necessary:
			skyboxShader->SetUniformTextureSampler2D("u_skybox", 0); // or SetUniform("u_skybox", 0)
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
		PrefilterEnvironmentMap();
		DrawBRDFLUT();
		// debug
		//_skyboxTextureObj = _prefilteredMapObj;
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
		glm::mat4 mvp = Application::renderer->GetRenderCamera().GetViewProjection() * umodel;
		glm::vec3 camPos = Application::renderer->GetRenderCamera().GetPos();

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
				shader->SetUniform("u_prefilteredMapMaxLOD", _prefilteredMapMaxMipLevels - 1);

				// lights
				unsigned int lightCount = 0;
				std::vector<glm::vec3> lightDirs;
				std::vector<glm::vec3> lightColors;
				if (!Application::lightPresets.empty() && std::cmp_less(Application::activeLightPresetIndex, Application::lightPresets.size()))
				{
					lightCount = static_cast<unsigned int>(Application::lightPresets[Application::activeLightPresetIndex].size());

					for (unsigned int i = 0; i < lightCount; ++i)
					{
						lightDirs.push_back(Application::lightPresets[Application::activeLightPresetIndex][i].GetDirection());
						lightColors.push_back(Application::lightPresets[Application::activeLightPresetIndex][i].GetColor());
					}
				}

				shader->SetUniform("u_nLights", lightCount);
				shader->SetUniformArray("u_lightDirs", lightDirs, MAX_LIGHTS);
				shader->SetUniformArray("u_lightDiffs", lightColors, MAX_LIGHTS);

				glActiveTexture(GL_TEXTURE0);
				glBindTexture(GL_TEXTURE_CUBE_MAP, _irradianceMapTextureObj);
				shader->SetUniformCubeSampler("u_irradianceMap", 0);

				glActiveTexture(GL_TEXTURE1);
				glBindTexture(GL_TEXTURE_CUBE_MAP, _prefilteredMapObj);
				shader->SetUniformCubeSampler("u_prefilteredMap", 1);

				glActiveTexture(GL_TEXTURE2);
				glBindTexture(GL_TEXTURE_2D, _brdfLUTTextureObj);
				shader->SetUniformTextureSampler2D("u_brdfLUT", 2);

				// Bind albedo (base) to texture unit 0
				// TODO: hardcoded texture unit indexes, also make functions for redundant uniform setting
				auto* albedoTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_BASE];
				if (albedoTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::BASE_TEXTURE)) {
					albedoTex->Bind(3);
					shader->SetUniformTextureSampler2D("u_albedoMap", 3);
				}

				 //Bind normal map to texture unit 1
				auto* normalTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_NORMAL];
				if (normalTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::NORMAL_MAPS)) {
					normalTex->Bind(4);
					shader->SetUniformTextureSampler2D("u_normalMap", 4);
				}

				auto* roughnessTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_ROUGHNESS];
				if (roughnessTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::ROUGHNESS_MAPS)) {
					roughnessTex->Bind(5);
					shader->SetUniformTextureSampler2D("u_roughnessMap", 5);
				}

				auto* metalnessTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_METALLIC];
				if (metalnessTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::METALNESS_MAPS)) {
					metalnessTex->Bind(6);
					shader->SetUniformTextureSampler2D("u_metalnessMap", 6);
				}

				auto* aoTex = model->materials[bm.materialIndex]->m_textures[TEX_TYPE_AO];
				if (aoTex && mr->m_render_flags[bm.materialIndex] & static_cast<uint32_t>(RenderFlags::AO_MAPS)) {
					aoTex->Bind(7);
					shader->SetUniformTextureSampler2D("u_aoMap", 7);
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
					LogGLErrors("glDrawElementsBaseVertex");
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

		for (int i = 0; i < 16; ++i) // Assuming 16 texture units (adjust if needed)
		{
			glActiveTexture(GL_TEXTURE0 + i);
			glBindTexture(GL_TEXTURE_2D, 0);
			glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
		}
		glBindVertexArray(0);
	}

}
