#ifndef SPRITEHOLDER_H
#define SPRITEHOLDER_H

#include <map>
#include <utility>
#include <SFML/Graphics.hpp>

class SpriteHolder
{
public:
    SpriteHolder();
    ~SpriteHolder();

    sf::Sprite  getSpriteOfHolder(std::string);
    void        setSpriteInHolder(std::string, sf::Sprite);
    bool        isEmptySpriteHolder();
    void        clearSpriteHolder();
    void        deleteSpriteOfHolder(std::string);
    void        setSpritePosition(std::string, float, float);
    sf::Vector2f getSpritePosition(std::string);

protected:

private:
    std::map<std::string, sf::Sprite> mapSprite;
};

#endif // SPRITEHOLDER_H
