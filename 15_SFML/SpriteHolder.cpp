#include "SpriteHolder.h"

SpriteHolder::SpriteHolder()
{
    //ctor
}

SpriteHolder::~SpriteHolder()
{
    //dtor
}


sf::Sprite SpriteHolder::getSpriteOfHolder(std::string nameSprite)
{
    if (!isEmptySpriteHolder())
        return mapSprite[nameSprite];
    else
        return sf::Sprite();
}


void SpriteHolder::setSpriteInHolder(std::string nameSprite, sf::Sprite sprite)
{
    mapSprite.insert(std::pair<std::string, sf::Sprite>(nameSprite, sprite));
}


bool SpriteHolder::isEmptySpriteHolder()
{
    return mapSprite.empty();
}


void SpriteHolder::clearSpriteHolder()
{
    mapSprite.clear();
}


void SpriteHolder::deleteSpriteOfHolder(std::string nameSprite)
{
    mapSprite.erase(nameSprite);
}


void SpriteHolder::setSpritePosition(std::string nameSprite, float x, float y)
{
    sf::Sprite *sprite = new sf::Sprite();

    *sprite = getSpriteOfHolder(nameSprite);
    deleteSpriteOfHolder(nameSprite);
    sprite->setPosition(x, y);
    setSpriteInHolder(nameSprite, *sprite);

    delete sprite;
}

sf::Vector2f SpriteHolder::getSpritePosition(std::string nameSprite) {
    if (!isEmptySpriteHolder())
    {
        return mapSprite[nameSprite].getPosition();
    }
    return sf::Vector2f(3000, 3000);
}
