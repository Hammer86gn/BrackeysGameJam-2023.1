#include <math/vec3.h>
#include <math.h>

struct vec3 vec3_add( struct vec3 a, struct vec3 b )
{
    struct vec3 resultant = { .x = a.x + b.x, .y = a.y + b.y, .z = a.z + b.z };
    return resultant;
}

struct vec3 vec3_multiply( struct vec3 a, struct vec3 b )
{
    struct vec3 resultant = { .x = a.x * b.x, .y = a.y * b.y, .z = a.z * b.z };
    return resultant;
}

struct vec3 vec3_subtract(struct vec3 a, struct vec3 b)
{
    struct vec3 resultant = { .x = a.x - b.x, .y = a.y - b.y, .z = a.z - b.z };
    return resultant;
}

struct vec3 vec3_divide(struct vec3 a, struct vec3 b)
{
    struct vec3 resultant = { .x = a.x / b.x, .y = a.y / b.y, .z = a.z / b.z };
    return resultant;
}

float vec3_length( struct vec3 vec )
{
    return sqrtf( ( vec.x * vec.x ) + ( vec.y * vec.y ) + ( vec.z * vec.z ) );
}

float vec3_length_squared( struct vec3 vec )
{
    return ( vec.x * vec.x ) + ( vec.y * vec.y ) + ( vec.z * vec.z );
}

struct vec3 normalize( struct vec3 vec )
{
    float length_squared = vec3_length_squared( vec );
    float inverse = 1 / sqrtf( length_squared );

    struct vec3 result = {.x = vec.x * inverse, .y = vec.y * inverse, .z = vec.z * inverse };
    return result;
}
