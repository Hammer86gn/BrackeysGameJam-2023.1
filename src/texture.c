#include <game/texture.h>
#include <malloc.h>
#include <glad/gl.h>
#include <stb_image.h>

struct texture* create_texture( file_path path )
{
    struct texture* texture = malloc( sizeof( struct texture ) );

    glGenTextures( 1, &texture->texture_id );
    glBindTexture( GL_TEXTURE_2D, texture->texture_id );

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );

    stbi_set_flip_vertically_on_load( 1 );
    uint8_t* data = stbi_load( path, &texture->texture_width, &texture->texture_height, &texture->texture_channels, 0 );

    if (!data) {
        printf( "Failed to load texture at: %s", path );
        return NULL; // TODO(Chloe): When the big refactor comes around this should be some default texture
    }

    int32_t texture_channel = 0;
    int32_t image_channel = 0;

    if (texture->texture_channels == 4) {
        texture_channel = GL_RGBA8;
        image_channel = GL_RGBA;
    } else if (texture->texture_channels == 3) {
        texture_channel = GL_RGBA8;
        image_channel = GL_RGB;
    }

    glTexImage2D( GL_TEXTURE_2D, 0, texture_channel, texture->texture_width, texture->texture_height, 0, image_channel, GL_UNSIGNED_BYTE, data );
    glGenerateMipmap( GL_TEXTURE_2D );
    stbi_image_free( data );

    return texture;
}

void use_texture( struct texture* texture )
{
    glBindTexture( GL_TEXTURE_2D, texture->texture_id );
}

void use_no_texture()
{
    glBindTexture( GL_TEXTURE_2D, 0 );
}

void destroy_texture( struct texture* texture )
{
    glDeleteTextures( 1, &texture->texture_id );
    free( texture );
}

struct texture_atlas* create_atlas( struct texture* texture, int32_t cell_width, int32_t cell_height )
{
    struct texture_atlas* atlas = malloc( sizeof( struct texture_atlas ) );

    atlas->cell_width = cell_width;
    atlas->cell_height = cell_height;

    atlas->texture = texture;

    atlas->total_cells =  ( ( texture->texture_width * texture->texture_height ) / cell_width ) / cell_height;


    return atlas;
}

float* get_texture_coords_based_on_cell( struct texture_atlas* atlas, uint32_t cell_x, uint32_t cell_y )
{
    float* texture_coords = malloc( 8 * sizeof( float ) );
    if (texture_coords == NULL) {
        return NULL;
    }
    // 0 - top right x
    // 1 - top right y

    // 2 - bottom right x
    // 3 - bottom right y

    // 4 - bottom left x
    // 5 - bottom left y

    // 6 - top left x
    // 7 - top left y

    texture_coords[0] = (float) ( ( cell_x + 1 ) * atlas->cell_width )  /  (float) atlas->texture->texture_width;
    texture_coords[1] = (float) ( ( cell_y + 1 ) * atlas->cell_height ) /  (float) atlas->texture->texture_height;

    texture_coords[2] = (float) ( ( cell_x + 1 ) * atlas->cell_width )  /  (float) atlas->texture->texture_width;
    texture_coords[3] = (float) ( ( cell_y ) * atlas->cell_height )     /  (float) atlas->texture->texture_height;

    texture_coords[4] = (float) ( ( cell_x ) * atlas->cell_width )      /  (float) atlas->texture->texture_width;
    texture_coords[5] = (float) ( ( cell_y ) * atlas->cell_height )     /  (float) atlas->texture->texture_height;

    texture_coords[6] = (float) ( ( cell_x ) * atlas->cell_width )      /  (float) atlas->texture->texture_width;
    texture_coords[7] = (float) ( ( cell_y + 1 ) * atlas->cell_height ) /  (float) atlas->texture->texture_height;

    return texture_coords;
}