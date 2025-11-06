#ifndef MONKEYTYPER_GAMEFUNCTIONS_H
#define MONKEYTYPER_GAMEFUNCTIONS_H


#include "GameData.h"

auto setText(sf::Text& text, const std::string& str, const sf::Font& font, int size, sf::Vector2f position, sf::Color color) -> void;
auto numberOfLines(const std::string& path) -> int;
auto loadWord(const GameData& gameData) -> std::string;
auto setWord(const GameData& gameData) -> sf::Text;
auto sIndex(GameData& gameData) -> int;
auto setSaved(GameData& gameData) -> sf::Text;
auto setScore(const GameData& gameData) -> sf::Text;
auto gameOver(GameData& gameData) -> void;
auto bestScore(GameData& gameData) -> void;
auto escInfo(GameData& gameData) -> void;
auto game(GameData& gameData) -> void;
auto settings(GameData& gameData) -> void;
auto menu(GameData& gameData) -> void;


#endif
