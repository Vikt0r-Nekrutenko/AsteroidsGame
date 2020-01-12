#include "AsteroidsData.h"

void AsteroidsData::destroy(size_t indx)
{
    SpaceObjectsData::destroy(indx);
    if (!m_destr_types[indx]->isDestroyed()) {
        changeDestructibleType(indx, new OneStageDestruction);
        m_velocities[indx] = {0,0};
        add(m_positions[indx] + m_radiuses[indx] * 2.f,
            m_velocities[indx] * -1.f,
            &global::sprites().get("small_asteroid"),
            new OneStageDestruction);
    }
}
