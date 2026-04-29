#pragma once
#include "Runtime/Components/Transform.h"
#include "Runtime/Camera/Camera.h"
#include "Utils/Utils.h"

#include <string>

#define MAX_LIGHTS 8

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
		std::string	name;
		int				size;
		unsigned int	loc;
	};

	class Shader
	{
	public:
		Shader(std::string name, std::string vsCode, std::string fsCode);
		~Shader();

		void Bind() const;

		void SetUniform(const std::string& name, vec3& val);
		void SetUniformArray(const std::string& name, const std::vector<vec3>& vec, int maxSizeAllowed);
		void SetUniform(const std::string& name, mat4& val);
		void SetUniform(const std::string& name, float val);
		void SetUniform(const std::string& name, unsigned int val);
		void SetUniformTextureSampler2D(const std::string& name, int textureUnit);
		void SetUniformCubeSampler(const std::string& name, int textureUnit);
		bool GetAttributeLocation(const std::string& name, unsigned int& outLoc) const;

		// TODO: implement shader lookup
		static Shader* LoadShaders(const std::string& fileName);
		int GetUniformLocation(std::string name);
		unsigned int GetNumberOfAttributes() const {
			return static_cast<unsigned int>(_attributes.size());
		}
		unsigned int GetNumberOfUniforms()	const {
			return static_cast<unsigned int>(_uniforms.size());
		}

		// Expose const access to attributes so callers can validate/inspect them.
		const std::vector<ShaderVariable>& GetAttributes() const { return _attributes; }

	protected:
	private:
		std::vector<ShaderVariable>	_uniforms;
		std::vector<ShaderVariable>	_attributes;

		static void ReadShader(const std::string fileName, std::string& outCode);

		void CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage);


		GLuint _program;
		GLuint _shaders[NUM_OF_SHADERS];
	};

}
