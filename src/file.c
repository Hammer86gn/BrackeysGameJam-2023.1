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
        printf("Error opening file: %s\n", strerror(errno));
        return "\0";
    }
    if (buffer) {
        char* new_buffer = malloc( (len + 1) * sizeof( char ) );
        for (int i = 0; i < len; i++) {
            new_buffer[i] = buffer[i];
        }
        buffer[len] = '\0';
        len += 1;
        return buffer;
    }
    return "\0";
}

//const char* read_file( file_path file_name) {
//    FILE *file = fopen(file_name, "r");
//    if (file == NULL) {
//
//        return NULL;
//    }
//
//    fseek(file, 0, SEEK_END);
//    long file_size = ftell(file);
//    rewind(file);
//
//    char *buffer = (char*)malloc((file_size + 1) * sizeof(char));
//    if (buffer == NULL) {
//        printf("Error allocating memory\n");
//        fclose(file);
//        return NULL;
//    }
//
//    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
//    if (bytes_read != file_size) {
//        printf("Error reading file\n");
//        free(buffer);
//        fclose(file);
//        return NULL;
//    }
//
//    buffer[file_size] = '\0';
//    fclose(file);
//    return buffer;
//}