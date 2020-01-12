#include "SpaceObjectsData.h"
#include "GlobalSettings.h"

using namespace global;

void SpaceObjectsData::setPosition(size_t indx, Vector2d value)
{
    m_positions[indx] = value;
}

void SpaceObjectsData::setVelocity(size_t indx, Vector2d value)
{
    m_velocities[indx] = value;
}

void SpaceObjectsData::setSpriteData(size_t indx, SpriteData *value)
{
    m_sprite_datas[indx] = value;
}

void SpaceObjectsData::setRadius(size_t indx, float value)
{
    m_radiuses[indx] = value;
}

const Vector2d &SpaceObjectsData::getPosition(size_t indx) const
{
    return m_positions[indx];
}

const Vector2d &SpaceObjectsData::getVelocity(size_t indx) const
{
    return m_velocities[indx];
}

const SpriteData *SpaceObjectsData::getSpriteData(size_t indx) const
{
    return m_sprite_datas[indx];
}

const Destructible *SpaceObjectsData::getDestructibleType(size_t indx) const
{
    return m_destr_types[indx];
}

float SpaceObjectsData::getRadius(size_t indx) const
{
    return m_radiuses[indx];
}

float SpaceObjectsData::left(size_t indx)
{
    return m_positions[indx].m_x - m_radiuses[indx];
}

float SpaceObjectsData::top(size_t indx)
{
    return m_positions[indx].m_y - m_radiuses[indx];
}

float SpaceObjectsData::right(size_t indx)
{
    return m_positions[indx].m_x + m_radiuses[indx];
}

float SpaceObjectsData::bottom(size_t indx)
{
    return m_positions[indx].m_y + m_radiuses[indx];
}

void SpaceObjectsData::draw() {
    for (size_t indx = 0ULL; indx < m_sprite_datas.size(); indx++) {
        if (!m_destr_types[indx]->isDestroyed())
            drawSprite(m_sprite_datas[indx]->sprite,
                       m_positions[indx].m_x - m_radiuses[indx] - setting("cam_offset_x"),
                       m_positions[indx].m_y - m_radiuses[indx] - setting("cam_offset_y"));
    }
}

void SpaceObjectsData::wrapCoordinates()
{
    for (size_t indx = 0ULL; indx < m_positions.size(); indx++) {
        if (!m_destr_types[indx]->isDestroyed()) {
            if (right(indx) < 0.f)                  m_positions[indx].m_x += setting("map_width")  + m_radiuses[indx] * 2.f;
            if (left(indx) > setting("map_width"))  m_positions[indx].m_x -= setting("map_width")  + m_radiuses[indx] * 2.f;
            if (bottom(indx) < 0.f)                 m_positions[indx].m_y += setting("map_height") + m_radiuses[indx] * 2.f;
            if (top(indx) > setting("map_height"))  m_positions[indx].m_y -= setting("map_height") + m_radiuses[indx] * 2.f;
        }
    }
}

void SpaceObjectsData::changeDestructibleType(size_t indx, Destructible *stage) {
    delete m_destr_types[indx];
    m_destr_types[indx] = stage;
}

void SpaceObjectsData::destroy(size_t indx) {
    if (indx < m_destr_types.size())
        m_destr_types[indx]->destroy(indx, *this);
}

void SpaceObjectsData::restore(size_t indx) {
    if (indx < m_destr_types.size())
        m_destr_types[indx]->restore(indx, *this);
}

void SpaceObjectsData::placeObjects(Vector2d center, float radius)
{
    float obj_w = m_radiuses[0] * 2.f;
    float obj_h = m_radiuses[0] * 2.f;

    size_t grid_w = size_t(setting("map_width")   / obj_w);
    size_t grid_h = size_t(setting("map_height")  / obj_h);

    size_t grid_size = grid_w * grid_h;
    vector<Vector2d> grid(grid_size);

    for (Vector2d &pos : grid) pos = { -1.f, -1.f };

    for (size_t indx = 0; indx < m_positions.size(); indx++) {
        Vector2d indexes = { random(0, grid_w), random(0, grid_h) }; // indexes in grid
        Vector2d position = { indexes.m_x * obj_w, indexes.m_y * obj_h }; // real positions of objects

        Vector2d &cell_ref = grid[grid_w * indexes.m_y + indexes.m_x];

        if ((cell_ref.m_x < 0.f && cell_ref.m_y < 0.f) && (center.distanceTo(position) > radius)) {
            cell_ref = m_positions[indx];
            m_positions[indx] = position;
        }
        else {
            indx--;
        }
    }

}

