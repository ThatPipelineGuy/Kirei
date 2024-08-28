#pragma once

#include <GLFW/glfw3.h>
#include <functional>
#include <map>
#include <utility>

namespace kirei {

class Input {
public:
    using KeyCallback = std::function<void(int, int, int, int)>;

    static Input& instance() {
        static Input input;
        return input;
    }

    void registerKeyCallback(GLFWwindow* window, KeyCallback callback) {
        glfwSetKeyCallback(window, [this, callback = std::move(callback)](GLFWwindow* win, int key, int scancode, int action, int mods) {
            keyCallback(key, scancode, action, mods);
        });
        m_keyCallback = std::move(callback);
    }

    void keyCallback(int key, int scancode, int action, int mods) {
        if (m_keyCallback) m_keyCallback(key, scancode, action, mods);
    }

private:
    KeyCallback m_keyCallback;

    Input() = default;
    ~Input() = default;
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;
};

}
