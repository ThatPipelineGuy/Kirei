#include "Window.hpp"
#include "Input.hpp"
#include <iostream>
#include <format>

int main() {
    try {
        kirei::Window window(800, 600, "Kirei App");

        // Handle resize events
        window.onResize([](int width, int height) {
            glViewport(0, 0, width, height);
            std::cout << std::format("Window resized: {}x{}\n", width, height);
        });

        // Handle key press events
        kirei::Input::instance().registerKeyCallback(window.getGLFWwindow(), [](int key, int scancode, int action, int mods) {
            std::cout << std::format("Key event: Key={}, Action={}\n", key, action);
        });

        // Main loop
        while (!window.shouldClose()) {
            window.update();
        }
    } catch (const std::exception& e) {
        std::cerr << std::format("Error: {}\n", e.what());
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}