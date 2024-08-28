#include "Shader.hpp"
#include <iostream>

namespace kirei {

Shader::Shader(const std::string& vertexSrc, const std::string& fragmentSrc) {
    GLuint vertexShader = compileShader(GL_VERTEX_SHADER, vertexSrc);
    GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, fragmentSrc);

    m_shaderProgram = glCreateProgram();
    glAttachShader(m_shaderProgram, vertexShader);
    glAttachShader(m_shaderProgram, fragmentShader);
    glLinkProgram(m_shaderProgram);

    GLint isLinked;
    glGetProgramiv(m_shaderProgram, GL_LINK_STATUS, &isLinked);
    if (!isLinked) {
        GLchar infoLog[1024];
        glGetProgramInfoLog(m_shaderProgram, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Error linking shader program: " << infoLog << std::endl;
        glDeleteProgram(m_shaderProgram);
        throw std::runtime_error("Failed to link shader program");
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    glDeleteProgram(m_shaderProgram);
}

void Shader::bind() const {
    glUseProgram(m_shaderProgram);
}

void Shader::unbind() const {
    glUseProgram(0);
}

GLuint Shader::compileShader(GLenum type, const std::string& source) {
    GLuint shader = glCreateShader(type);
    const GLchar* src = source.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);

    GLint isCompiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
        GLchar infoLog[1024];
        glGetShaderInfoLog(shader, sizeof(infoLog), nullptr, infoLog);
        std::cerr << "Error compiling " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << " shader: " << infoLog << std::endl;
        glDeleteShader(shader);
        throw std::runtime_error("Failed to compile shader");
    }

    return shader;
}

}