#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace kirei {

class Renderer {
public:
    Renderer();
    ~Renderer();

    void clear() const;
    void setClearColor(float r, float g, float b, float a) const;
    void draw() const;  // TODO: we will extend this to draw VAOs, etc.

    // No copying or moving
    Renderer(const Renderer&) = delete;
    Renderer& operator=(const Renderer&) = delete;
    Renderer(Renderer&&) = delete;
    Renderer& operator=(Renderer&&) = delete;
};

}