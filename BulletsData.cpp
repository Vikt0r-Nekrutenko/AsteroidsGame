#include "BulletsData.h"
#include "GlobalSettings.h"

using namespace global;

void BulletsData::add(Vector2d position, Vector2d velocity, SpriteData *sprite_data, Destructible *stage) {
    if (m_positions.size() < setting("num_ammo")) {
        SpaceObjectsData::add(position, velocity, sprite_data, stage);
    }
    else {
        m_destr_types[old_bullet_indx]->restore(old_bullet_indx, *this);
        m_positions[old_bullet_indx] = position;
        m_velocities[old_bullet_indx] = velocity;

        old_bullet_indx += (old_bullet_indx == setting("num_ammo") - 1) ? -old_bullet_indx : 1ULL;
    }
}

void BulletsData::collisionHandler(vector<SpaceObjectsData::OverlappedPair> &overlapped_indxs, SpaceObjectsData &targets, float dt)
{
    for (size_t indx = 0ull; indx < overlapped_indxs.size(); indx++) {
        size_t obj_indx = overlapped_indxs[indx].object;
        size_t trg_indx = overlapped_indxs[indx].target;

        destroy(obj_indx);
        targets.destroy(trg_indx);
    }
}
