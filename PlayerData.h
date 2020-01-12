#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include "SpaceObjectsData.h"

namespace global {
const float DEF_MOMENTUM = 0.8f;
}

class PlayerData : public SpaceObjectsData
{
public:
    float getAngle() const;

    void update(float dt) override;

    void setAngle(Vector2d delta_position);

    void setMomentum(float value);

    void wrapCoordinates() override;

private:
    float m_momentum = global::DEF_MOMENTUM;
    float m_angle = 0.f;
};

#endif // PLAYERDATA_H
