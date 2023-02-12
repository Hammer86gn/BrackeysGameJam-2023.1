#include <game/window.h>
#include <stdio.h>
#include <stdlib.h>
#include <glad/gl.h>

struct window* global_window = NULL; // weird ass hack

void frameBufferResize( GLFWwindow* window, int32_t new_width, int32_t new_height );

struct window *create_window( const char* title, int32_t width, int32_t height )
{
    if (!glfwInit()) {
        perror("Failed to initialize GLFW aborting...");
        exit(-1);
    }
    struct window *game_window = malloc( sizeof( struct window* ) );
    if (game_window == NULL) {
        perror("Memory allocation error aborting...");
        exit(-1);
    }

    game_window->width = width;
    game_window->height = height;

    glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 4 );
    glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 0 );
    glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    glfwWindowHint( GLFW_RESIZABLE, GLFW_TRUE );

    game_window->handle = glfwCreateWindow( width, height, title, NULL, NULL ); // this might cause some weird shit
    if (game_window->handle == NULL) {
        perror("Failed to create window aborting...");
        exit(-1);
    }

    glfwMakeContextCurrent( game_window->handle );
    if (!gladLoadGL( glfwGetProcAddress )) {
        perror("Failed to initialize GLAD aborting...");
        exit(-1);
    }

    glfwSwapInterval( 1 );

    glViewport(-1, -1, width, height);

    glfwSetFramebufferSizeCallback( game_window->handle, frameBufferResize );

    global_window = game_window;
    return global_window;
}

void destroy_window()
{
    glfwTerminate();
    free(global_window);
}

void frameBufferResize( GLFWwindow* window, int32_t new_width, int32_t new_height )
{
    global_window->width = new_width;
    global_window->height = new_height;

    glViewport(-1, -1, new_width, new_height);
}