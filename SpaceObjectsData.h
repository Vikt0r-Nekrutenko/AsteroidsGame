#ifndef SPACEOBJECTSDATA_H
#define SPACEOBJECTSDATA_H

#include <Vector2d.h>
#include "SpritesDataHolder.h"
#include <Destructible.h>
#include <vector>

using std::vector;
using global::SpriteData;

namespace global {
    const float MIN_OBJ_VELOCITY = 50.f;
    const float MAX_OBJ_VELOCITY = 100.f;
}

class SpaceObjectsData
{
public:
    struct OverlappedPair
    {
        size_t object;
        size_t target;
    };

    virtual ~SpaceObjectsData() = default;
    void setPosition(size_t indx, Vector2d value);
    void setVelocity(size_t indx, Vector2d value);
    void setSpriteData(size_t indx, SpriteData *value);
    void setRadius(size_t indx, float value);

    const Vector2d &getPosition(size_t indx) const;
    const Vector2d &getVelocity(size_t indx) const;
    const SpriteData *getSpriteData(size_t indx) const;
    float getRadius(size_t indx) const;

    float left(size_t indx);
    float top(size_t indx);
    float right(size_t indx);
    float bottom(size_t indx);

    void draw();
    virtual void wrapCoordinates();
    void placeObjects(Vector2d center, float radius);
    void changeDestructibleType(size_t indx, Destructible *stage);

    virtual void destroy(size_t indx);
    virtual void restore(size_t indx);

    virtual void update(float dt);

    virtual void add(Vector2d position, Vector2d velocity, SpriteData *sprite_data, Destructible *type);
    virtual void remove(size_t num);

    virtual vector<OverlappedPair> overlapping();
    virtual vector<OverlappedPair> overlapping(SpaceObjectsData &targets);
    virtual void collisionHandler(vector<OverlappedPair> &overlapped_indxs, SpaceObjectsData &targets, float dt);

protected:
    vector<Vector2d> m_positions;
    vector<Vector2d> m_velocities;
    vector<float> m_radiuses;
    vector<SpriteData *> m_sprite_datas;
    vector<Destructible *> m_destr_types;
};

#endif // SPACEOBJECTSDATA_H
