#pragma once

// Core functionality: Context management for GLFW initialization and termination
#include "../../src/core/Context.hpp"

// Window management: Abstraction over GLFW window creation and handling
#include "../../src/window/Window.hpp"

// Input management: Abstraction over GLFW input handling
#include "../../src/input/Input.hpp"

// Additional utilities or future expansions can be included here as needed

/*
 * Kirei - A sleek and modern C++20
 * 
 * This header provides a single entry point to include the entire Kirei library.
 * By including this header, all core functionalities, window management, and input handling
 * abstractions are made available.
 *
 * Example usage:
 *
 * #include <kirei/Kirei.hpp>
 *
 * int main() {
 *     kirei::Window window(800, 600, "Kirei Application");
 *     // Application logic here
 *     return 0;
 * }
 *
 * Enjoy the simplicity and power of Kirei!
 */

namespace kirei {
// All public APIs are available under the `kirei` namespace. 
// Future functionalities and utilities will be added here.
}
