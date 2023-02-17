#include <game/renderer.h>
#include <game/render_buffers.h>
#include <game/shader.h>

#include <cglm/mat4.h>
#include <cglm/affine.h>
#include <cglm/struct.h>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#define CREATE_UNIT_MAT4() { { 1, 1 ,1, 1 }, { 1, 1 ,1, 1 }, { 1, 1 ,1, 1 }, { 1, 1 ,1, 1 } }

struct renderer_manager {

    int32_t viewport_right;
    int32_t viewport_top;

    float* quad_vertices;
    uint32_t* quad_indices;

    struct shader_program* main_program;

};

struct renderer_manager* renderer = NULL;

void renderer_init( struct window* window )
{
    renderer = malloc( sizeof( struct renderer_manager ) );
    renderer->viewport_top = window->height;
    renderer->viewport_right = window->width;

    float verts[] = {
             0.5f,  0.5f,  0.0f,
             0.5f, -0.5f,  0.0f,
            -0.5f, -0.5f,  0.0f,
            -0.5f,  0.5f,  0.0f,
    };

    uint32_t quad_indices[] = {
            0, 1, 3,
            1, 2, 3
    };

    renderer->quad_vertices = verts;
    renderer->quad_indices = quad_indices;

    renderer->main_program = create_program();
    attach_shader_file( renderer->main_program, "res/shaders/vertex/advanced_vertex.vsh", GL_VERTEX_SHADER );
    attach_shader_file( renderer->main_program, "res/shaders/fragment/quad_shader.fsh", GL_FRAGMENT_SHADER );
    compile_program( renderer->main_program );

}

void render_quad( vec2 position, vec2 size, float rotation, vec3 color, struct texture* texture )
{
    if (renderer == NULL) {
        return;
    }

    mat4 transformation_matrix = CREATE_UNIT_MAT4();

    vec3 translation = { position[0], position[1], 1 };
    glm_translate( transformation_matrix, translation );

    vec3 scalar = { size[0], size[1], 1 };
    glm_scale( transformation_matrix, scalar );

    vec3 rotational_axis = { 0, 0, 1 };
    glm_rotate( transformation_matrix, glm_rad(rotation), rotational_axis );

    mat4 projection_matrix = CREATE_UNIT_MAT4();


    glm_ortho( -1, (float) renderer->viewport_right, -1, (float) renderer->viewport_top, 0.1f, 100, projection_matrix );

    mat4 view_matrix = CREATE_UNIT_MAT4();

    use_program( renderer->main_program );

    struct shader_uniform transform_uniform = {
        .uniform_name = "transform",
        .uniform_type = GL_MATRIX4_NV,
        .uniform_value = transformation_matrix
    };
    struct shader_uniform projection = {
            .uniform_name = "projection",
            .uniform_type = GL_MATRIX4_NV,
            .uniform_value = projection_matrix
    };
    struct shader_uniform view = {
            .uniform_name = "view",
            .uniform_type = GL_MATRIX4_NV,
            .uniform_value = view_matrix
    };



    set_program_uniform( renderer->main_program, transform_uniform );
    set_program_uniform( renderer->main_program, projection );
    set_program_uniform( renderer->main_program, view );


    struct vertex_attrib position_attrib = {
            .attrib_index = 0,
            .attrib_type_components = 3,
            .attrib_type_base = GL_FLOAT,
            .attrib_type_base_size = sizeof ( float ),
    };

    struct vertex_attrib color_attrib = {
            .attrib_index = 1,
            .attrib_type_components = 3,
            .attrib_type_base = GL_FLOAT,
            .attrib_type_base_size = sizeof ( float ),
    };

    struct vertex_attrib t_coord_attrib = {
            .attrib_index = 2,
            .attrib_type_components = 2,
            .attrib_type_base = GL_FLOAT,
            .attrib_type_base_size = sizeof ( float ),
    };



    float verts[32] = {
            renderer->quad_vertices[0], renderer->quad_vertices[1], renderer->quad_vertices[2], color[0], color[1], color[2], 0, 0,
            renderer->quad_vertices[3], renderer->quad_vertices[4], renderer->quad_vertices[5], color[0], color[1], color[2], 1, 0,
            renderer->quad_vertices[6], renderer->quad_vertices[7], renderer->quad_vertices[8], color[0], color[1], color[2], 0, 0,
            renderer->quad_vertices[9], renderer->quad_vertices[10], renderer->quad_vertices[11], color[0], color[1], color[2], 0, 1,
    };

    struct vbo* vbo = create_vbo();
    struct ibo* ibo = create_ibo();

    struct vao* vao = create_vao();
    bind_vao( vao );

    set_vbo_data( vbo, verts, sizeof( verts ) );
    set_ibo_data( ibo, renderer->quad_indices, sizeof( renderer->quad_indices ) );

    enable_vertex_attrib( vao, position_attrib );
    enable_vertex_attrib( vao, color_attrib );
    enable_vertex_attrib( vao, t_coord_attrib );

    attach_vbo( vao, vbo );
    compile_vertex_attribs( vao );

    attach_ibo( vao, ibo );

    use_program( renderer->main_program );
    use_texture( texture );

    glDrawElements( GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0 );

    bind_no_vbo();

    bind_no_vao();
    use_no_program();

    destroy_vbo( vbo );
    destroy_ibo( ibo );
    destroy_vao( vao );
}