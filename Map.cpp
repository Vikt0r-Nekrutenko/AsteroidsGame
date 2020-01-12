#include "Map.h"
#include "GlobalSettings.h"
#include "SpritesDataHolder.h"

void drawMap()
{
    using namespace global;
    for (int i = 0; i < setting("map_width"); i += sprites().get("map").width)
        for (int j = 0; j < setting("map_height"); j += sprites().get("map").height)
            drawSprite(sprites().get("map").sprite, int(i - setting("cam_offset_x")) , int(j - setting("cam_offset_y")));
}
