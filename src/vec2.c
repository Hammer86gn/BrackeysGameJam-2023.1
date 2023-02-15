#include <math/vec2.h>
#include <math.h>

struct vec2 vec2_add( struct vec2 a, struct vec2 b )
{
    struct vec2 result = {.x = a.x + b.x, .y = a.y + b.y};
    return result;
}

struct vec2 vec2_multiply( struct vec2 a, struct vec2 b )
{
    struct vec2 result = {.x = a.x * b.x, .y = a.y * b.y};
    return result;
}

struct vec2 vec2_subtract( struct vec2 a, struct vec2 b )
{
    struct vec2 result = {.x = a.x - b.x, .y = a.y - b.y};
    return result;
}

struct vec2 vec2_divide( struct vec2 a, struct vec2 b )
{
    struct vec2 result = {.x = a.x / b.x, .y = a.y / b.y};
    return result;
}

float vec2_length( struct vec2 vec2 )
{
    return sqrtf( ( vec2.x * vec2.x ) + ( vec2.y * vec2.y ) );
}

float vec2_length_squared( struct vec2 vec )
{
    return ( vec.x * vec.x ) + ( vec.y * vec.y );
}

struct vec2 vec2_normalize( struct vec2 vec )
{
    float length_squared = vec2_length_squared( vec );
    float inverse = 1 / sqrtf( length_squared );

    struct vec2 result = {.x = vec.x * inverse, .y = vec.y * inverse };
    return result;
}