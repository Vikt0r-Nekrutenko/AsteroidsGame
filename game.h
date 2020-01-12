#ifndef GAME_H
#define GAME_H

#include "Framework.h"
#include "GlobalSettings.h"
#include "SpritesDataHolder.h"

#include "AsteroidsData.h"
#include "PlayerData.h"
#include "BulletsData.h"

class ImprovementsData : public SpaceObjectsData
{
public:

private:
    vector<float> m_periods;
    vector<bool> m_stages;
};

class MyFramework : public Framework {
public:
    void PreInit(int &width, int &height, bool &fullscreen) override;
    bool Init() override;
    bool Tick() override;
    void Close() override;
    void onKeyPressed(FRKey k) override;
    void onKeyReleased(FRKey k) override;
    void onMouseMove(int x, int y, int xrelative, int yrelative) override;
    void onMouseButtonClick(FRMouseButton button, bool isReleased) override;
    const char * GetTitle() override;

private:
    ImprovementsData improvements;
    AsteroidsData asteroids;
    BulletsData bullets;
    PlayerData player;

    Vector2d cursor_position;
    float dt = 0.f;
};

#endif // GAME_H
