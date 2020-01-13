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
    sprites().load("data/background.png", "map");
    sprites().load("data/big_asteroid.png", "big_asteroid");
    sprites().load("data/small_asteroid.png", "small_asteroid");
    sprites().load("data/spaceship.png", "spaceship");
    sprites().load("data/bullet.png", "bullet");
    sprites().load("data/auto_shooting.png", "auto_shooting");
    sprites().load("data/shield.png", "shield");
    sprites().load("data/rocket.png", "rocket");

    for (int i = 0; i < setting("num_asteroids"); i++)
        asteroids.add({ 0.f, 0.f }, { random(-MAX_OBJ_VELOCITY, +MAX_OBJ_VELOCITY), random(-MAX_OBJ_VELOCITY, +MAX_OBJ_VELOCITY)}, &sprites().get("big_asteroid"), new BigAsteroidDestruction);
    player.add({ setting("map_width") / 2.f, setting("map_height") / 2.f }, { 0.f, 0.f }, &sprites().get("spaceship"), new OneStageDestruction);

    player.setImprovementsData(&improvements);
    improvements.setPlayerData(&player);
    improvements.setAsteroidsData(&asteroids);

    asteroids.placeObjects(player.getPosition(0ull), CLEAR_SPACE_RADIUS);

    return true;
}

void MyFramework::Close()
{

}

bool MyFramework::Tick()
{
    auto t1 = chrono::high_resolution_clock::now();

    // drawing & updating
    {
        drawMap();

        player.draw();
        player.update(dt);

        bullets.draw();
        bullets.update(dt);

        asteroids.draw();
        asteroids.update(dt);

        improvements.draw();
        improvements.update(dt);
    }

    // collision & overlapping
    {
        // 1 STEP. between improvements & asteroids;
        vector<SpaceObjectsData::OverlappedPair> ovrlpd_imprvs_astrds = improvements.overlapping(asteroids);
        improvements.collisionHandler(ovrlpd_imprvs_astrds, asteroids, dt);

        // between improvements & player;
        vector<SpaceObjectsData::OverlappedPair> ovrlpd_imprvs_player = improvements.overlapping(player);
        player.addImprovements(ovrlpd_imprvs_player);

        // between asteroids & asteroids
        vector<SpaceObjectsData::OverlappedPair> ovrlpd_astrds = asteroids.overlapping();
        asteroids.collisionHandler(ovrlpd_astrds, asteroids, dt);

        // between bullets & asteroids
        vector<SpaceObjectsData::OverlappedPair> ovrlpd_astrds_bullts = bullets.overlapping(asteroids);
        bullets.collisionHandler(ovrlpd_astrds_bullts, asteroids, dt);

        // creation new improvement
        createImprovement(ovrlpd_astrds_bullts);

        // 2 STEP. of between improvements & asteroids;
        vector<SpaceObjectsData::OverlappedPair> ovrlpd_imprvs_astrds2 = improvements.overlapping(asteroids);
        improvements.collisionHandler(ovrlpd_imprvs_astrds2, asteroids, dt);

        // game restarting
        vector<SpaceObjectsData::OverlappedPair> ovrlpd_astrds_player = asteroids.overlapping(player);
        restart(ovrlpd_astrds_player);
    }

    this_thread::sleep_for(chrono::milliseconds(5));
    auto t2 = chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - t1);
    dt = t2.count() / 1000.f;

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
    if (isReleased) {
        switch (button) {
        case FRMouseButton::LEFT:
            bullets.add(player.getPosition(0),
                        { 4 * MAX_OBJ_VELOCITY * sinf(player.getAngle()), 4 * MAX_OBJ_VELOCITY * -cosf(player.getAngle()) },
                        &sprites().get("bullet"),
                        new OneStageDestruction);

            break;
        case FRMouseButton::RIGHT:
            player.activateImprovements();
            for (size_t indx = 0ull; indx < asteroids.size(); indx++) {
                if (cursor_position.distanceTo(asteroids.getPosition(indx)) < asteroids.getRadius(indx)) {
                    improvements.setCurrentTarget(indx);
                }
            }
            break;
        }
    }
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

void MyFramework::restart(vector<SpaceObjectsData::OverlappedPair> ovrlpd_indxs)
{
    if (!ovrlpd_indxs.empty()) {
        // player restarting
        {
            player.setPosition(0ULL, { setting("map_width") / 2.f, setting("map_height") / 2.f });
            player.setVelocity(0ULL, { 0.f, 0.f });
        }

        // asteroids restarting
        {
            asteroids.remove(asteroids.size() - setting("num_asteroids"));

            for (size_t i = 0ull; i < setting("num_asteroids"); i++) {
                asteroids.restore(i);
                asteroids.setVelocity(i, { random(-MAX_OBJ_VELOCITY, +MAX_OBJ_VELOCITY), random(-MAX_OBJ_VELOCITY, +MAX_OBJ_VELOCITY)});
            }

            asteroids.placeObjects(player.getPosition(0), CLEAR_SPACE_RADIUS);
        }

        // bullets restarting
        {
            for (size_t i = 0ull; i < setting("num_ammo"); i++) {
                bullets.destroy(i);
            }
        }

        // improvements restarting
        {
            improvements.remove(improvements.size());
        }
    }
}

void MyFramework::createImprovement(vector<SpaceObjectsData::OverlappedPair> ovrlpd_indxs)
{
    for (size_t indx = 0ull; indx < ovrlpd_indxs.size(); indx++) {
        size_t asteroid_indx = ovrlpd_indxs[indx].target;

        if (asteroids.getDestructibleType(asteroid_indx)->isDestroyed()) {
            float probability = random(0.f, 100.f);
            if(probability < setting("ability_probability") * 100.f){
                int posible_imprv = random(0.f, 3.f);
                switch (posible_imprv) {
                case 0:
                    improvements.add(asteroids.getPosition(asteroid_indx), {0,0}, &sprites().get("shield"), new OneStageDestruction, new Shield);
                    break;
                case 1:
                    improvements.add(asteroids.getPosition(asteroid_indx), {0,0}, &sprites().get("auto_shooting"), new OneStageDestruction, new AutoShooting);
                    break;
                case 2:
                    improvements.add(asteroids.getPosition(asteroid_indx), {0,0}, &sprites().get("rocket"), new OneStageDestruction, new Rocket);
                    break;
                }
            }
        }
    }
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
