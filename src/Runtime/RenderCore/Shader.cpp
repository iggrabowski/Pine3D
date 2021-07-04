#pragma once
#include "Runtime/RenderCore/Shader.h"
#include "Runtime/Renderer/Renderer.h"

#include <iostream>
#include <fstream>

namespace Pine {

    extern UniquePtr<Renderer> renderer;

    //Credit: https://github.com/JoeyDeVries/Cell/blob/master/cell/shading/shader.cpp
    Shader::Shader(std::string name, std::string vsCode, std::string fsCode)
    {
        m_Shaders[VERTEX_SHADER] = glCreateShader(GL_VERTEX_SHADER);
        m_Shaders[FRAGMENT_SHADER] = glCreateShader(GL_FRAGMENT_SHADER);
        m_Program = glCreateProgram();

        const char* vsSourceC = vsCode.c_str();
        const char* fsSourceC = fsCode.c_str();

        glShaderSource(m_Shaders[VERTEX_SHADER], 1, &vsSourceC, NULL);
        glShaderSource(m_Shaders[FRAGMENT_SHADER], 1, &fsSourceC, NULL);

        glCompileShader(m_Shaders[VERTEX_SHADER]);
        glCompileShader(m_Shaders[FRAGMENT_SHADER]);

        CheckShaderError(m_Shaders[VERTEX_SHADER], GL_COMPILE_STATUS, false, "Error compiling shader!");
        CheckShaderError(m_Shaders[FRAGMENT_SHADER], GL_COMPILE_STATUS, false, "Error compiling shader!");

        glAttachShader(m_Program, m_Shaders[VERTEX_SHADER]);
        glAttachShader(m_Program, m_Shaders[FRAGMENT_SHADER]);
        glLinkProgram(m_Program);

        CheckShaderError(m_Program, GL_LINK_STATUS, true, "Error linking shader program");

        // query the number of active uniforms and attributes
        GLint nrAttributes, nrUniforms;
        glGetProgramiv(m_Program, GL_ACTIVE_ATTRIBUTES, &nrAttributes);
        glGetProgramiv(m_Program, GL_ACTIVE_UNIFORMS, &nrUniforms);
        Attributes.resize(nrAttributes);
        Uniforms.resize(nrUniforms);

        // iterate over all active attributes
        char buffer[128];
        for (unsigned int i = 0; i < nrAttributes; ++i)
        {
            glGetActiveAttrib(m_Program, i, sizeof(buffer), 0, &Attributes[i].Size, &Attributes[i].Type, buffer);
            Attributes[i].Name = std::string(buffer);

            Attributes[i].Location = glGetAttribLocation(m_Program, buffer);
        }

        // iterate over all active uniforms
        for (unsigned int i = 0; i < nrUniforms; ++i)
        {
            GLenum glType;
            glGetActiveUniform(m_Program, i, sizeof(buffer), 0, &Uniforms[i].Size, &Uniforms[i].Type, buffer);
            Uniforms[i].Name = std::string(buffer);

            Uniforms[i].Location = glGetUniformLocation(m_Program, buffer);
        }
    }

    Shader::~Shader()
    {
        for (unsigned int i = 0; i < NUMBER_OF_SHADERS; i++)
        {
            glDetachShader(m_Program, m_Shaders[i]);
            glDeleteShader(m_Shaders[i]);
        }

        glDeleteProgram(m_Program);
    }

    void Shader::SetUniform(std::string name, Mat4& val)
    {
        int loc = GetUniformLocation(name);
        if (loc >= 0) {
            glUniformMatrix4fv(loc, 1, GL_FALSE, &val[0][0]);
        }
    }

    void Shader::SetUniform(std::string name, Vec3& val)
    {
        int loc = GetUniformLocation(name);
        if (loc >= 0) {
            glUniform3fv(loc, 1, &val[0]);
        }
    }

    bool Shader::GetAttributeLocation(std::string name, unsigned int& outLoc)
    {
        for (unsigned int i = 0; i < Attributes.size(); ++i)
        {
            if (Attributes[i].Name == name) {
                outLoc =  Attributes[i].Location;
                return true;
            }
        }
        std::cout << "ERROR: Attribute: \"" << name << "\" not found in the program " << m_Program << std::endl;
        return false;
    }

    void Shader::Bind()
    {
        glUseProgram(m_Program);
    }

    Shader* Shader::LoadShader(const std::string& fileName)
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
        for (unsigned int i = 0; i < Uniforms.size(); ++i)
        {
            if (Uniforms[i].Name == name)
                return Uniforms[i].Location;
        }
        std::cout << "ERROR: Uniform: \"" << name << "\" not found in the program " << m_Program << std::endl;
        return -1;
    }
}