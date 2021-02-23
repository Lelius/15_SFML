constexpr auto SPEED_ANIMATION = 15;

#include <SFML/Graphics.hpp>
#include <string>
#include "BoxWithChips.h"
#include "SpriteHolder.h"

int initialization(SpriteHolder *);
void visualizeChips(sf::RenderWindow &, BoxWithChips *, SpriteHolder *);
int getGlobalNumInBox(sf::Vector2i, BoxWithChips *);
bool checkChipMovement(sf::RenderWindow &, int, BoxWithChips *, SpriteHolder *);
void winWindow(sf::RenderWindow &, sf::Clock, SpriteHolder *);
void moveChipAnimation(sf::RenderWindow &, int, std::string, BoxWithChips *, SpriteHolder *);

sf::Texture boxTexture;
sf::Texture chip_1_Texture, chip_2_Texture, chip_3_Texture, chip_4_Texture, chip_5_Texture;
sf::Texture chip_6_Texture, chip_7_Texture, chip_8_Texture, chip_9_Texture, chip_10_Texture;
sf::Texture chip_11_Texture, chip_12_Texture, chip_13_Texture, chip_14_Texture, chip_15_Texture;
sf::Texture restartButtonTexture, quitButtonTexture;
sf::Texture wellBlackTexture, wellWhiteTexture;

int main()
{
    // Объект, который, собственно, является главным окном приложения
    const wchar_t *nameWindow = L"Пятнашки";
    sf::RenderWindow window(sf::VideoMode(445, 495), nameWindow);
    window.setVerticalSyncEnabled(true);

    sf::Clock clock;
    clock.restart();

    auto *spriteHolder = new SpriteHolder();

    if (initialization(spriteHolder) == EXIT_FAILURE)
        return EXIT_FAILURE;

    auto *boxWithChips = new BoxWithChips(4, 4);
    boxWithChips->randomChips();

    visualizeChips(window, boxWithChips, spriteHolder);

    // Главный цикл приложения. Выполняется, пока открыто окно
    while (window.isOpen())
    {
        // Обрабатываем очередь событий в цикле
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Space:
                    boxWithChips->randomChips();
                    break;
                case sf::Keyboard::Enter:
                    boxWithChips->randomChips();
                    break;
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                default:
                    break;
                }
            }

            if (event.type == sf::Event::KeyPressed && !(boxWithChips->isMatchingChips()))
            {
                switch (event.key.code)
                {
                case sf::Keyboard::Up:
                    boxWithChips->toTheUpChip();
                    break;
                case sf::Keyboard::Down:
                    boxWithChips->toTheBottomChip();
                    break;
                case sf::Keyboard::Left:
                    boxWithChips->toTheLeftChip();
                    break;
                case sf::Keyboard::Right:
                    boxWithChips->toTheRightChip();
                    break;
                case sf::Keyboard::F1:
                    boxWithChips->buildInOrderChips();
                    break;
                default:
                    break;
                }
            }

            if (event.type == sf::Event::MouseButtonPressed)
            {
                if (event.mouseButton.button == sf::Mouse::Left)
                {

                    if (sf::Mouse::getPosition(window).x >= 0 && sf::Mouse::getPosition(window).x < 332)
                        if (sf::Mouse::getPosition(window).y >= 445 && sf::Mouse::getPosition(window).y < 495)
                            boxWithChips->randomChips();
                    if (sf::Mouse::getPosition(window).x >= 333 && sf::Mouse::getPosition(window).x < 445)
                        if (sf::Mouse::getPosition(window).y >= 445 && sf::Mouse::getPosition(window).y < 495)
                            window.close();
                    if (!boxWithChips->isMatchingChips())
                        checkChipMovement(window, getGlobalNumInBox(sf::Mouse::getPosition(window), boxWithChips), boxWithChips, spriteHolder);
                }
            }

            // Пользователь нажал на «крестик» и хочет закрыть окно?
            if (event.type == sf::Event::Closed)
                // тогда закрываем его
                window.close();
        }
        // Отрисовка окна
        if (boxWithChips->isMatchingChips())
        {
            window.clear();
            winWindow(window, clock, spriteHolder);
            window.display();
        }
        else
        {
            window.clear();
            visualizeChips(window, boxWithChips, spriteHolder);
            window.display();
        }
    }

    delete spriteHolder;
    delete boxWithChips;

    return 0;
}


