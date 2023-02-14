#include <math/mat4.h>
#include <malloc.h>
#include <math.h>

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

void mat4_rotate( mat4* matrix, float radians, struct vec3 axis ) // I have zero idea if this works
{
    float angle_cosine = cosf( radians );
    float angle_sine = sinf( radians );

    struct vec3 normalized_axis = normalize( axis );

    struct vec3 temp_scalar = {
            .x = 1 - angle_cosine,
            .y = 1 - angle_cosine,
            .z = 1 - angle_cosine
    };

    struct vec3 rotational_axis = vec3_multiply(temp_scalar, normalized_axis);

    mat4 resultant = malloc( __MAT4_FLOAT_SIZE__ * sizeof( float ) );

    float x = rotational_axis.x;
    float y = rotational_axis.y;
    float z = rotational_axis.z;

    resultant[0] = angle_cosine + x * x * temp_scalar.x;
    resultant[1] = x * y * temp_scalar.x + z * angle_sine;
    resultant[2] = x * z * temp_scalar.x - y * angle_sine;
    resultant[3] = 0;

    resultant[4] = x * y * temp_scalar.x - z * angle_sine;
    resultant[5] = angle_cosine + y * y * temp_scalar.y;
    resultant[6] = y * z * temp_scalar.y + x * angle_sine;
    resultant[7] = 0;

    resultant[8] = x * z * temp_scalar.x + y * angle_sine;
    resultant[9] = y * z * temp_scalar.y - x * angle_sine;
    resultant[10] = angle_cosine + z * z * temp_scalar.z;
    resultant[11] = 0;

    resultant[12] = 0;
    resultant[13] = 0;
    resultant[14] = 0;
    resultant[15] = 1;

    mat4_multiply(*matrix, resultant);
    free(resultant);
}

void mat4_translate( mat4* matrix, struct vec3 translation )
{
    mat4 deref = *matrix;
    deref[12] += translation.x;
    deref[13] += translation.y;
    deref[14] += translation.z;
    matrix = &deref;
}