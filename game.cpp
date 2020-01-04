

#include "Framework.h"
#include "GlobalSettings.h"
#include "SpritesHolder.h"

/* Test Framework realization */
class MyFramework : public Framework {

public:

	virtual void PreInit(int& width, int& height, bool& fullscreen)
	{
        width = int(global::setting("screen_width"));
        height = int(global::setting("screen_height"));
		fullscreen = false;
	}

	virtual bool Init() {

        global::sprites().load("release/data/bullet.png", "bullet");
		return true;
	}

	virtual void Close() {

	}

	virtual bool Tick() {
        drawSprite(global::sprites().get("bullet"), 100, 100);
		return false;
	}

	virtual void onMouseMove(int x, int y, int xrelative, int yrelative) {

	}

	virtual void onMouseButtonClick(FRMouseButton button, bool isReleased) {

	}

	virtual void onKeyPressed(FRKey k) {
	}

	virtual void onKeyReleased(FRKey k) {
	}
	
	virtual const char* GetTitle() override
	{
		return "asteroids";
	}
};

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
