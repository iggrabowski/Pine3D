#pragma once
#include "Runtime/Components/Transform.h"
#include "Runtime/Camera/Camera.h"
#include "Utils/Utils.h"

#include <string>

namespace pine {

	enum SHADER_TYPE
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		NUM_OF_SHADERS
	};

	struct ShaderVariable
	{
		unsigned int	type;
		std::string		name;
		int				size;
		unsigned int	loc;
	};

	class Shader
	{
	public:
		Shader(std::string name, std::string vsCode, std::string fsCode);
		~Shader();

		void Bind();

		void SetUniform(std::string name, glm::vec3& val);
		void SetUniform(std::string name, glm::mat4& val);
		bool GetAttributeLocation(std::string name, unsigned int& outLoc);

		static Shader* LoadShaders(const std::string& fileName);
	protected:
	private:
		std::vector<ShaderVariable>	_uniforms;
		std::vector<ShaderVariable>	_attributes;

		static void ReadShader(const std::string fileName, std::string& outCode);

		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

		int GetUniformLocation(std::string name);

		GLuint _program;
		GLuint _shaders[NUM_OF_SHADERS];
	};

}
