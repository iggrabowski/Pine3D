#pragma once

#include "Runtime/Renderer/Renderer.h"

namespace pine {
enum RenderColorBufferType {
  SCENE_COLOR_BUFFER = 0,
  BLOOM_COLOR_BUFFER,
  NUM_COLOR_BUFFERS
};

class OpenGLRenderer final : public Renderer {
public:
  OpenGLRenderer();

  void OnUpdate() override;
  void Clear() override;
  void DrawSkybox() override;
  void Startup() override;
  void Draw(MeshRenderer *mr) override;
  void PrefilterEnvironmentMap();
  // void Init() override;
  void BufferModelMesh(MeshRenderer *mr) override;
  void DrawBRDFLUT();
  void RenderQuad();

private:
  std::unique_ptr<Shader> _blurShader;
  std::unique_ptr<Shader> _blendShader;

  void LoadShaders();
  void LoadVertexAttributeArray(MeshBufferDataInfo &info, MeshRenderer &mr);
  void DrawIndexed(/*const IndexedModel& model*/) override;
  void RenderMesh(MeshRenderer *mr);
  void InitSkybox();
  void GenerateIrradianceMap();
  void GenerateFrameBuffers();
  void InitPingPongBuffers();
  void ResizeTexture(GLuint textureID, int width, int height);
  void PostProcessBloom();
  unsigned int _prefilteredMapMaxMipLevels;
  GLuint _skyboxTextureObj;
  GLuint _skyboxCubeVAO;
  GLuint _irradianceMapTextureObj;
  GLuint _prefilteredMapObj;
  GLuint _brdfLUTTextureObj;
  GLuint _renderFrameCBO[NUM_COLOR_BUFFERS];
  GLuint _captureFBO;
  GLuint _pingpongFBO[2];
  GLuint _pingpongCBO[2];
};

} // namespace pine
