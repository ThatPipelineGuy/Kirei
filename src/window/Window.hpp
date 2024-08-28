#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <string>

namespace kirei {

class Window {
public:
    Window(int width, int height, const std::string& title);
    ~Window();

    [[nodiscard]] bool shouldClose() const;
    void update();

    Window& onResize(std::function<void(int, int)> callback);

    [[nodiscard]] GLFWwindow* getGLFWwindow() const;

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    Window(Window&& other) noexcept;
    Window& operator=(Window&& other) noexcept;

private:
    GLFWwindow* m_window;
    int m_width;
    int m_height;
    std::string m_title;

    std::function<void(int, int)> m_resizeCallback;  // Store the resize callback

    // Static function to handle framebuffer size changes
    static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
};

}