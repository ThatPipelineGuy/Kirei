#pragma once

#include <GLFW/glfw3.h>
#include <stdexcept>

namespace kirei {

class Context {
public:
    // Constructor and destructor
    Context();
    ~Context();

    // Context should not be copied or moved
    Context(const Context&) = delete;
    Context& operator=(const Context&) = delete;
    Context(Context&&) = delete;
    Context& operator=(Context&&) = delete;
};

}