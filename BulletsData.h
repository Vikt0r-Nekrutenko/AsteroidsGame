#ifndef BULLETSDATA_H
#define BULLETSDATA_H

#include "SpaceObjectsData.h"

class BulletsData : public SpaceObjectsData
{
public:
    void add(Vector2d position, Vector2d velocity, SpriteData *sprite_data, Destructible *stage) override;

    void collisionHandler(vector<OverlappedPair> &overlapped_indxs, SpaceObjectsData &targets, float dt) override;
private:
    size_t old_bullet_indx = 0ULL;
};

#endif // BULLETSDATA_H
