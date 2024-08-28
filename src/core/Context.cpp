#include "Context.hpp"
#include <iostream>

namespace kirei {

Context::Context() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    std::cout << "GLFW initialized\n";
}

Context::~Context() {
    glfwTerminate();
    std::cout << "GLFW terminated\n";
}

Context& Context::instance() {
    static Context context;
    return context;
}

}