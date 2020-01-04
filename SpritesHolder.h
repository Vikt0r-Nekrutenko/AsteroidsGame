#ifndef SPRITES_HOLDER_H
#define SPRITES_HOLDER_H


#include <map>
#include <string>
#include <Framework.h>

using std::string;
using std::map;

namespace global {
    class SpritesHolder
    {
    public:
        ~SpritesHolder();

        Sprite *load(const string &path, const string &key);
        Sprite *get(const string &key);

        SpritesHolder() = default;
        SpritesHolder(const SpritesHolder &) = delete;
        SpritesHolder(SpritesHolder &&) = delete;
        SpritesHolder &operator=(const SpritesHolder &) = delete;
        SpritesHolder &operator=(SpritesHolder &&) = delete;

    private:
        map<string, Sprite *> m_sprites;
    };

    SpritesHolder &sprites();
}

#endif // SPRITES_HOLDER_H
