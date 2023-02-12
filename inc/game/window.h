#ifndef BRACKEYSGAMEJAM_WINDOW_H
#define BRACKEYSGAMEJAM_WINDOW_H

#include <stdint.h>

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

struct window {
    int32_t width;
    int32_t height;

    GLFWwindow* handle;
};


struct window* create_window( const char* title, int32_t width, int32_t height );
void destroy_window();

#endif //BRACKEYSGAMEJAM_WINDOW_H
