#include "Context.hpp"
#include <iostream>

namespace kirei {

// Constructor: Initializes GLFW
Context::Context() {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    std::cout << "GLFW initialized\n";
}

// Destructor: Terminates GLFW
Context::~Context() {
    glfwTerminate();
    std::cout << "GLFW terminated\n";
}

}