bool checkChipMovement(sf::RenderWindow &window, int globalNumChip, BoxWithChips *box, SpriteHolder *spriteHolder)
{
    if (globalNumChip < 0 || globalNumChip > box->getSizeBox())
        return false;
    if ((globalNumChip % box->getYNum()) > 0 && (globalNumChip - 1) == box->getPosEmptyPlace())
    {
        moveChipAnimation(window, globalNumChip, "left", box, spriteHolder);
        box->toTheLeftChip();
        return true;
    }
    if ((globalNumChip % box->getYNum()) < (box->getXNum() - 1) && (globalNumChip + 1) == box->getPosEmptyPlace())
    {
        moveChipAnimation(window, globalNumChip, "right", box, spriteHolder);
        box->toTheRightChip();
        return true;
    }
    if ((globalNumChip / box->getXNum()) > 0 && (globalNumChip - box->getXNum()) == box->getPosEmptyPlace())
    {
        moveChipAnimation(window, globalNumChip, "up", box, spriteHolder);
        box->toTheUpChip();
        return true;
    }
    if ((globalNumChip / box->getXNum()) < (box->getYNum() - 1) && (globalNumChip + box->getXNum()) == box->getPosEmptyPlace())
    {
        moveChipAnimation(window, globalNumChip, "bottom", box, spriteHolder);
        box->toTheBottomChip();
        return true;
    }
    return false;
}


void winWindow(sf::RenderWindow &winWindow, sf::Clock clock, SpriteHolder *spriteHolder)
{
    sf::Time time;
    time = clock.getElapsedTime();

    spriteHolder->setSpritePosition("box", 0, 0);
    winWindow.draw(spriteHolder->getSpriteOfHolder("box"));

    if (time.asMilliseconds() % 1000 < 500)
    {
        spriteHolder->setSpritePosition("wellBlack", 35, 45);
        winWindow.draw(spriteHolder->getSpriteOfHolder("wellBlack"));
    }
    else
    {
        spriteHolder->setSpritePosition("wellWhite", 35, 45);
        winWindow.draw(spriteHolder->getSpriteOfHolder("wellWhite"));
    }

    spriteHolder->setSpritePosition("restartButton", 0, 445);
    spriteHolder->setSpritePosition("quitButton", 333, 445);
    winWindow.draw(spriteHolder->getSpriteOfHolder("restartButton"));
    winWindow.draw(spriteHolder->getSpriteOfHolder("quitButton"));
}


int getGlobalNumInBox(sf::Vector2i posMouse, BoxWithChips *box)
{
    for (int j = 0; j < box->getYNum(); ++j)
    {
        for (int i = 0; i < box->getXNum(); ++i)
        {
            if (posMouse.x >= 15 + 105 * i && posMouse.x < 115 + 105 * i)
                if (posMouse.y >= 15 + 105 * j && posMouse.y < 115 + 105 * j)
                    return i + 4 * j;
        }
    }
    return -1;
}


void visualizeChips(sf::RenderWindow &window, BoxWithChips *box, SpriteHolder *spriteHolder)
{
    spriteHolder->setSpritePosition("box", 0, 0);

    for (int j = 0; j < box->getYNum(); ++j)
    {
        for (int i = 0; i < box->getXNum(); ++i)
        {
            int numberChip = box->getBoxWithChips()[i + (j * 4)];
            spriteHolder->setSpritePosition("chip_" + std::to_string(numberChip), float(15 + (i * 105)), float(15 + (j * 105)));
        }
    }

    spriteHolder->setSpritePosition("restartButton", 0, 445);
    spriteHolder->setSpritePosition("quitButton", 333, 445);

    window.draw(spriteHolder->getSpriteOfHolder("box"));

    for (int i = 1; i <= 15; i++)
    {
        window.draw(spriteHolder->getSpriteOfHolder("chip_" + std::to_string(i)));
    }

    window.draw(spriteHolder->getSpriteOfHolder("restartButton"));
    window.draw(spriteHolder->getSpriteOfHolder("quitButton"));
}


