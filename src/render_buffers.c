#include <game/render_buffers.h>
#include <malloc.h>
#include <glad/gl.h>

struct vbo* create_vbo()
{
    struct vbo* vbo = malloc( sizeof( struct vbo ) );
    if (vbo == NULL) {
        perror("Failed to allocate memory for a vertex buffer");
        return NULL;
    }
    glGenBuffers(1, &vbo->vbo_id);

    return vbo;
}

struct vbo* create_immediate_vbo( float* vertices )
{
    struct vbo* vbo = create_vbo();
    bind_vbo( vbo );
    set_vbo_data( vbo, vertices );
    return vbo;
}

void set_vbo_data( struct vbo* vbo, float* vertices )
{
    bind_vbo( vbo );
    vbo->size = sizeof( vertices );

    glBufferData( GL_ARRAY_BUFFER, vbo->size, vertices, GL_STATIC_DRAW );
}

void bind_vbo( struct vbo* vbo )
{
    glBindBuffer( GL_ARRAY_BUFFER, vbo->vbo_id );
}

void bind_no_vbo()
{
    glBindBuffer( GL_ARRAY_BUFFER, 0 );
}

void destroy_vbo( struct vbo* vbo )
{
    glDeleteBuffers( 1, &vbo->vbo_id );
    free( vbo );
}

struct ibo* create_ibo()
{
    struct ibo* ibo = malloc( sizeof( struct ibo ) );
    if (ibo == NULL) {
        perror("Failed to allocate memory for a vertex buffer");
        return NULL;
    }
    glGenBuffers(1, &ibo->ibo_id);

    return ibo;
}

struct ibo* create_immediate_ibo( uint32_t* indices )
{
    struct ibo* ibo = create_ibo();
    bind_ibo( ibo );
    set_ibo_data( ibo, indices );
    return ibo;
}

void set_ibo_data( struct ibo* ibo, uint32_t* indices )
{
    bind_ibo( ibo );
    ibo->size = sizeof( indices );

    glBufferData( GL_ELEMENT_ARRAY_BUFFER, ibo->size, indices, GL_STATIC_DRAW );
}

void bind_ibo( struct ibo* ibo )
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, ibo->ibo_id );
}

void bind_no_ibo()
{
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, 0 );
}

void destroy_ibo( struct ibo* ibo )
{
    glDeleteBuffers( 1, &ibo->ibo_id );
    free( ibo );
}

struct vao* create_vao()
{
    struct vao* vao = malloc( sizeof( struct vao ) );

    vao->bound_vbo = NULL;
    vao->bound_ibo = NULL;

    vao->attrib_array_len = 1;
    vao->attrib_array = malloc( sizeof( struct vertex_attrib ) );

    vao->attrib_stride = 0;

    glCreateVertexArrays(1, &vao->vao_id);


    return vao;
}

void attach_vbo( struct vao* vao, struct vbo* vbo )
{
    bind_vao( vao );
    vao->bound_vbo = vbo;
}

void attach_ibo( struct vao* vao, struct ibo* ibo )
{
    bind_vao( vao );
    vao->bound_ibo = ibo;
}

void enable_vertex_attrib( struct vao* vao, struct vertex_attrib attrib )
{
    vao->attrib_stride = 0;

    struct vertex_attrib* new_arr = malloc( sizeof( vao->attrib_array ) + ( sizeof( struct vertex_attrib ) ) );
    for (int i = 0; i < vao->attrib_array_len; i++) {
       vao->attrib_stride += vao->attrib_array[i].attrib_type_base_size * vao->attrib_array[i].attrib_type_components;
       new_arr[i] = vao->attrib_array[i];
    }
    new_arr[vao->attrib_array_len + 1] = attrib;
    free(vao->attrib_array);
    vao->attrib_array_len += 1;

    vao->attrib_array = new_arr;
    vao->attrib_stride += attrib.attrib_type_base_size * attrib.attrib_type_components;
}

void compile_vertex_attribs( struct vao* vao )
{
    bind_vao( vao );
    ssize_t offset = 0;

    for ( int i = 0; i < vao->attrib_array_len; i++ ) {
        struct vertex_attrib attrib = vao->attrib_array[i];

        glEnableVertexAttribArray( attrib.attrib_index );
        glVertexAttribPointer( attrib.attrib_index, attrib.attrib_type_components, attrib.attrib_type_base, 0, vao->attrib_stride, (void*) offset );

        offset += attrib.attrib_type_base_size * attrib.attrib_type_components;
    }

}

void bind_vao( struct vao* vao )
{
    if (vao->bound_vbo != NULL) {
        bind_vbo(vao->bound_vbo);
    }
    if (vao->bound_ibo != NULL) {
        bind_ibo(vao->bound_ibo);
    }
    glBindVertexArray( vao->vao_id );
}

void bind_no_vao()
{
    glBindVertexArray( 0 );
}

void destroy_vao( struct vao* vao )
{
    glDeleteVertexArrays( 1, &vao->vao_id );
    free( vao );
}