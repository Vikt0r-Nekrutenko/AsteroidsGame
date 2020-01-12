#include "Improvable.h"
#include "PlayerData.h"
#include "AsteroidsData.h"
#include "ImprovementsData.h"
#include <cmath>

void Shield::update(size_t indx, size_t owner_indx, size_t targer_indx, ImprovementsData &imprvs_data)
{
    imprvs_data.setPosition(indx, imprvs_data.getPlayerData()->getPosition(owner_indx));
}

void Shield::collision(size_t indx, size_t target_indx, ImprovementsData &imprvs_data, float dt)
{
    AsteroidsData &target_ref = *imprvs_data.getAsteroidsData();

    Vector2d imprv_pos = imprvs_data.getPosition(indx);
    Vector2d target_pos = target_ref.getPosition(target_indx);

    float imprv_radius = imprvs_data.getRadius(indx);
    float target_radius = target_ref.getRadius(target_indx);

    float distance = imprv_pos.distanceTo(target_pos);
    float f = (imprv_radius + target_radius) / distance;

    Vector2d target_velocity = target_ref.getVelocity(target_indx);

    target_ref.setVelocity(target_indx, target_velocity - (imprv_pos - target_pos) * f / distance / target_radius / dt);
}

void AutoShooting::update(size_t indx, size_t owner_indx, size_t targer_indx, ImprovementsData &imprvs_data)
{
    imprvs_data.setPosition(indx, imprvs_data.getPlayerData()->getPosition(owner_indx));
}

void AutoShooting::collision(size_t indx, size_t target_indx, ImprovementsData &imprvs_data, float dt)
{
    imprvs_data.getAsteroidsData()->destroy(target_indx);
}

void Rocket::update(size_t indx, size_t owner_indx, size_t targer_indx, ImprovementsData &imprvs_data)
{
    AsteroidsData &target_ref = *imprvs_data.getAsteroidsData();

    Vector2d delta_pos = target_ref.getPosition(targer_indx) - imprvs_data.getPosition(indx);

    float angle = atan2f(delta_pos.m_y, delta_pos.m_x) + atanf(45.f);

    imprvs_data.setVelocity(indx, { 2.f * global::MAX_OBJ_VELOCITY * sinf(angle),
                                    2.f * global::MAX_OBJ_VELOCITY * -cosf(angle) });

}

void Rocket::collision(size_t indx, size_t target_indx, ImprovementsData &imprvs_data, float dt)
{
    imprvs_data.getAsteroidsData()->destroy(target_indx);
    imprvs_data.destroy(indx);
}

