#ifndef BRACKEYSGAMEJAM_RENDER_BUFFERS_H
#define BRACKEYSGAMEJAM_RENDER_BUFFERS_H

#include <stdint.h>

//<editor-fold desc="Vertex Buffer">
struct vbo {
    uint32_t size;
    float* vertices;

    uint32_t vbo_id;
};

struct vbo* create_vbo();
struct vbo* create_immediate_vbo( float* vertices, ssize_t size );

void set_vbo_data( struct vbo* vbo, float* vertices, ssize_t size );

void bind_vbo( struct vbo* vbo );
void bind_no_vbo();

void destroy_vbo( struct vbo* vbo );

//</editor-fold>


//<editor-fold desc="Index Buffer">
struct ibo {
    uint32_t size;
    uint32_t* indices;

    uint32_t ibo_id;
};

struct ibo* create_ibo();
struct ibo* create_immediate_ibo( uint32_t* indices, ssize_t size );

void set_ibo_data( struct ibo* ibo, uint32_t* indices, ssize_t size );

void bind_ibo( struct ibo* ibo );
void bind_no_ibo();

void destroy_ibo( struct ibo* ibo );
//</editor-fold>

//<editor-fold desc="Vertex Array Object">
struct vertex_attrib {

    uint32_t attrib_index;

    int32_t attrib_type_components;
    uint32_t attrib_type_base;
    ssize_t attrib_type_base_size;

};

struct vao {
    struct vbo* bound_vbo;
    struct ibo* bound_ibo;

    ssize_t attrib_array_len;
    struct vertex_attrib* attrib_array;

    int32_t attrib_stride;

    uint32_t vao_id;
};

struct vao* create_vao();

void attach_vbo( struct vao* vao, struct vbo* vbo );
void attach_ibo( struct vao* vao, struct ibo* ibo );

void enable_vertex_attrib( struct vao* vao, struct vertex_attrib attrib );
void compile_vertex_attribs( struct vao* vao );

void bind_vao( struct vao* vao );
void bind_no_vao();

void destroy_vao( struct vao* vao );

//</editor-fold>

#endif //BRACKEYSGAMEJAM_RENDER_BUFFERS_H
