//Taken from learnopengl.com

#ifndef SHADER_H
#define SHADER_H

#include "OpenGL_Includer.h"
#include "glm/glm.hpp"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
public:
	unsigned int ID;
	// constructor generates the shader on the fly
	// ------------------------------------------------------------------------

	//vert and frag shader
	Shader(const char* vertexPath, const char* fragmentPath)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			std::stringstream vShaderStream, fShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
		}
		catch (const std::ifstream::failure &e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			return;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
	}

	//fragment Shader
	Shader(const char* fragmentPath)
	{
		// 1. retrieve the fragment source code from filePath
		std::string fragmentCode;
		std::ifstream fShaderFile;
		// ensure ifstream objects can throw exceptions:
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			fShaderFile.open(fragmentPath);
			std::stringstream fShaderStream;
			// read file's buffer contents into streams
			fShaderStream << fShaderFile.rdbuf();
			// close file handlers
			fShaderFile.close();
			// convert stream into string
			fragmentCode = fShaderStream.str();
		}
		catch (const std::ifstream::failure &e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			return;
		}

		const char * fShaderCode = fragmentCode.c_str();
		// 2. compile shader
		unsigned int fragment;
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");
		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, fragment);
		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shader as they're linked into our program now and no longer necessary
		glDeleteShader(fragment);
	}


	//vert, frag shader, and geom shader
	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* Name[] = nullptr)
	{
		// 1. retrieve the vertex/fragment source code from filePath
		std::string vertexCode;
		std::string fragmentCode;
		std::string geometryCode;
		std::ifstream vShaderFile;
		std::ifstream fShaderFile;
		std::ifstream gShaderFile;
		// ensure ifstream objects can throw exceptions:
		vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		gShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			vShaderFile.open(vertexPath);
			fShaderFile.open(fragmentPath);
			gShaderFile.open(geometryPath);
			std::stringstream vShaderStream, fShaderStream, gShaderStream;
			// read file's buffer contents into streams
			vShaderStream << vShaderFile.rdbuf();
			fShaderStream << fShaderFile.rdbuf();
			gShaderStream << gShaderFile.rdbuf();
			// close file handlers
			vShaderFile.close();
			fShaderFile.close();
			gShaderFile.close();
			// convert stream into string
			vertexCode = vShaderStream.str();
			fragmentCode = fShaderStream.str();
			geometryCode = gShaderStream.str();
		}
		catch (const std::ifstream::failure &e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			return;
		}

		const char* vShaderCode = vertexCode.c_str();
		const char * fShaderCode = fragmentCode.c_str();
		const char * gShaderCode = geometryCode.c_str();
		// 2. compile shaders
		unsigned int vertex, fragment, geometry;
		// vertex shader
		vertex = glCreateShader(GL_VERTEX_SHADER);
		glShaderSource(vertex, 1, &vShaderCode, NULL);
		glCompileShader(vertex);
		checkCompileErrors(vertex, "VERTEX");
		// fragment Shader
		fragment = glCreateShader(GL_FRAGMENT_SHADER);
		glShaderSource(fragment, 1, &fShaderCode, NULL);
		glCompileShader(fragment);
		checkCompileErrors(fragment, "FRAGMENT");

		//geometry Shader
		geometry = glCreateShader(GL_GEOMETRY_SHADER);
		glShaderSource(geometry, 1, &gShaderCode, NULL);
		glCompileShader(geometry);
		checkCompileErrors(geometry, "FRAGMENT");

		// shader Program
		ID = glCreateProgram();
		glAttachShader(ID, vertex);
		glAttachShader(ID, fragment);
		glAttachShader(ID, geometry);

		if(Name != nullptr)
		{
			//taken from ex16
			for (int k=0;Name[k];k++)
				if (Name[k][0])
					glBindAttribLocation(ID,k,Name[k]);
		}
		


		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shaders as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(fragment);
		glDeleteShader(geometry);
	}


	unsigned int AddShaderPart(unsigned int program, const GLenum type, const char* partPath)
	{
		// 1. retrieve the shader source code from filePath
		std::string code;
		std::ifstream file;
		// ensure ifstream objects can throw exceptions:
		file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
		try
		{
			// open files
			file.open(partPath);
			std::stringstream shaderStream;
			// read file's buffer contents into streams
			shaderStream << file.rdbuf();
			// close file handlers
			file.close();
			// convert stream into string
			code = shaderStream.str();
		}
		catch (const std::ifstream::failure &e)
		{
			std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
			return 0;
		}

		const char* shaderCode = code.c_str();
		// 2. compile shader
		unsigned int shader;
		// fragment Shader
		shader = glCreateShader(type);
		glShaderSource(shader, 1, &shaderCode, NULL);
		glCompileShader(shader);
		checkCompileErrors(shader, partPath);

		//attach
		glAttachShader(program, shader);



		return shader;
	}



	Shader(const char* vertexPath, const char* fragmentPath, const char* geometryPath, const char* tessellationControlPath, const char* tessellationEvaluationPath)
	{
		ID = glCreateProgram();
		unsigned int vertex = AddShaderPart(ID, GL_VERTEX_SHADER, vertexPath);
		unsigned int control = AddShaderPart(ID, GL_TESS_CONTROL_SHADER, tessellationControlPath);
		unsigned int evaluation = AddShaderPart(ID, GL_TESS_EVALUATION_SHADER, tessellationEvaluationPath);
		unsigned int geometry = AddShaderPart(ID, GL_GEOMETRY_SHADER, geometryPath);
		unsigned int fragment = AddShaderPart(ID, GL_FRAGMENT_SHADER, fragmentPath);

		glLinkProgram(ID);
		checkCompileErrors(ID, "PROGRAM");
		// delete the shader as they're linked into our program now and no longer necessary
		glDeleteShader(vertex);
		glDeleteShader(control);
		glDeleteShader(evaluation);
		glDeleteShader(geometry);
		glDeleteShader(fragment);
	}

	~Shader() {
		glDeleteShader(ID);
	}

	// activate the shader
	// ------------------------------------------------------------------------
	void use()
	{
		glUseProgram(ID);
	}
	// utility uniform functions
	// ------------------------------------------------------------------------
	void setBool(const std::string &name, bool value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
	}
	// ------------------------------------------------------------------------
	void setInt(const std::string &name, int value) const
	{
		glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
	void setFloat(const std::string &name, float value) const
	{
		glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
	}
	// ------------------------------------------------------------------------
    void setVec2(const std::string &name, const glm::vec2 &value) const
    { 
        glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec2(const std::string &name, float x, float y) const
    { 
        glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y); 
    }
    // ------------------------------------------------------------------------
    void setVec3(const std::string &name, const glm::vec3 &value) const
    { 
        glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec3(const std::string &name, float x, float y, float z) const
    { 
        glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z); 
    }
    // ------------------------------------------------------------------------
    void setVec4(const std::string &name, const glm::vec4 &value) const
    { 
        glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]); 
    }
    void setVec4(const std::string &name, float x, float y, float z, float w) 
    { 
        glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w); 
    }
    // ------------------------------------------------------------------------
    void setMat2(const std::string &name, const glm::mat2 &mat) const
    {
        glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat3(const std::string &name, const glm::mat3 &mat) const
    {
        glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }
    // ------------------------------------------------------------------------
    void setMat4(const std::string &name, const glm::mat4 &mat) const
    {
        glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
    }


private:
	// utility function for checking shader compilation/linking errors.
	// ------------------------------------------------------------------------
	void checkCompileErrors(unsigned int shader, std::string type)
	{
		int success;
		char infoLog[1024];
		if (type != "PROGRAM")
		{
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
		else
		{
			glGetProgramiv(shader, GL_LINK_STATUS, &success);
			if (!success)
			{
				glGetProgramInfoLog(shader, 1024, NULL, infoLog);
				std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
			}
		}
	}
};
#endif