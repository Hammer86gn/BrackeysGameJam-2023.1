#include <math/mat4.h>
#include <malloc.h>

mat4 mat4_create_default( float default_value )
{
    mat4 matrix = malloc( __MAT4_FLOAT_SIZE__ * sizeof( float ) );
    for (int i = 0; i < __MAT4_FLOAT_SIZE__; i++) {
        matrix[i] = default_value;
    }
    return matrix;
}

mat4 mat4_add( const mat4 a, const mat4 b )
{
    mat4 resultant = mat4_create_default( 0 );
    for (int i = 0; i < __MAT4_FLOAT_SIZE__; i++) {
        resultant[i] = a[i] + b[i];
    }
    return resultant;
}

mat4 mat4_multiply( const mat4 a, const mat4 b )
{
    mat4 resultant = mat4_create_default( 0 );
    for (int i = 0; i < 4; i++) {
        for (int ii = 0; ii < 4; ii++) {
            float sum = 0;
            for (int iii = 0; iii < 4; iii++) {
                sum += a[i * 4 + iii] * b[iii * 4 + ii];
            }
            resultant[i * 4 + ii] = sum;
        }
    }
    return resultant;
}

mat4 mat4_subtract( const mat4 a, const mat4 b )
{
    mat4 resultant = mat4_create_default( 0 );
    for (int i = 0; i < __MAT4_FLOAT_SIZE__; i++) {
        resultant[i] = a[i] - b[i];
    }
    return resultant;
}