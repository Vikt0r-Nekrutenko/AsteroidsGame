#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include "SpaceObjectsData.h"

namespace global {
const float DEF_MOMENTUM = 0.8f;
}

class PlayerData : public SpaceObjectsData
{
public:
    void update(float dt) override;

    void setAngle(Vector2d delta_position);

    float getAngle() const;

    void setMomentum(float value);

private:
    float m_momentum = global::DEF_MOMENTUM;
    float m_angle = 0.f;
};

#endif // PLAYERDATA_H
