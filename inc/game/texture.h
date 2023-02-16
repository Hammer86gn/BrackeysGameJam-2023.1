#ifndef BRACKEYSGAMEJAM_TEXTURE_H
#define BRACKEYSGAMEJAM_TEXTURE_H

#include <stdint.h>
#include <util/file.h>

struct texture {
    int32_t texture_width;
    int32_t texture_height;
    int32_t texture_channels;

    uint32_t texture_id;
};

struct texture* create_texture( file_path path );

void use_texture( struct texture* texture );
void use_no_texture();

void destroy_texture( struct texture* texture );

struct texture_atlas {
    int32_t cell_width;
    int32_t cell_height;

    int32_t total_cells;

    struct texture* texture;
};

struct texture_atlas* create_atlas( struct texture* texture, int32_t cell_width, int32_t cell_height );
float* get_texture_coords_based_on_cell( struct texture_atlas* atlas, uint32_t cell_x, uint32_t cell_y );

#endif //BRACKEYSGAMEJAM_TEXTURE_H
