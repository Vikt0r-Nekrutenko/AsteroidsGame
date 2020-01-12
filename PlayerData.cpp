#include "PlayerData.h"
#include "GlobalSettings.h"
#include <cmath>

using namespace global;

void PlayerData::update(float dt)
{
    Vector2d acceleration;

    if (fabsf(m_velocities[0].m_x) > MIN_OBJ_VELOCITY)
        acceleration.m_x = -m_velocities[0].m_x * m_momentum;
    if (fabsf(m_velocities[0].m_y) > MIN_OBJ_VELOCITY)
        acceleration.m_y = -m_velocities[0].m_y * m_momentum;

    float sw = setting("screen_width");
    float sh = setting("screen_height");

    float mw = setting("map_width");
    float mh = setting("map_height");

    if (m_positions[0].m_x > sw / 2 && m_positions[0].m_x < mw - sw / 2)
        setting("cam_offset_x") = m_positions[0].m_x - sw / 2.f;
    if (m_positions[0].m_y > sh / 2 && m_positions[0].m_y < mh - sh / 2)
        setting("cam_offset_y") = m_positions[0].m_y - sh / 2.f;

    m_velocities[0] += acceleration * dt;
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
