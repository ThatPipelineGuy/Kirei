#pragma once

#include <glad/glad.h>
#include <string>
#include <stdexcept>

namespace kirei {

class Shader {
public:
    Shader(const std::string& vertexSrc, const std::string& fragmentSrc);
    ~Shader();

    void bind() const;
    void unbind() const;

    // No copying or moving
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;
    Shader(Shader&&) = delete;
    Shader& operator=(Shader&&) = delete;

private:
    GLuint m_shaderProgram;

    GLuint compileShader(GLenum type, const std::string& source);
};

}