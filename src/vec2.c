#include <math/vec2.h>

struct vec2 vec2_add( struct vec2 a, struct vec2 b )
{
    float resultX, resultY;

    // 0, 1 - resultant
    // 2, 3 - v1.x v1.y
    // 4, 5 - v2.x v2.y
    __asm__(
            "FLDS %2 \n" // v1.x
            "FADDS %4 \n" // v2.x
            "FSTPS %0 \n"

            "FLDS %3 \n"
            "FADDS %5 \n"
            "FSTPS %1 \n"
            :"=m"(resultX), "=m"(resultY)
            :"m"(a.x), "m"(a.y), "m"(b.x), "m"(b.y)
            :
            );

    struct vec2 result = {.x = resultX, .y = resultY};
    return result;
}

struct vec2 vec2_multiply( struct vec2 a, struct vec2 b )
{
    float resultX, resultY;

    // 0, 1 - resultant
    // 2, 3 - v1.x v1.y
    // 4, 5 - v2.x v2.y
    __asm__(
            "FLDS %2 \n" // v1.x
            "FMULS %4 \n" // v2.x
            "FSTPS %0 \n"

            "FLDS %3 \n"
            "FMULS %5 \n"
            "FSTPS %1 \n"
            :"=m"(resultX), "=m"(resultY)
            :"m"(a.x), "m"(a.y), "m"(b.x), "m"(b.y)
            :
            );

    struct vec2 result = {.x = resultX, .y = resultY};
    return result;
}

struct vec2 vec2_subtract( struct vec2 a, struct vec2 b )
{
    float resultX, resultY;

    // 0, 1 - resultant
    // 2, 3 - v1.x v1.y
    // 4, 5 - v2.x v2.y
    __asm__(
            "FLDS %2 \n" // v1.x
            "FSUBS %4 \n" // v2.x
            "FSTPS %0 \n"

            "FLDS %3 \n"
            "FSUBS %5 \n"
            "FSTPS %1 \n"
            :"=m"(resultX), "=m"(resultY)
            :"m"(a.x), "m"(a.y), "m"(b.x), "m"(b.y)
            :
            );

    struct vec2 result = {.x = resultX, .y = resultY};
    return result;
}

struct vec2 vec2_divide( struct vec2 a, struct vec2 b )
{
    float resultX, resultY;

    // 0, 1 - resultant
    // 2, 3 - v1.x v1.y
    // 4, 5 - v2.x v2.y
    __asm__(
            "FLDS %2 \n" // v1.x
            "FDIVS %4 \n" // v2.x
            "FSTPS %0 \n"

            "FLDS %3 \n"
            "FDIVS %5 \n"
            "FSTPS %1 \n"
            :"=m"(resultX), "=m"(resultY)
            :"m"(a.x), "m"(a.y), "m"(b.x), "m"(b.y)
            :
            );

    struct vec2 result = {.x = resultX, .y = resultY};
    return result;
}