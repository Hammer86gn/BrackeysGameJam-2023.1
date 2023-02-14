#include <game/shader.h>
#include <malloc.h>
#include <stdio.h>
#include <glad/gl.h>

struct shader_program* create_program()
{
    struct shader_program* program = malloc( sizeof( struct shader_program* ) );
    if (program == NULL) {
        printf("Shader Program memory allocation failed\n");
        return NULL;
    }

    program->program_id = glCreateProgram();
    glBindAttribLocation( program->program_id, 0, "position" );
    // TODO(Chloe): Add the other attribs like texture coords and color kthxbye
    //      these aren't needed if its specified in the shader e.g. layout (location = 0) in vec3 position
    //      but I honestly do not care those can be the exception to the "default" attributes
    return program;
}

void attach_shader( struct shader_program* shader_program, const char* source, int32_t type )
{
    uint32_t shader = glCreateShader( type );
    glShaderSource( shader, 1, &source, NULL );
    glCompileShader( shader );

    int32_t compiled;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
    if (compiled != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetShaderInfoLog(shader, 1024, &log_length, message);
        perror("Shader failed to compile: ");
        perror(message);
        perror("\n");
    }

    glAttachShader( shader_program->program_id, shader );
    glDeleteShader( shader ); // might have to be deleted later
    free( source );
}

void attach_shader_file( struct shader_program* shader_program, file_path path, int32_t type )
{
    attach_shader( shader_program, read_file(path), type );
}

void compile_program( struct shader_program* shader_program )
{
    use_program(shader_program);
    glLinkProgram( shader_program->program_id );

    int32_t link_status;
    glGetProgramiv(shader_program->program_id, GL_LINK_STATUS, &link_status);
    if (link_status != GL_TRUE)
    {
        GLsizei log_length = 0;
        GLchar message[1024];
        glGetProgramInfoLog(shader_program->program_id, 1024, &log_length, message);
        perror("Shader program failed to link: ");
        perror(message);
        perror("\n");
    }
}

void set_program_uniform( struct shader_program* shader_program, struct shader_uniform uniform )
{
    int32_t uniform_location = glGetUniformLocation( shader_program->program_id, uniform.uniform_name );

    use_program( shader_program );
    switch ( uniform.uniform_type ) {
        case GL_FLOAT:
            printf("Name: %s, Float: %f", uniform.uniform_name,  uniform.uniform_value.float_type );
            glUniform1f( uniform_location, uniform.uniform_value.float_type );
            break;
        default:
            perror("Unsupported type for a shader uniform\n");
    }
    use_no_program();
}

void use_program( struct shader_program* shader_program )
{
    glUseProgram( shader_program->program_id );
}

void use_no_program()
{
    glUseProgram( 0 );
}

void destroy_program( struct shader_program* shader_program )
{
    glDeleteProgram( shader_program->program_id );
    free( shader_program );
}
