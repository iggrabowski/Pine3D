#pragma once
#include "Runtime/RenderCore/Shader.h"
#include "Runtime/Renderer/Renderer.h"
#include "Utils/Logger.h"
#include <iostream>
#include <fstream>

namespace pine {

    extern UniquePtr<Renderer> renderer;

    //Credit: https://github.com/JoeyDeVries/Cell/blob/master/cell/shading/shader.cpp
    Shader::Shader(std::string name, std::string vsCode, std::string fsCode)
    {
        _shaders[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
        _shaders[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);
        _program = glCreateProgram();

        const char* vsSourceC = vsCode.c_str();
        const char* fsSourceC = fsCode.c_str();

        glShaderSource(_shaders[VERTEX_SHADER], 1, &vsSourceC, NULL);
        glShaderSource(_shaders[FRAGMENT_SHADER], 1, &fsSourceC, NULL);

        glCompileShader(_shaders[VERTEX_SHADER]);
        glCompileShader(_shaders[FRAGMENT_SHADER]);

        CheckShaderError(_shaders[VERTEX_SHADER], GL_COMPILE_STATUS, false, "Error compiling shader!");
        CheckShaderError(_shaders[FRAGMENT_SHADER], GL_COMPILE_STATUS, false, "Error compiling shader!");

        glAttachShader(_program, _shaders[VERTEX_SHADER]);
        glAttachShader(_program, _shaders[FRAGMENT_SHADER]);
        glLinkProgram(_program);

        CheckShaderError(_program, GL_LINK_STATUS, true, "Error linking shader program");

        // query the number of active uniforms and attributes
        GLint nrAttributes, nrUniforms;
        glGetProgramiv(_program, GL_ACTIVE_ATTRIBUTES, &nrAttributes);
        glGetProgramiv(_program, GL_ACTIVE_UNIFORMS, &nrUniforms);
        _attributes.resize(nrAttributes);
        _uniforms.resize(nrUniforms);

        // iterate over all active attributes
        char buffer[128];
        for (int i = 0; i < nrAttributes; ++i)
        {
            glGetActiveAttrib(_program, i, sizeof(buffer), 0, &_attributes[i].size, &_attributes[i].type, buffer);
            _attributes[i].name = std::string(buffer);

            _attributes[i].loc = glGetAttribLocation(_program, buffer);
        }

        // iterate over all active uniforms
        for (int i = 0; i < nrUniforms; ++i)
        {
            //GLenum glType;
            glGetActiveUniform(_program, i, sizeof(buffer), 0, &_uniforms[i].size, &_uniforms[i].type, buffer);
            _uniforms[i].name = std::string(buffer);

            _uniforms[i].loc = glGetUniformLocation(_program, buffer);
        }
    }

    Shader::~Shader()
    {
        for (unsigned int i = 0; i < NUM_OF_SHADERS; i++)
        {
            glDetachShader(_program, _shaders[i]);
            glDeleteShader(_shaders[i]);
        }

        glDeleteProgram(_program);
    }

    void Shader::SetUniform(std::string name, glm::mat4& val)
    {
        int loc = GetUniformLocation(name);
        if (loc >= 0) {
            glUniformMatrix4fv(loc, 1, GL_FALSE, &val[0][0]);
			Logger::Instance().Info("SHADER: Added value to uniform" + name);
        }
    }

    void Shader::SetUniform(std::string name, glm::vec3& val)
    {
        int loc = GetUniformLocation(name);
        if (loc >= 0) {
            glUniform3fv(loc, 1, &val[0]);
        }
    }

    bool Shader::GetAttributeLocation(std::string name, unsigned int& outLoc)
    {
        for (unsigned int i = 0; i < _attributes.size(); ++i)
        {
            if (_attributes[i].name == name) {
                outLoc =  _attributes[i].loc;
                return true;
            }
        }
        std::cout << "ERROR: Attribute: \"" << name << "\" not found in the program " << _program << std::endl;
        return false;
    }

    void Shader::Bind()
    {
        glUseProgram(_program);
    }

    Shader* Shader::LoadShaders(const std::string& fileName)
    {
        std::string vsCode;
        std::string fsCode;

        std::string vsFileName = fileName + ".vs";
        ReadShader(vsFileName, vsCode);

        std::string fsFileName = fileName + ".fs";
        ReadShader(fsFileName, fsCode);
        
        return new Shader(fileName, vsCode, fsCode);
    }

    void Shader::ReadShader(const std::string fileName, std::string& outCode) {

        std::ifstream File;
        File.open((fileName).c_str());

        std::string line;
        if (File.is_open())
        {
            while (File.good())
            {
                getline(File, line);
                outCode.append(line + "\n");
            }
        }
        else
        {
            std::cerr << "Unable to load shader." << std::endl;
        }
        File.close();
    }

    void Shader::CheckShaderError(GLuint shader, GLuint flag, bool isProgram, const std::string& errorMessage)
    {
        GLint success = 0;
        GLchar error[1024] = { 0 };

        if (isProgram)
            glGetProgramiv(shader, flag, &success);
        else
            glGetShaderiv(shader, flag, &success);

        if (success == GL_FALSE)
        {
            if (isProgram)
                glGetProgramInfoLog(shader, sizeof(error), NULL, error);
            else
                glGetShaderInfoLog(shader, sizeof(error), NULL, error);

            std::cerr << errorMessage << ": '" << error << "'" << std::endl;
        }
    }

    //Credit: https://github.com/JoeyDeVries/Cell/blob/master/cell/shading/shader.cpp
    int Shader::GetUniformLocation(std::string name)
    {
        // read from uniform/attribute array as originally obtained from OpenGL
        for (unsigned int i = 0; i < _uniforms.size(); ++i)
        {
            if (_uniforms[i].name == name)
                return _uniforms[i].loc;
        }
        std::cout << "ERROR: Uniform: \"" << name << "\" not found in the program " << _program << std::endl;
        return -1;
    }
}