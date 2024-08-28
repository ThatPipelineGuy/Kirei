#include "Window.hpp"
#include "../core/Context.hpp"  // Include context to ensure GLFW is initialized
#include <iostream>
#include <stdexcept>
#include <format>  // C++20 for formatted strings

namespace kirei {

Window::Window(int width, int height, const std::string& title) 
    : m_width(width), m_height(height), m_title(title) {

    Context::instance();  // Ensure GLFW context is initialized

    // Set GLFW window hints (can be customized)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        throw std::runtime_error(std::format("Failed to create GLFW window: {}", title));
    }

    glfwMakeContextCurrent(m_window);
    std::cout << std::format("Window created: {} ({}x{})\n", title, width, height);
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        std::cout << std::format("Window destroyed: {}\n", m_title);
    }
}

bool Window::shouldClose() const {
    return glfwWindowShouldClose(m_window);
}

void Window::update() {
    glfwSwapBuffers(m_window);
    glfwPollEvents();
}

Window& Window::onResize(std::function<void(int, int)> callback) {
    glfwSetFramebufferSizeCallback(m_window, [callback = std::move(callback)](GLFWwindow*, int width, int height) {
        callback(width, height);
    });
    return *this;
}

GLFWwindow* Window::getGLFWwindow() const {
    return m_window;
}

}