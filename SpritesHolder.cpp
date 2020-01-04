#include "SpritesHolder.h"

global::SpritesHolder::~SpritesHolder()
{
    for (auto &i : m_sprites) {
        destroySprite(i.second);
    }
}

Sprite *global::SpritesHolder::load(const string &path, const string &key)
{
    Sprite* &sprite_ref = m_sprites[key];
    if (sprite_ref != nullptr)
        return sprite_ref;

    sprite_ref = createSprite(path.c_str());
    return sprite_ref;
}

Sprite *global::SpritesHolder::get(const string &key)
{
    return m_sprites[key];
}

global::SpritesHolder &global::sprites()
{
    static SpritesHolder holder;
    return holder;
}
