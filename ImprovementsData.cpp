#include "ImprovementsData.h"
#include "PlayerData.h"

void ImprovementsData::setPlayerData(PlayerData *value)
{
    m_owners = value;
}

void ImprovementsData::setAsteroidsData(AsteroidsData *value)
{
    m_targets = value;
}

void ImprovementsData::setCurrentTarget(size_t indx)
{
    m_current_target_indx = indx;
}

PlayerData *ImprovementsData::getPlayerData()
{
    return m_owners;
}

AsteroidsData *ImprovementsData::getAsteroidsData()
{
    return m_targets;
}

void ImprovementsData::activate(size_t indx)
{
    m_stages[indx] = true;
}

void ImprovementsData::add(Vector2d position, Vector2d velocity, global::SpriteData *sprite_data, Destructible *type, Improvable *imprv_type)
{
    SpaceObjectsData::add(position, velocity, sprite_data, type);

    m_types.push_back(imprv_type);
    m_periods.push_back(global::DEF_PERIOD);
    m_stages.push_back(false);
}

void ImprovementsData::remove(size_t num) {
    SpaceObjectsData::remove(num);
    for (size_t i = 0ull; i < num; i++) {
        delete m_types.back();
        m_periods.pop_back();
        m_stages.pop_back();
    }
}

void ImprovementsData::update(float dt) {
    for (size_t indx = 0ull; indx < m_types.size(); indx++) {
        if (!m_destr_types[indx]->isDestroyed() && m_stages[indx]) {

            m_types[indx]->update(indx, 0ull, m_current_target_indx, *this);
            SpaceObjectsData::update(dt);

            if((m_periods[indx] -= dt + 0.001f) <= 0.f)
                destroy(indx);
        }
    }
}

bool ImprovementsData::getStage(size_t indx)
{
    return m_stages[indx];
}

Improvable *ImprovementsData::getType(size_t indx)
{
    return m_types[indx];
}

void ImprovementsData::collisionHandler(vector<SpaceObjectsData::OverlappedPair> &overlapped_indxs, SpaceObjectsData &targets, float dt)
{
    for (size_t indx = 0ull; indx < overlapped_indxs.size(); indx++) {
        size_t imprv_indx = overlapped_indxs[indx].object;
        size_t targt_indx = overlapped_indxs[indx].target;

        if (!m_destr_types[imprv_indx]->isDestroyed() && m_stages[imprv_indx] == true)
            m_types[imprv_indx]->collision(imprv_indx, targt_indx, *this, dt);
    }
}
