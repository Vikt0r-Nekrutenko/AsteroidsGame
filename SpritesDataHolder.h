#ifndef SPRITES_HOLDER_H
#define SPRITES_HOLDER_H


#include <map>
#include <string>
#include <Framework.h>

using std::string;
using std::map;

namespace global {
    struct SpriteData
    {
        Sprite *sprite;
        int width, height;
    };

    class SpritesDataHolder
    {
    public:
        ~SpritesDataHolder();

        SpriteData &load(const string &path, const string &key);
        SpriteData &get(const string &key);

        SpritesDataHolder() = default;
        SpritesDataHolder(const SpritesDataHolder &) = delete;
        SpritesDataHolder(SpritesDataHolder &&) = delete;
        SpritesDataHolder &operator=(const SpritesDataHolder &) = delete;
        SpritesDataHolder &operator=(SpritesDataHolder &&) = delete;

    private:
        map<string, SpriteData> m_sprites_data;
    };

    SpritesDataHolder &sprites();
}

#endif // SPRITES_HOLDER_H
