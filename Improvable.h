#ifndef IMPROVABLE_H
#define IMPROVABLE_H

#include <vector>
#include "SpaceObjectsData.h"

class PlayerData;
class AsteroidsData;
class ImprovementsData;

class Improvable
{
public:
    virtual ~Improvable() = default;

    virtual void update(size_t indx, size_t owner_indx, size_t targer_indx, ImprovementsData &imprvs_data) = 0;

    virtual void collision(size_t indx, size_t target_indx, ImprovementsData &imprvs_data, float dt) = 0;
};

class Shield : public Improvable
{
public:
    void update(size_t indx, size_t owner_indx, size_t targer_indx, ImprovementsData &imprvs_data) override;

    void collision(size_t indx, size_t target_indx, ImprovementsData &imprvs_data, float dt) override;
};

class AutoShooting : public Improvable
{
public:
    void update(size_t indx, size_t owner_indx, size_t targer_indx, ImprovementsData &imprvs_data) override;

    void collision(size_t indx, size_t target_indx, ImprovementsData &imprvs_data, float dt) override;
};

class Rocket : public Improvable
{
public:
    void update(size_t indx, size_t owner_indx, size_t targer_indx, ImprovementsData &imprvs_data) override;

    void collision(size_t indx, size_t target_indx, ImprovementsData &imprvs_data, float dt) override;
};

#endif // IMPROVABLE_H
