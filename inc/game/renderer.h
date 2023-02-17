#ifndef BRACKEYSGAMEJAM_RENDERER_H
#define BRACKEYSGAMEJAM_RENDERER_H

// TODO(Chloe) Batch rendering

#include <cglm/vec2.h>
#include <cglm/vec3.h>

#include <game/texture.h>
#include <game/window.h>


void renderer_init();
void renderer_close();

void render_quad( vec2 position, vec2 size, float rotation, vec3 color, struct texture* texture );

#endif //BRACKEYSGAMEJAM_RENDERER_H
