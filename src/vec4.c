#include <math/vec4.h>
#include <math.h>

struct vec4 vec4_add( struct vec4 a, struct vec4 b )
{
    struct vec4 resultant = { .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z, .w = a.w + b.w };
    return resultant;
}

struct vec4 vec4_multiply( struct vec4 a, struct vec4 b )
{
    struct vec4 resultant = { .x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z, .w = a.w * b.w };
    return resultant;
}

struct vec4 vec4_subtract(struct vec4 a, struct vec4 b)
{
    struct vec4 resultant = { .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z, .w = a.w - b.w };
    return resultant;
}

struct vec4 vec4_divide(struct vec4 a, struct vec4 b)
{
    struct vec4 resultant = { .x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z, .w = a.w / b.w };
    return resultant;
}

float vec4_length( struct vec4 vec )
{
    return sqrtf( ( vec.x * vec.x ) + ( vec.y * vec.y ) + ( vec.z * vec.z ) + ( vec.w * vec.w ) );
}

float vec4_length_squared( struct vec4 vec )
{
    return ( vec.x * vec.x ) + ( vec.y * vec.y ) + ( vec.z * vec.z ) + ( vec.w * vec.w );
}

struct vec4 vec4_normalize( struct vec4 vec )
{
    float length_squared = vec4_length_squared( vec );
    float inverse = 1 / sqrtf( length_squared );

    struct vec4 result = {.x = vec.x * inverse, .y = vec.y * inverse, .z = vec.z * inverse, .w = vec.w * inverse };
    return result;
}