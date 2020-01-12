#include "PlayerData.h"
#include "GlobalSettings.h"
#include "ImprovementsData.h"
#include <cmath>

using namespace global;

void PlayerData::update(float dt)
{
    Vector2d acceleration;

    acceleration.m_x = -m_velocities[0].m_x * m_momentum;
    acceleration.m_y = -m_velocities[0].m_y * m_momentum;

    m_velocities[0] += acceleration * dt;

    float sw = setting("screen_width");
    float sh = setting("screen_height");

    float mw = setting("map_width");
    float mh = setting("map_height");

    if (m_positions[0].m_x > sw / 2 && m_positions[0].m_x < mw - sw / 2)
        setting("cam_offset_x") = m_positions[0].m_x - sw / 2.f;
    if (m_positions[0].m_y > sh / 2 && m_positions[0].m_y < mh - sh / 2)
        setting("cam_offset_y") = m_positions[0].m_y - sh / 2.f;

    SpaceObjectsData::update(dt);
}

void PlayerData::setAngle(Vector2d delta_position)
{
    m_angle = atan2f(delta_position.m_y, delta_position.m_x) - atanf(45.f);
}

float PlayerData::getAngle() const
{
    return m_angle;
}

void PlayerData::setMomentum(float value)
{
    m_momentum = value;
}

void PlayerData::wrapCoordinates()
{
    using namespace global;
    float mw = setting("map_width");
    float mh = setting("map_height");

    float sw = setting("screen_width");
    float sh = setting("screen_height");

    // horizontal wrapping
    {
        if (right(0ull) < 0.f) {
            m_positions[0ull].m_x = mw - m_radiuses[0ull];
            setting("cam_offset_x") = m_positions[0ull].m_x - sw + m_radiuses[0ull];
        }

        if (left(0ull) > mw)  {
            m_positions[0ull].m_x = m_radiuses[0ull];
            setting("cam_offset_x") = m_positions[0ull].m_x - m_radiuses[0ull];
        }
    }

    // vertival wrapping
    {
        if (bottom(0ull) < 0.f) {
            m_positions[0ull].m_y = mh - m_radiuses[0ull];
            setting("cam_offset_y") = m_positions[0ull].m_y - sh + m_radiuses[0ull];
        }

        if (top(0ull) > mh)     {
            m_positions[0ull].m_y = m_radiuses[0ull];
            setting("cam_offset_y") = m_positions[0ull].m_y - m_radiuses[0ull];
        }
    }
}

void PlayerData::activateImprovements()
{
    // if improvement exist AND improvement not destroyed AND improvement not active
    if (m_improvements->size() && !m_improvements->getDestructibleType(m_active_imprvs_indx)->isDestroyed() && m_improvements->getStage(m_active_imprvs_indx))
        m_improvements->destroy(m_active_imprvs_indx);

    if (!m_owned_imprvs.empty()) {
        m_active_imprvs_indx = m_owned_imprvs.top();

        m_improvements->restore(m_active_imprvs_indx);
        m_improvements->activate(m_active_imprvs_indx);

        m_improvements->setPosition(m_active_imprvs_indx, m_positions[0ull]);

        m_owned_imprvs.pop();
    }
}

void PlayerData::setImprovementsData(ImprovementsData *value)
{
    m_improvements = value;
}

void PlayerData::addImprovements(vector<SpaceObjectsData::OverlappedPair> ovrlpd_imprvs)
{
    for (size_t indx = 0ull; indx < ovrlpd_imprvs.size(); indx++) {
        size_t imprv_indx = ovrlpd_imprvs[indx].object;
        if (!m_improvements->getDestructibleType(imprv_indx)->isDestroyed() && m_improvements->getStage(imprv_indx) == false) {
            m_owned_imprvs.push(imprv_indx);
            m_improvements->destroy(imprv_indx);
        }
    }
}
