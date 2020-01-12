#ifndef IMPROVEMENTSDATA_H
#define IMPROVEMENTSDATA_H

#include "SpaceObjectsData.h"
#include "Improvable.h"


namespace global {
const float DEF_PERIOD = 5.f;
}

class ImprovementsData : public SpaceObjectsData
{
public:
    void setPlayerData(PlayerData *value);

    void setAsteroidsData(AsteroidsData *value);

    void setCurrentTarget(size_t indx);

    void activate(size_t indx);

    void remove(size_t num) override;

    void update(float dt) override;

    bool getStage(size_t indx);

    void add(Vector2d position, Vector2d velocity, SpriteData *sprite_data, Destructible *type, Improvable *imprv_type);

    void collisionHandler(vector<OverlappedPair> &overlapped_indxs, SpaceObjectsData &targets, float dt) override;

    PlayerData *getPlayerData();

    AsteroidsData *getAsteroidsData();

    Improvable *getType(size_t indx);

private:
    vector<Improvable *> m_types;
    vector<float> m_periods;
    vector<bool> m_stages;

    size_t m_current_target_indx = 0ull;
    PlayerData *m_owners = nullptr;
    AsteroidsData *m_targets = nullptr;
};

#endif // IMPROVEMENTSDATA_H
