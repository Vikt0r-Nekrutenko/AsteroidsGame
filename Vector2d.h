#ifndef VECTOR2D_H
#define VECTOR2D_H

float random(float min, float max);

struct Vector2d
{
    float m_x, m_y;

    Vector2d(float x = 0.f, float y = 0.f);
    Vector2d operator + (const Vector2d &vec) const;
    Vector2d operator - (const Vector2d &vec) const;
    Vector2d operator * (const float s) const;
    Vector2d operator / (const float s) const;

    Vector2d &operator += (const Vector2d &vec);
    Vector2d &operator -= (const Vector2d &vec);

    float distanceTo(const Vector2d &vec) const;
};

#endif // VECTOR2D_H
