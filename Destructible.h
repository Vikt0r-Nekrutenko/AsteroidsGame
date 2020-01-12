#ifndef DESTRUCTIBLE_H
#define DESTRUCTIBLE_H

#include <stdint.h>

class SpaceObjectsData;

class Destructible
{
public:
    virtual ~Destructible() = default;
    bool isDestroyed() const;
    virtual void destroy(size_t indx, SpaceObjectsData &sod) = 0;
    virtual void restore(size_t indx, SpaceObjectsData &sod) = 0;
protected:
    bool m_is_destroyed = false;
};

class OneStageDestruction : public Destructible {
    void destroy(size_t indx, SpaceObjectsData &sod) override;
    void restore(size_t indx, SpaceObjectsData &sod) override;
};

class BigAsteroidDestruction : public Destructible {
public:
    void destroy(size_t indx, SpaceObjectsData &sod) override;
    void restore(size_t indx, SpaceObjectsData &sod) override;
};

#endif // DESTRUCTIBLE_H
