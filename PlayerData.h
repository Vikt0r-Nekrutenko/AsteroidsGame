#ifndef PLAYERDATA_H
#define PLAYERDATA_H

#include "SpaceObjectsData.h"
#include <stack>

using std::stack;

namespace global {
const float DEF_MOMENTUM = 0.8f;
}

class ImprovementsData;

class PlayerData : public SpaceObjectsData
{
public:
    float getAngle() const;

    void update(float dt) override;

    void setAngle(Vector2d delta_position);

    void setMomentum(float value);

    void wrapCoordinates() override;

    void activateImprovements();

    void setImprovementsData(ImprovementsData *value);

    void addImprovements(vector<SpaceObjectsData::OverlappedPair> ovrlpd_imprvs);

private:
    stack<size_t> m_owned_imprvs;
    ImprovementsData *m_improvements = nullptr;
    size_t m_active_imprvs_indx = 0ull;
    float m_momentum = global::DEF_MOMENTUM;
    float m_angle = 0.f;
};

#endif // PLAYERDATA_H
