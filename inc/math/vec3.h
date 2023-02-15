#ifndef BRACKEYSGAMEJAM_VEC3_H
#define BRACKEYSGAMEJAM_VEC3_H

struct vec3 {
    float x;
    float y;
    float z;
};

struct vec3 vec3_add( struct vec3 a, struct vec3 b );
struct vec3 vec3_multiply( struct vec3 a, struct vec3 b );

struct vec3 vec3_subtract(struct vec3 a, struct vec3 b);
struct vec3 vec3_divide(struct vec3 a, struct vec3 b);

float vec3_length( struct vec3 vec );
float vec3_length_squared( struct vec3 vec );

struct vec3 vec3_normalize( struct vec3 vec );

#endif //BRACKEYSGAMEJAM_VEC3_H
