#include "Destructible.h"
#include "SpaceObjectsData.h"

using namespace global;

bool Destructible::isDestroyed() const
{
    return m_is_destroyed;
}

void OneStageDestruction::destroy(size_t indx, SpaceObjectsData &sod)
{
    m_is_destroyed = true;
}

void OneStageDestruction::restore(size_t indx, SpaceObjectsData &sod)
{
    m_is_destroyed = false;
}

void BigAsteroidDestruction::destroy(size_t indx, SpaceObjectsData &sod)
{
    sod.setSpriteData(indx, &sprites().get("small_asteroid"));
    sod.setRadius(indx, (sod.getSpriteData(indx)->width + sod.getSpriteData(indx)->height) / 2.f / 2.f);
}

void BigAsteroidDestruction::restore(size_t indx, SpaceObjectsData &sod)
{
    sod.setSpriteData(indx, &sprites().get("big_asteroid"));
    sod.setRadius(indx, (sod.getSpriteData(indx)->width + sod.getSpriteData(indx)->height) / 2.f / 2.f);
}
