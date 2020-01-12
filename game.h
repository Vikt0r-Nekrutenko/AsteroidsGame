#ifndef GAME_H
#define GAME_H

#include "Framework.h"
#include "GlobalSettings.h"
#include "SpritesDataHolder.h"

#include "SpaceObjectsData.h"

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
    SpaceObjectsData asteroids;

    float dt = 0.f;
};

#endif // GAME_H
