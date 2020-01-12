#include "AsteroidsData.h"
#include "PlayerData.h"
#include <cmath>

using namespace global;

void AsteroidsData::destroy(size_t indx)
{
    SpaceObjectsData::destroy(indx);
    if (!m_destr_types[indx]->isDestroyed()) {
        changeDestructibleType(indx, new OneStageDestruction);
        m_velocities[indx] = m_velocities[indx] * -1.f;
        add(m_positions[indx] + m_radiuses[indx] * 2.f,
            m_velocities[indx] * -1.f,
            &global::sprites().get("small_asteroid"),
            new OneStageDestruction);
    }
}

void AsteroidsData::restore(size_t indx)
{
    changeDestructibleType(indx, new BigAsteroidDestruction);
    SpaceObjectsData::restore(indx);
}

void AsteroidsData::update(float dt)
{
    for (size_t indx = 0ULL; indx < m_positions.size(); indx++) {
        if (!m_destr_types[indx]->isDestroyed()) {
            Vector2d acceleration;
            if (fabsf(m_velocities[indx].m_x) > MIN_OBJ_VELOCITY)
                acceleration.m_x = -m_velocities[indx].m_x * DEF_MOMENTUM;
            if (fabsf(m_velocities[indx].m_y) > MIN_OBJ_VELOCITY)
                acceleration.m_y = -m_velocities[indx].m_y * DEF_MOMENTUM;
            m_velocities[indx] += acceleration * dt;
        }
    }
    SpaceObjectsData::update(dt);
}
