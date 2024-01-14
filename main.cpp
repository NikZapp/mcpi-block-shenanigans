#include <GLES/gl.h>

#include <libreborn/libreborn.h>

#include <iostream>
#include <mods/misc/misc.h>
#include <symbols/minecraft.h>

typedef unsigned char uchar;

typedef bool (*TileRenderer_tesselateInWorld_t)(uchar *tileRenderer, uchar *tile, int x, int y, int z);
static TileRenderer_tesselateInWorld_t TileRenderer_tesselateInWorld = (TileRenderer_tesselateInWorld_t)0x5e80c;
static Level_getTile_t Level_getData = (Level_getTile_t)0xa3324;
static Level_setTileAndData_t Level_setTileAndDataNoUpdate = (Level_setTileAndData_t)0xa33d0;
static uchar *Tesselator_instance = (uchar *)0x137538;

uchar *level = NULL;

static void mcpi_callback(uchar *minecraft) {
    if (minecraft == NULL) return;
    level = *(uchar **)(minecraft + Minecraft_level_property_offset);
}

bool TileRenderer_tesselateInWorld_injection(uchar *tile_renderer, uchar *tile, int x, int y, int z) {
    uchar *vtable = *(uchar **)tile;
    auto Tile_getRenderShape = *(Tile_getRenderShape_t *)(vtable + Tile_getRenderShape_vtable_offset);
    int shape = Tile_getRenderShape(tile);
    int data = Level_getData(level, x, y, z);

    srand(x * z + y * x + y);
    float uv_size = 1.0 / 16.0;

    switch (shape) {
    case 3: {
        // It's fire
        if (data != 0) {
            float uv_size = 1.0 / 16.0;
            float uv_x0 = 4.0 * uv_size;
            float uv_y0 = 10.0 * uv_size;
            float uv_x1 = uv_x0 + uv_size;
            float uv_y1 = uv_y0 + uv_size;

            int r = (rand() & 0xff) | 0x80;
            int g = (rand() & 0xff) | 0x80;
            int b = 0xff;
            Tesselator_color(Tesselator_instance, r, g, b, 255);

            // Basically, imagine the flower shape. It rotates around Y.
            // This is just 3 flower shapes, aligned to X, Y, Z

            // YZ cross
            Tesselator_vertexUV(Tesselator_instance, x, y, z, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z + 1, uv_x0, uv_y1);

            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z + 1, uv_x0, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x, y, z, uv_x0, uv_y0);

            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x, y, z + 1, uv_x0, uv_y1);

            Tesselator_vertexUV(Tesselator_instance, x, y, z + 1, uv_x0, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z, uv_x0, uv_y0);

            // XY cross
            Tesselator_vertexUV(Tesselator_instance, x, y, z, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x, y, z + 1, uv_x0, uv_y1);

            Tesselator_vertexUV(Tesselator_instance, x, y, z + 1, uv_x0, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x, y, z, uv_x0, uv_y0);

            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z + 1, uv_x0, uv_y1);

            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z + 1, uv_x0, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z, uv_x0, uv_y0);

            // XZ cross
            Tesselator_vertexUV(Tesselator_instance, x, y, z, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 1, uv_x0, uv_y1);

            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 1, uv_x0, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x, y, z, uv_x0, uv_y0);

            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x, y, z + 1, uv_x0, uv_y1);

            Tesselator_vertexUV(Tesselator_instance, x, y, z + 1, uv_x0, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x, y + 1, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y + 1, z, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z, uv_x0, uv_y0);
        }
        return true;
    }
    case 1: {
        // Flower shape
        int below = Level_getTile(level, x, y - 1, z);
        int block = Level_getTile(level, x, y, z);
        int above = Level_getTile(level, x, y + 1, z);
        // If water is below
        if ((below == 9) || (below == 8)) {
            // Lilypad
            float uv_x0 = 12.0 * uv_size;
            float uv_y0 = 4.0 * uv_size;
            float uv_x1 = uv_x0 + uv_size;
            float uv_y1 = uv_y0 + uv_size;
            Tesselator_color(Tesselator_instance, rand() & 0x7f, 255, rand() & 0x1f, 255);

            Tesselator_vertexUV(Tesselator_instance, x + 0, y, z + 0, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 0, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 0, y, z + 1, uv_x0, uv_y1);

            Tesselator_vertexUV(Tesselator_instance, x + 0, y, z + 1, uv_x0, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 1, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1, y, z + 0, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 0, y, z + 0, uv_x0, uv_y0);
        }
        if ((block == 83) && (above != 83)) {
            // Sugarcane leaves

            float uv_x0 = 15.0 * uv_size;
            float uv_y0 = 8.0 * uv_size;
            float uv_x1 = uv_x0 + uv_size;
            float uv_y1 = uv_y0 + uv_size;
            Tesselator_color(Tesselator_instance, 160, 255, 70, 255);

            for (int i = 0; i < 3; i++) {
                float h1 = (rand() % 0xf) / 16.0;
                float h2 = (rand() % 0xf) / 16.0;
                float h3 = (rand() % 0xf) / 16.0;
                float h4 = (rand() % 0xf) / 16.0;

                // Render 2 "planes"
                // the if statement rotates them 90 degrees to avoid similarity

                if (i & 1) {
                    Tesselator_vertexUV(Tesselator_instance, x - 0.2, y + h1, z - 0.2, uv_x0, uv_y0);
                }

                Tesselator_vertexUV(Tesselator_instance, x + 1.2, y + h2, z - 0.2, uv_x1, uv_y0);
                Tesselator_vertexUV(Tesselator_instance, x + 1.2, y + h3, z + 1.2, uv_x1, uv_y1);
                Tesselator_vertexUV(Tesselator_instance, x - 0.2, y + h4, z + 1.2, uv_x0, uv_y1);

                Tesselator_vertexUV(Tesselator_instance, x - 0.2, y + h1, z - 0.2, uv_x0, uv_y0);

                Tesselator_vertexUV(Tesselator_instance, x - 0.2, y + h1, z - 0.2, uv_x0, uv_y0);
                Tesselator_vertexUV(Tesselator_instance, x - 0.2, y + h4, z + 1.2, uv_x0, uv_y1);
                Tesselator_vertexUV(Tesselator_instance, x + 1.2, y + h3, z + 1.2, uv_x1, uv_y1);

                if (!(i & 1)) {
                    Tesselator_vertexUV(Tesselator_instance, x + 1.2, y + h1, z - 0.2, uv_x1, uv_y0);
                }
            }
        }
        return TileRenderer_tesselateInWorld(tile_renderer, tile, x, y, z);
    }
    case 6: {
        // Wheat
        // TODO: Make the top wave
        return TileRenderer_tesselateInWorld(tile_renderer, tile, x, y, z);
    }
    case 13: {
        // Cacti
        int above = Level_getTile(level, x, y + 1, z);
        if ((above == 0) && ((rand() % 5) == 0)) {
            // Flower
            float uv_x0 = 9.0 * uv_size;
            float uv_y0 = 8.0 * uv_size;
            float uv_x1 = uv_x0 + uv_size;
            float uv_y1 = uv_y0 + uv_size;
            Tesselator_color(Tesselator_instance, 255, 0, 255, 255);

            // Abusing the tesselator here to render triangles

            // X aligned petals
            Tesselator_vertexUV(Tesselator_instance, x + 0.5, y + 1.0, z + 0.0, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x - 0.5, y + 1.5, z + 0.5, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 0.5, y + 1.0, z + 1.0, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 1.5, y + 1.5, z + 0.5, uv_x0, uv_y1);

            Tesselator_vertexUV(Tesselator_instance, x + 0.5, y + 1.0, z + 0.0, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 1.5, y + 1.5, z + 0.5, uv_x0, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 0.5, y + 1.0, z + 1.0, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x - 0.5, y + 1.5, z + 0.5, uv_x1, uv_y0);

            // Z aligned petals
            Tesselator_vertexUV(Tesselator_instance, x + 1.0, y + 1.0, z + 0.5, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 0.5, y + 1.5, z - 0.5, uv_x1, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 0.0, y + 1.0, z + 0.5, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 0.5, y + 1.5, z + 1.5, uv_x0, uv_y1);

            Tesselator_vertexUV(Tesselator_instance, x + 1.0, y + 1.0, z + 0.5, uv_x0, uv_y0);
            Tesselator_vertexUV(Tesselator_instance, x + 0.5, y + 1.5, z + 1.5, uv_x0, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 0.0, y + 1.0, z + 0.5, uv_x1, uv_y1);
            Tesselator_vertexUV(Tesselator_instance, x + 0.5, y + 1.5, z - 0.5, uv_x1, uv_y0);
        }
        return TileRenderer_tesselateInWorld(tile_renderer, tile, x, y, z);
    }
    default: {
        return TileRenderer_tesselateInWorld(tile_renderer, tile, x, y, z);
    }
    }
}

int FireTile_getRenderLayer_injection(uchar *tile) {
    return 1;
}


static void add_star_item(unsigned char *filling_container) {
    ItemInstance *star_instance = new ItemInstance;
    ALLOC_CHECK(star_instance);
    star_instance->count = 255;
    star_instance->auxiliary = 1;
    star_instance->id = 51;
    (*FillingContainer_addItem)(filling_container, star_instance);
}


__attribute__((constructor)) static void init() {
    overwrite_calls((void *)TileRenderer_tesselateInWorld, (void *)TileRenderer_tesselateInWorld_injection);
    // FireTile vtable addr of Tile_getRenderLayer
    patch_address((void *)0x11493c, (void *)FireTile_getRenderLayer_injection);
    misc_run_on_update(mcpi_callback);
    misc_run_on_creative_inventory_setup(add_star_item);
}
