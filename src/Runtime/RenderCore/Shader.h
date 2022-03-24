#pragma once
#include "Runtime/Components/Transform.h"
#include "Runtime/Camera/Camera.h"
#include "Utils/Utils.h"

#include <string>

namespace Pine {

	enum SHADER_TYPE
	{
		VERTEX_SHADER,
		FRAGMENT_SHADER,
		NUMBER_OF_SHADERS
	};

	struct ShaderVariable
	{
		unsigned int	Type;
		std::string		Name;
		int				Size;
		unsigned int	Location;
	};

	class Shader
	{
	public:
		Shader(std::string name, std::string vsCode, std::string fsCode);
		~Shader();

		void Bind();

		void SetUniform(std::string name, Vec3& val);
		void SetUniform(std::string name, Mat4& val);
		bool GetAttributeLocation(std::string name, unsigned int& outLoc);

		static Shader* LoadShader(const std::string& fileName);
	protected:
	private:
		std::vector<ShaderVariable>	Uniforms;
		std::vector<ShaderVariable>	Attributes;

		static void ReadShader(const std::string fileName, std::string& outCode);

		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);

		int GetUniformLocation(std::string name);

		GLuint m_Program;
		GLuint m_Shaders[NUMBER_OF_SHADERS];
	};

}
