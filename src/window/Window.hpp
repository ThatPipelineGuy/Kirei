#pragma once
#include "Context.hpp"
#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include <iostream>
#include <format>

namespace kirei {

class Window {
public:
    Window(int width, int height, const std::string& title) 
        : m_width(width), m_height(height), m_title(title) {
        
        Context::instance();  // Ensure GLFW context is initialized

        // Set GLFW window hints
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

    [[nodiscard]] bool shouldClose() const {
        return glfwWindowShouldClose(m_window);
    }

    void update() {
        glfwSwapBuffers(m_window);
        glfwPollEvents();
    }

    Window& onResize(std::function<void(int, int)> callback) {
        glfwSetFramebufferSizeCallback(m_window, [callback = std::move(callback)](GLFWwindow*, int width, int height) {
            callback(width, height);
        });
        return *this;
    }

    // Getter for GLFWwindow pointer
    [[nodiscard]] GLFWwindow* getGLFWwindow() const {
        return m_window;
    }

    ~Window() {
        if (m_window) {
            glfwDestroyWindow(m_window);
            std::cout << std::format("Window destroyed: {}\n", m_title);
        }
    }

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;
};

}