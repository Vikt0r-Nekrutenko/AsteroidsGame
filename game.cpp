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
    sprites().load("release/data/spaceship.png", "spaceship");

    for (int i = 0; i < setting("num_asteroids"); i++)
        asteroids.add({ 0.f, 0.f },
                      { 0.f, 0.f },
//                      { random(-MAX_OBJ_VELOCITY, +MAX_OBJ_VELOCITY), random(-MAX_OBJ_VELOCITY, +MAX_OBJ_VELOCITY)},
                      &sprites().get("big_asteroid"), new BigAsteroidDestruction);
    player.add({ setting("map_width") / 2.f, setting("map_height") / 2.f },
               { 0.f, 0.f },
               &sprites().get("spaceship"),
               new OneStageDestruction);

    asteroids.placeObjects(player.getPosition(0ull), 150);
    return true;
}

void MyFramework::Close()
{

}

bool MyFramework::Tick()
{
    auto t1 = chrono::high_resolution_clock::now();

    drawMap();

    player.draw();
    player.update(dt);

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
    cursor_position = { float(x + setting("cam_offset_x")), float(y + setting("cam_offset_y")) };

    float dx = player.getPosition(0ull).m_x - cursor_position.m_x;
    float dy = player.getPosition(0ull).m_y - cursor_position.m_y;

    player.setAngle({ dx, dy });
}

void MyFramework::onMouseButtonClick(FRMouseButton button, bool isReleased)
{

}

void MyFramework::onKeyPressed(FRKey k)
{
    switch (k) {
    case FRKey::UP:    player.setVelocity(0ull, { 0.f, -MAX_OBJ_VELOCITY }); break;
    case FRKey::DOWN:  player.setVelocity(0ull, { 0.f, +MAX_OBJ_VELOCITY }); break;
    case FRKey::LEFT:  player.setVelocity(0ull, { -MAX_OBJ_VELOCITY, 0.f }); break;
    case FRKey::RIGHT: player.setVelocity(0ull, { +MAX_OBJ_VELOCITY, 0.f }); break;
    }
    player.setMomentum(0.f);
}

void MyFramework::onKeyReleased(FRKey k)
{
    player.setMomentum(DEF_MOMENTUM);
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
