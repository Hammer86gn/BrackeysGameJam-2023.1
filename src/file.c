#include <util/file.h>
#include <string.h>
#include <stdint.h>
#include <limits.h>
#include <stdio.h>
#include <malloc.h>

const char* read_file( file_path path )
{
    int64_t path_size = strlen( path );
    if (path_size > PATH_MAX) {
        perror("Given path is too long\n");
        return "\0";
    }

    char* buffer = 0;
    int64_t len;

    FILE* file_buffer = fopen( path, "rb" );
    if (file_buffer) {
        fseek( file_buffer, 0, SEEK_END );
        len = ftell( file_buffer );
        fseek( file_buffer, 0, SEEK_SET );
        buffer = malloc( len );
        if (buffer)
        {
            fread ( buffer, 1, len, file_buffer );
        }
        fclose( file_buffer );
    } else {
        return "\0";
    }

    if (buffer) {
        return buffer;
    }
    return "\0";
}