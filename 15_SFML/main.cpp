#include <SFML/Graphics.hpp>
#include "BoxWithChips.h"

int initialised();

sf::Texture boxTexture;
sf::Texture chip_1_Texture, chip_2_Texture, chip_3_Texture, chip_4_Texture, chip_5_Texture;
sf::Texture chip_6_Texture, chip_7_Texture, chip_8_Texture, chip_9_Texture, chip_10_Texture;
sf::Texture chip_11_Texture, chip_12_Texture, chip_13_Texture, chip_14_Texture, chip_15_Texture;

int main()
{
	// Объект, который, собственно, является главным окном приложения
	sf::RenderWindow window(sf::VideoMode(445, 495), "Пятнашки");
	window.setVerticalSyncEnabled(true);

	BoxWithChips *boxWithChips = new BoxWithChips(4, 4);

	if (initialised() == EXIT_FAILURE)
		return EXIT_FAILURE;

	sf::Sprite boxSprite(boxTexture);
	sf::Sprite chip_1_Sprite(chip_1_Texture);
	sf::Sprite chip_2_Sprite(chip_2_Texture);
	sf::Sprite chip_3_Sprite(chip_3_Texture);
	sf::Sprite chip_4_Sprite(chip_4_Texture);
	sf::Sprite chip_5_Sprite(chip_5_Texture);
	sf::Sprite chip_6_Sprite(chip_6_Texture);
	sf::Sprite chip_7_Sprite(chip_7_Texture);
	sf::Sprite chip_8_Sprite(chip_8_Texture);
	sf::Sprite chip_9_Sprite(chip_9_Texture);
	sf::Sprite chip_10_Sprite(chip_10_Texture);
	sf::Sprite chip_11_Sprite(chip_11_Texture);
	sf::Sprite chip_12_Sprite(chip_12_Texture);
	sf::Sprite chip_13_Sprite(chip_13_Texture);
	sf::Sprite chip_14_Sprite(chip_14_Texture);
	sf::Sprite chip_15_Sprite(chip_15_Texture);

	boxSprite.setPosition(0, 50);

	window.draw(boxSprite);

	// Главный цикл приложения. Выполняется, пока открыто окно
	while (window.isOpen())
	{
		// Обрабатываем очередь событий в цикле
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Пользователь нажал на «крестик» и хочет закрыть окно?
			if (event.type == sf::Event::Closed)
				// тогда закрываем его
				window.close();
		}
		// Отрисовка окна	
		window.draw(boxSprite);
		window.display();
	}

	delete[]boxWithChips;

	return 0;
}


int initialised()
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
}