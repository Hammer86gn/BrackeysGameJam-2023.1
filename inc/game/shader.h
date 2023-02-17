#ifndef BRACKEYSGAMEJAM_SHADER_H
#define BRACKEYSGAMEJAM_SHADER_H

#include <stdint.h>
#include <util/file.h>
#include <cglm/mat4.h>

struct shader_program {
    uint32_t program_id;
};

struct shader_uniform {
    const char* uniform_name;
    int32_t uniform_type;
    void* uniform_value;
};

struct shader_program* create_program();

void attach_shader( struct shader_program* shader_program, const char* shader, int32_t type );
void attach_shader_file( struct shader_program* shader_program, file_path path, int32_t type );

void compile_program( struct shader_program* shader_program );

void set_program_uniform( struct shader_program* shader_program, struct shader_uniform uniform );

void use_program( struct shader_program* shader_program );
void use_no_program();

void destroy_program( struct shader_program* );

#endif //BRACKEYSGAMEJAM_SHADER_H
