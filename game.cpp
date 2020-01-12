#include "game.h"
#include <cmath>
#include <thread>
#include "Map.h"

using namespace global;

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
    width = int(setting("screen_width"));
    height = int(setting("screen_height"));
    fullscreen = false;
}

bool MyFramework::Init()
{
    sprites().load("release/data/background.png", "map");
    sprites().load("release/data/big_asteroid.png", "big_asteroid");
    sprites().load("release/data/small_asteroid.png", "small_asteroid");

    for (int i = 0; i < setting("num_asteroids"); i++)
        asteroids.add({ 0.f, 0.f },
                      { 0.f, 0.f },
//                      { random(-MAX_OBJ_VELOCITY, +MAX_OBJ_VELOCITY), random(-MAX_OBJ_VELOCITY, +MAX_OBJ_VELOCITY)},
                      &sprites().get("big_asteroid"), new BigAsteroidDestruction);
    asteroids.placeObjects({340, 190}, 150);
    return true;
}

void MyFramework::Close()
{

}

bool MyFramework::Tick()
{
    auto t1 = chrono::high_resolution_clock::now();

    drawMap();

    asteroids.draw();
    asteroids.update(dt);

    vector<SpaceObjectsData::OverlappedPair> ovrlpd_astrds = asteroids.overlapping();
    asteroids.collisionHandler(ovrlpd_astrds, asteroids, dt);

    this_thread::sleep_for(chrono::milliseconds(5));
    auto t2 = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1);
    dt = t2.count() / 1000.f;
    printf("%.2f\r", 1.f / dt);
    return false;
}

void MyFramework::onMouseMove(int x, int y, int xrelative, int yrelative)
{

}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{

}

void MyFramework::onKeyPressed(FRKey k)
{

}

void MyFramework::onKeyReleased(FRKey k)
{

}

const char* MyFramework::GetTitle()
{
    return "asteroids";
}

int main(int argc, char *argv[])
{
    readCmdParams(argc, argv, { { "-map",                 { &setting("map_width"),    &setting("map_height")     } },
                                { "-window",              { &setting("screen_width"), &setting("screen_height")  } },
                                { "-num_asteroids",       { &setting("num_asteroids")                            } },
                                { "-num_ammo",            { &setting("num_ammo")                                 } },
                                { "-ability_probability", { &setting("ability_probability")                      } } });
	return run(new MyFramework);
}