int initialization(SpriteHolder *spriteHolder)
{
    if (!boxTexture.loadFromFile("image/box.png"))
        return EXIT_FAILURE;
    if (!chip_1_Texture.loadFromFile("image/1_chip.png"))
        return EXIT_FAILURE;
    if (!chip_2_Texture.loadFromFile("image/2_chip.png"))
        return EXIT_FAILURE;
    if (!chip_3_Texture.loadFromFile("image/3_chip.png"))
        return EXIT_FAILURE;
    if (!chip_4_Texture.loadFromFile("image/4_chip.png"))
        return EXIT_FAILURE;
    if (!chip_5_Texture.loadFromFile("image/5_chip.png"))
        return EXIT_FAILURE;
    if (!chip_6_Texture.loadFromFile("image/6_chip.png"))
        return EXIT_FAILURE;
    if (!chip_7_Texture.loadFromFile("image/7_chip.png"))
        return EXIT_FAILURE;
    if (!chip_8_Texture.loadFromFile("image/8_chip.png"))
        return EXIT_FAILURE;
    if (!chip_9_Texture.loadFromFile("image/9_chip.png"))
        return EXIT_FAILURE;
    if (!chip_10_Texture.loadFromFile("image/10_chip.png"))
        return EXIT_FAILURE;
    if (!chip_11_Texture.loadFromFile("image/11_chip.png"))
        return EXIT_FAILURE;
    if (!chip_12_Texture.loadFromFile("image/12_chip.png"))
        return EXIT_FAILURE;
    if (!chip_13_Texture.loadFromFile("image/13_chip.png"))
        return EXIT_FAILURE;
    if (!chip_14_Texture.loadFromFile("image/14_chip.png"))
        return EXIT_FAILURE;
    if (!chip_15_Texture.loadFromFile("image/15_chip.png"))
        return EXIT_FAILURE;
    if (!restartButtonTexture.loadFromFile("image/reset.png"))
        return EXIT_FAILURE;
    if (!quitButtonTexture.loadFromFile("image/X2.png"))
        return EXIT_FAILURE;
    if (!wellBlackTexture.loadFromFile("image/well-black_380x350.png"))
        return EXIT_FAILURE;
    if (!wellWhiteTexture.loadFromFile("image/well-white_380x350.png"))
        return EXIT_FAILURE;

    spriteHolder->setSpriteInHolder("box", sf::Sprite(boxTexture));
    spriteHolder->setSpriteInHolder("chip_1", sf::Sprite(chip_1_Texture));
    spriteHolder->setSpriteInHolder("chip_2", sf::Sprite(chip_2_Texture));
    spriteHolder->setSpriteInHolder("chip_3", sf::Sprite(chip_3_Texture));
    spriteHolder->setSpriteInHolder("chip_4", sf::Sprite(chip_4_Texture));
    spriteHolder->setSpriteInHolder("chip_5", sf::Sprite(chip_5_Texture));
    spriteHolder->setSpriteInHolder("chip_6", sf::Sprite(chip_6_Texture));
    spriteHolder->setSpriteInHolder("chip_7", sf::Sprite(chip_7_Texture));
    spriteHolder->setSpriteInHolder("chip_8", sf::Sprite(chip_8_Texture));
    spriteHolder->setSpriteInHolder("chip_9", sf::Sprite(chip_9_Texture));
    spriteHolder->setSpriteInHolder("chip_10", sf::Sprite(chip_10_Texture));
    spriteHolder->setSpriteInHolder("chip_11", sf::Sprite(chip_11_Texture));
    spriteHolder->setSpriteInHolder("chip_12", sf::Sprite(chip_12_Texture));
    spriteHolder->setSpriteInHolder("chip_13", sf::Sprite(chip_13_Texture));
    spriteHolder->setSpriteInHolder("chip_14", sf::Sprite(chip_14_Texture));
    spriteHolder->setSpriteInHolder("chip_15", sf::Sprite(chip_15_Texture));
    spriteHolder->setSpriteInHolder("restartButton", sf::Sprite(restartButtonTexture));
    spriteHolder->setSpriteInHolder("quitButton", sf::Sprite(quitButtonTexture));
    spriteHolder->setSpriteInHolder("wellBlack", sf::Sprite(wellBlackTexture));
    spriteHolder->setSpriteInHolder("wellWhite", sf::Sprite(wellWhiteTexture));

    return 0;
}


void moveChipAnimation(sf::RenderWindow &window, int globalNumber, std::string direction, BoxWithChips *box, SpriteHolder *spriteHolder)
{
    int chipNumberAnimation;
    chipNumberAnimation = box->getChipTheGlobalNumber(globalNumber);

    sf::Clock clockAnimation;
    clockAnimation.restart();

    int step{};
    sf::Vector2<float> pos;
    while (step < 10)
    {
        if (clockAnimation.getElapsedTime().asMilliseconds() > SPEED_ANIMATION * step)
        {
            step += 1;

            window.clear();

            spriteHolder->setSpritePosition("box", 0, 0);

            for (int j = 0; j < box->getYNum(); ++j)
            {
                for (int i = 0; i < box->getXNum(); ++i)
                {
                    int numberChip = box->getBoxWithChips()[i + (j * 4)];
                    spriteHolder->setSpritePosition("chip_" + std::to_string(numberChip), float(15 + (i * 105)), float(15 + (j * 105)));
                }
            }

            spriteHolder->setSpritePosition("restartButton", 0, 445);
            spriteHolder->setSpritePosition("quitButton", 333, 445);

            pos = spriteHolder->getSpritePosition("chip_" + std::to_string(chipNumberAnimation));

            if (direction == "left")
            {
                spriteHolder->setSpritePosition("chip_" + std::to_string(chipNumberAnimation), pos.x - (10 * step), pos.y);
            }
            if (direction == "right")
            {
                spriteHolder->setSpritePosition("chip_" + std::to_string(chipNumberAnimation), pos.x + (10 * step), pos.y);
            }
            if (direction == "up")
            {
                spriteHolder->setSpritePosition("chip_" + std::to_string(chipNumberAnimation), pos.x, pos.y - (10 * step));
            }
            if (direction == "bottom")
            {
                spriteHolder->setSpritePosition("chip_" + std::to_string(chipNumberAnimation), pos.x, pos.y + (10 * step));
            }

            window.draw(spriteHolder->getSpriteOfHolder("box"));

            for (int i = 1; i <= 15; i++)
            {
                window.draw(spriteHolder->getSpriteOfHolder("chip_" + std::to_string(i)));
            }

            window.draw(spriteHolder->getSpriteOfHolder("restartButton"));
            window.draw(spriteHolder->getSpriteOfHolder("quitButton"));

            window.display();
        }
    }
}
