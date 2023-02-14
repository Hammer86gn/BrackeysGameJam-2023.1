#ifndef BRACKEYSGAMEJAM_VEC2_H
#define BRACKEYSGAMEJAM_VEC2_H

struct vec2 {
    float x;
    float y;
};

struct vec2 vec2_add( struct vec2 a, struct vec2 b );
struct vec2 vec2_multiply( struct vec2 a, struct vec2 b );

struct vec2 vec2_subtract(struct vec2 a, struct vec2 b);
struct vec2 vec2_divide(struct vec2 a, struct vec2 b);

float vec2_length( struct vec2 vec );

#endif //BRACKEYSGAMEJAM_VEC2_H
