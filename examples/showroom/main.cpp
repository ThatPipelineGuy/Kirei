#include "../../src/window/Window.hpp"
#include "../../src/input/Input.hpp"
#include "../../src/renderer/Renderer.hpp"
#include "../../src/renderer/Shader.hpp"
#include <iostream>
#include <format>

const std::string vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    void main() {
        gl_Position = vec4(aPos, 1.0);
    }
)";

const std::string fragmentShaderSource = R"(
    #version 330 core
    out vec4 FragColor;
    void main() {
        FragColor = vec4(1.0, 0.5, 0.2, 1.0);
    }
)";

int main() {
    try {
        kirei::Window window(800, 600, "Kirei App");
        kirei::Renderer renderer;

        kirei::Shader shader(vertexShaderSource, fragmentShaderSource);
        shader.bind();

        // Handle resize events
        window.onResize([](int width, int height) {
            glViewport(0, 0, width, height);
            std::cout << std::format("Window resized: {}x{}\n", width, height);
        });

        // Main loop
        while (!window.shouldClose()) {
            renderer.clear();
            renderer.setClearColor(0.1f, 0.1f, 0.1f, 1.0f);

            // Render using the shader
            shader.bind();
            renderer.draw();  // TODO: Placeholder draw call

            window.update();
        }
    } catch (const std::exception& e) {
        std::cerr << std::format("Error: {}\n", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}