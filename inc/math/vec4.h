#ifndef BRACKEYSGAMEJAM_VEC4_H
#define BRACKEYSGAMEJAM_VEC4_H

struct vec4 {
    float x;
    float y;
    float z;
    float w;
};

struct vec4 vec4_add( struct vec4 a, struct vec4 b );
struct vec4 vec4_multiply( struct vec4 a, struct vec4 b );

struct vec4 vec4_subtract(struct vec4 a, struct vec4 b);
struct vec4 vec4_divide(struct vec4 a, struct vec4 b);

float vec4_length( struct vec4 vec );
float vec4_length_squared( struct vec4 vec );

struct vec4 normalize( struct vec4 vec );


#endif //BRACKEYSGAMEJAM_VEC4_H
