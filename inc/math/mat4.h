#ifndef BRACKEYSGAMEJAM_MAT4_H
#define BRACKEYSGAMEJAM_MAT4_H

#define __MAT4_FLOAT_SIZE__ 16

typedef float* mat4;

mat4 mat4_create_default( float default_value );

mat4 mat4_add( mat4 a, mat4 b );
mat4 mat4_multiply( mat4 a, mat4 b );

mat4 mat4_subtract( mat4 a, mat4 b );

#endif //BRACKEYSGAMEJAM_MAT4_H
