#include "Renderer.hpp"

namespace kirei {

Renderer::Renderer() {
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    std::cout << "OpenGL initialized with GLAD\n";
}

Renderer::~Renderer() {
    // TODO: Cleanup if needed; OpenGL itself does not need a destructor
}

void Renderer::clear() const {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::setClearColor(float r, float g, float b, float a) const {
    glClearColor(r, g, b, a);
}

void Renderer::draw() const {
    // TODO: Placeholder draw function; can be extended to draw VAOs, etc.
    glDrawArrays(GL_TRIANGLES, 0, 3);  // Example: draw 3 vertices as a triangle
}

}