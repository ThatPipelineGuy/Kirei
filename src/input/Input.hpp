#pragma once

#include <GLFW/glfw3.h>
#include <functional>

namespace kirei {

class Input {
public:
    using KeyCallback = std::function<void(int, int, int, int)>;

    static Input& instance();

    // Register a key callback with GLFW, using a static method for the actual callback
    void registerKeyCallback(GLFWwindow* window, KeyCallback callback);

private:
    KeyCallback m_keyCallback;

    Input() = default;
    ~Input() = default;
    Input(const Input&) = delete;
    Input& operator=(const Input&) = delete;

    // Static callback function that conforms to GLFWkeyfun type
    static void keyCallbackInternal(GLFWwindow* window, int key, int scancode, int action, int mods);
};

}