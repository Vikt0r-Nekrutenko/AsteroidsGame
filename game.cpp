#include "game.h"

void MyFramework::PreInit(int& width, int& height, bool& fullscreen)
{
    width = int(global::setting("screen_width"));
    height = int(global::setting("screen_height"));
    fullscreen = false;
}

bool MyFramework::Init()
{

    return true;
}

void MyFramework::Close()
{

}

bool MyFramework::Tick()
{
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
    using namespace global;

    readCmdParams(argc, argv, { { "-map",                 { &setting("map_width"),    &setting("map_height")     } },
                                { "-window",              { &setting("screen_width"), &setting("screen_height")  } },
                                { "-num_asteroids",       { &setting("num_asteroids")                            } },
                                { "-num_ammo",            { &setting("num_ammo")                                 } },
                                { "-ability_probability", { &setting("ability_probability")                      } } });
	return run(new MyFramework);
}
