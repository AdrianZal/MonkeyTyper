#include <SFML/Graphics.hpp>
#include "GameData.h"
#include "GameFunctions.h"

auto main() -> int {
    GameData gameData;
    gameData.window.create(sf::VideoMode(1280, 720), "Monkey Typer", sf::Style::Default);
    gameData.window.setFramerateLimit(240);
    gameData.iFont.loadFromFile(gameData.iFontName);
    gameData.wCount = numberOfLines("assets\\words.txt");
    menu(gameData);
    return 0;
}
