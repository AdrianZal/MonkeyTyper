#ifndef MONKEYTYPER_GAMEDATA_H
#define MONKEYTYPER_GAMEDATA_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

enum class GameState {MENU, SAVING_GAME, STARTING, LOADING, SHOWING_SCORES, SAVING_SCORE};
enum class fontSize {SMALL = 50, MEDIUM = 75, BIG = 100};

struct GameData {
    sf::RenderWindow window;
    sf::Font iFont;
    sf::Font gFont;
    std::string iFontName = "assets\\Tiny5.ttf";
    std::string gFontName = "assets\\Arial.ttf";
    int wSize = int(fontSize::MEDIUM);
    int wCount = 0;
    int ssIndex = 0;
    int Y = 0;
    int score = 0;
    std::vector<std::string> savedGame;
    GameState state = GameState::MENU;
};

#endif
