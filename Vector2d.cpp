#include "Vector2d.h"
#include <cmath>

float random(float min, float max) {
    return min + rand() % int(max - min);
}

Vector2d::Vector2d(float x, float y) :
    m_x{x}, m_y{y}
{

}

Vector2d Vector2d::operator +(const Vector2d &vec) const
{
    return { m_x + vec.m_x, m_y + vec.m_y };
}

Vector2d Vector2d::operator -(const Vector2d &vec) const
{
    return { m_x - vec.m_x, m_y - vec.m_y };
}

Vector2d Vector2d::operator *(const float s) const
{
    return { m_x * s, m_y * s };
}

Vector2d Vector2d::operator /(const float s) const
{
    return { m_x / s, m_y / s };
}

Vector2d &Vector2d::operator +=(const Vector2d &vec)
{
    m_x += vec.m_x;
    m_y += vec.m_y;
    return *this;
}

Vector2d &Vector2d::operator -=(const Vector2d &vec)
{
    m_x -= vec.m_x;
    m_y -= vec.m_y;
    return *this;
}

float Vector2d::distanceTo(const Vector2d &vec) const
{
    return sqrtf(powf(m_x - vec.m_x, 2.f) + powf(m_y - vec.m_y, 2.f));
}
