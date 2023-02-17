#include <stdio.h>
#include <game/window.h>
#include <game/render_buffers.h>
#include <game/shader.h>
#include <io.h>
#include <limits.h>
#include "glad/gl.h"

#define TEMP_FSHADER_SOURCE "#version 400 core\n" \
                            "out vec4 FragColor;\n" \
                            "void main()\n" \
                            "{\n" \
                                "FragColor = vec4(1.0, 1.0, 1.0, 1.0);\n" \
                            "}\0" \

#define TEMP_VSHADER_SOURCE "#version 400 core\n"\
                            "layout (location = 0) in vec3 aPos;\n"\
                            "void main()\n"\
                            "{\n"\
                            "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"\
                            "}\0"

float temp_quad[] = {
         0.5f,  0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
};

unsigned int temp_quad_indices[] = {
        0, 1, 3,
        1, 2, 3
};

struct shader_program* shader_program;

struct vbo* vbo;
struct ibo* ibo;
struct vao* vao;

void setup_test_render();
void preform_test_render();
void preform_cleanup();

#include <game/renderer.h>

int main()
{
    struct window* window = create_window("Test", 720, 720);
    glfwMakeContextCurrent(window->handle);

//    setup_test_render();

    renderer_init();

    struct texture* texture = create_texture( "res/assets/sprites/default_texture.png" );

    while (!glfwWindowShouldClose( window->handle )) {
        glClearColor((float) 255 / 255, (float) 11 / 255, (float) 200 / 255, (float ) 255 / 255);
        glClear(GL_COLOR_BUFFER_BIT);

//        preform_test_render();

        vec2 pos = { 2, 5 };
        vec2 scale = { 1, 1 };
        vec3 color = { 0xFF, 0x33, 0xCC };
        render_quad( pos, scale, 90, color, texture );

        glfwSwapBuffers( window->handle );
        glfwPollEvents();
    }
//    preform_cleanup();
    destroy_window();
}

void setup_test_render()
{
    shader_program = create_program();


//    attach_shader( shader_program, TEMP_FSHADER_SOURCE, GL_FRAGMENT_SHADER );
//    attach_shader( shader_program, TEMP_VSHADER_SOURCE, GL_VERTEX_SHADER );

//    char cwd[PATH_MAX];
//    if (getcwd(cwd, sizeof(cwd)) != NULL) {
//        printf("Current working dir: %s\n", cwd);
//    } else {
//        perror("getcwd() error");
//    }
    attach_shader_file( shader_program, "res/shaders/fragment/base_fragment.fsh", GL_FRAGMENT_SHADER );
    attach_shader_file( shader_program, "res/shaders/vertex/base_vertex.vsh", GL_VERTEX_SHADER );
    compile_program( shader_program );

    struct shader_uniform test_uniform = {
            .uniform_name = "red\0",
            .uniform_type = GL_FLOAT,
            .uniform_value = 0
    };
    set_program_uniform( shader_program, test_uniform );

    vbo = create_vbo();
    ibo = create_ibo();

    vao = create_vao();
    bind_vao( vao );

    set_vbo_data( vbo, temp_quad, sizeof( temp_quad ) );
    set_ibo_data( ibo, temp_quad_indices, sizeof( temp_quad_indices ) );

    struct vertex_attrib attrib = {
            .attrib_index = 0,
            .attrib_type_base = GL_FLOAT,
            .attrib_type_base_size = sizeof( float ),
            .attrib_type_components = 3,
    };

    enable_vertex_attrib( vao, attrib );

    attach_vbo( vao, vbo );
    compile_vertex_attribs( vao );

    attach_ibo( vao, ibo );



    bind_no_vbo();

    bind_no_vao();

}

void preform_test_render()
{
    use_program( shader_program );
    bind_vao( vao );
    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );
}

void preform_cleanup()
{
    destroy_program( shader_program );
    destroy_vbo( vbo );
    destroy_ibo( ibo );
    destroy_vao( vao );
}