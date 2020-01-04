#include "SpritesDataHolder.h"

global::SpritesDataHolder::~SpritesDataHolder()
{
    for (auto &i : m_sprites_data) {
        destroySprite(i.second.sprite);
    }
}

global::SpriteData &global::SpritesDataHolder::load(const string &path, const string &key)
{
    SpriteData &sprite_ref = m_sprites_data[key];
    if (sprite_ref.sprite != nullptr)
        return sprite_ref;

    sprite_ref.sprite = createSprite(path.c_str());
    getSpriteSize(sprite_ref.sprite, sprite_ref.width, sprite_ref.height);
    return sprite_ref;
}

global::SpriteData &global::SpritesDataHolder::get(const string &key)
{
    return m_sprites_data[key];
}

global::SpritesDataHolder &global::sprites()
{
    static SpritesDataHolder holder;
    return holder;
}
