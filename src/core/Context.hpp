#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>
#include <iostream>
#include <format>

namespace kirei {

class Context {
public:
    static Context& instance() {
        static Context context;
        return context;
    }

    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;

    ~Context() {
        glfwTerminate();
        std::cout << "GLFW terminated\n";
    }

private:
    Context() {
        if (!glfwInit()) {
            throw std::runtime_error("Failed to initialize GLFW");
        }
        std::cout << "GLFW initialized\n";
    }
};

}