void SpaceObjectsData::update(float dt)
{
    for (size_t indx = 0ULL; indx < m_positions.size(); indx++) {
        if (!m_destr_types[indx]->isDestroyed())
            m_positions[indx] += m_velocities[indx] * dt;
    }
    wrapCoordinates();
}

void SpaceObjectsData::add(Vector2d position, Vector2d velocity, SpriteData *sprite_data, Destructible *type)
{
    m_positions.push_back(position);
    m_velocities.push_back(velocity);
    m_sprite_datas.push_back(sprite_data);
    m_radiuses.push_back((sprite_data->width + sprite_data->height) / 2.f / 2.f);
    m_destr_types.push_back(type);
}

void SpaceObjectsData::remove(size_t num)
{
    for (size_t i = 0ull; i < num; i++) {
        m_positions.pop_back();
        m_velocities.pop_back();
        m_radiuses.pop_back();
        m_sprite_datas.pop_back();
        delete m_destr_types.back();
        m_destr_types.pop_back();
    }
}

vector<SpaceObjectsData::OverlappedPair> SpaceObjectsData::overlapping()
{
    vector<OverlappedPair> overlaped_indxs;

    for (size_t indx_1 = 0ull; indx_1 < m_positions.size() - 1ull; indx_1++) {
        for (size_t indx_2 = indx_1 + 1; indx_2 < m_positions.size(); indx_2++) {
            if (!m_destr_types[indx_1]->isDestroyed() && !m_destr_types[indx_2]->isDestroyed()) {
                if (m_positions[indx_1].distanceTo(m_positions[indx_2]) < m_radiuses[indx_1] + m_radiuses[indx_2])
                    overlaped_indxs.push_back({ indx_1, indx_2 });
            }
        }
    }
    return overlaped_indxs;
}

vector<SpaceObjectsData::OverlappedPair> SpaceObjectsData::overlapping(SpaceObjectsData &targets)
{
    vector<OverlappedPair> overlaped_indxs;

    for (size_t indx_1 = 0ull; indx_1 < m_positions.size(); indx_1++) {
        for (size_t indx_2 = 0ull; indx_2 < targets.m_positions.size(); indx_2++) {
            if (!m_destr_types[indx_1]->isDestroyed() && !targets.m_destr_types[indx_2]->isDestroyed()) {
                if (m_positions[indx_1].distanceTo(targets.m_positions[indx_2]) < m_radiuses[indx_1] + targets.m_radiuses[indx_2])
                    overlaped_indxs.push_back({ indx_1, indx_2 });
            }
        }
    }
    return overlaped_indxs;
}

void SpaceObjectsData::collisionHandler(vector<OverlappedPair> &overlapped_indxs, SpaceObjectsData &targets, float dt)
{
    for (size_t indx = 0ull; indx < overlapped_indxs.size(); indx++) {
        size_t obj_indx = overlapped_indxs[indx].object;
        size_t trg_indx = overlapped_indxs[indx].target;

        float distance = m_positions[obj_indx].distanceTo(targets.m_positions[trg_indx]);
        float f = (m_radiuses[obj_indx] + targets.m_radiuses[trg_indx]) / distance;
                m_velocities[obj_indx] += (m_positions[obj_indx] - targets.m_positions[trg_indx]) * f / distance / m_radiuses[obj_indx] / dt;
        targets.m_velocities[trg_indx] -= (m_positions[obj_indx] - targets.m_positions[trg_indx]) * f / distance / targets.m_radiuses[trg_indx] / dt;
    }
}
