#ifndef GAME_H
#define GAME_H

#include "Framework.h"
#include "GlobalSettings.h"
#include "SpritesDataHolder.h"

#include "AsteroidsData.h"
#include "PlayerData.h"
#include "BulletsData.h"
#include "ImprovementsData.h"

namespace global {
const float CLEAR_SPACE_RADIUS = 150.f;
}

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

    void restart(vector<SpaceObjectsData::OverlappedPair> ovrlpd_indxs);
    void createImprovement(vector<SpaceObjectsData::OverlappedPair> ovrlpd_indxs);

private:
    ImprovementsData improvements;
    AsteroidsData asteroids;
    BulletsData bullets;
    PlayerData player;

    Vector2d cursor_position;
    float dt = 0.f;
};

#endif // GAME_H
