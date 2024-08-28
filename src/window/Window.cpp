#include "Window.hpp"
#include <iostream>
#include <stdexcept>
#include <format>

namespace kirei {

Window::Window(int width, int height, const std::string& title) 
    : m_width(width), m_height(height), m_title(title) {

    if (!glfwInit()) {
        throw std::runtime_error("Please initialize a kirei::Context first.");
    }

    // Set GLFW window hints (can be customized)
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create the window
    m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
    if (!m_window) {
        throw std::runtime_error(std::format("Failed to create Kirei window: {}", title));
    }

    glfwMakeContextCurrent(m_window);
    std::cout << std::format("Kirei Window created: {} ({}x{})\n", title, width, height);
}

Window::~Window() {
    if (m_window) {
        glfwDestroyWindow(m_window);
        std::cout << std::format("Kirei Window destroyed: {}\n", m_title);
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
    m_resizeCallback = std::move(callback);  // Store the callback

    // Register the static callback with GLFW
    glfwSetFramebufferSizeCallback(m_window, framebufferSizeCallback);
    return *this;
}

void Window::framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    // Retrieve the Window instance associated with the GLFWwindow pointer
    Window* currentWindow = static_cast<Window*>(glfwGetWindowUserPointer(window));
    if (currentWindow && currentWindow->m_resizeCallback) {
        currentWindow->m_resizeCallback(width, height);  // Call the user-provided callback
    }
}

GLFWwindow* Window::getGLFWwindow() const {
    return m_window;
}

// Move constructor
Window::Window(Window&& other) noexcept 
    : m_window(other.m_window), m_width(other.m_width), m_height(other.m_height), m_title(std::move(other.m_title)) {
    other.m_window = nullptr;
}

// Move assignment operator
Window& Window::operator=(Window&& other) noexcept {
    if (this != &other) {
        // Clean up current window
        if (m_window) {
            glfwDestroyWindow(m_window);
        }

        // Transfer ownership
        m_window = other.m_window;
        m_width = other.m_width;
        m_height = other.m_height;
        m_title = std::move(other.m_title);
        other.m_window = nullptr;
    }
    return *this;
}

}