#include <SFML/Graphics.hpp>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include "GameData.h"
#include "GameFunctions.h"

auto setText(sf::Text& text, const std::string& str, const sf::Font& font, int size, sf::Vector2f position, sf::Color color) ->void {
    text.setString(str);
    text.setFont(font);
    text.setCharacterSize(size);
    text.setPosition(position);
    text.setFillColor(color);
}
auto numberOfLines(const std::string& path) -> int {
    auto file = std::ifstream(path);
    auto line = std::string();
    auto lineCount = int(0);
    while (std::getline(file, line)) lineCount ++;
    return lineCount;
}
auto loadWord (const GameData& gameData) -> std::string {
    auto lineNr = rand() % gameData.wCount + 1;
    std::ifstream file("assets\\words.txt");
    std::string line;
    for(int i = 0; i < lineNr; ++i)
        std::getline(file, line);
    return line;
}
auto setWord (const GameData& gameData) -> sf::Text{
    auto tmp = sf::Text();
    setText(tmp, loadWord(gameData), gameData.gFont, gameData.wSize, sf::Vector2f(0, 0), sf::Color::Yellow);
    tmp.setPosition(-tmp.getGlobalBounds().width-10 , gameData.Y);
    return tmp;
}
auto sIndex(GameData& gameData) -> int {
    return gameData.ssIndex++;
}
auto setSaved(GameData& gameData) -> sf::Text {
    auto str = gameData.savedGame[sIndex(gameData)];
    auto tmp = sf::Text();
    auto x = float(std::stof(gameData.savedGame[sIndex(gameData)]));
    auto y = float(std::stof(gameData.savedGame[sIndex(gameData)]));
    setText(tmp, str, gameData.gFont, gameData.wSize, sf::Vector2f(x, y), sf::Color::Yellow);
    return tmp;
}
auto setScore(const GameData& gameData) -> sf::Text {
    auto tmp = sf::Text();
    setText(tmp, "Score: " + std::to_string(gameData.score), gameData.iFont, 30,sf::Vector2f(5, 680), sf::Color::White);
    return tmp;
}
auto gameOver(GameData& gameData) -> void {
    auto s = std::string();
    auto xOffset = float(0);
    auto scoreText = sf::Text();
    if(gameData.state==GameState::SAVING_GAME) {
        s = "GAME SAVED";
        xOffset = 50;
    }
    else {
        s = "GAME OVER";
        setText(scoreText, "Score: " + std::to_string(gameData.score), gameData.iFont, 50, sf::Vector2f(550, 400), sf::Color::White);
    }

    sf::Text gameOver, pressEnter;
    setText(gameOver ,s, gameData.iFont, 150, sf::Vector2f(270 - xOffset, 200), sf::Color::White);
    setText(pressEnter ,"Press Enter", gameData.iFont, 50, sf::Vector2f(530, 650),sf::Color::White);

    while (gameData.window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        gameData.window.clear();
        gameData.window.draw(gameOver);
        gameData.window.draw(scoreText);
        gameData.window.draw(pressEnter);
        gameData.window.display();
    }
    gameData.state = GameState::MENU;
}
auto bestScore(GameData& gameData) -> void{
    std::vector<int> v;
    std::vector<sf::Text> vec;
    auto bfile = std::ifstream("assets\\best.txt");
    auto s = std::string();
    auto i = std::string();
    auto count = int(0);
    while(bfile >> s){
        v.push_back(std::stoi(s));
    }
    std::ranges::sort(v, std::ranges::greater());
    if(gameData.state==GameState::SHOWING_SCORES){
        count = 0;
        auto bestY = int(100);
        for(auto b : v){
            count++;
            auto tmp = sf::Text();
            setText(tmp, std::to_string(count)+". "+std::to_string(b), gameData.iFont, 75, sf::Vector2f(400, bestY), sf::Color::White);
            bestY+=80;
            vec.push_back(tmp);
            if(count==5) break;
        }

        sf::Text topText, backText;
        setText(backText, "Back", gameData.iFont, 70, sf::Vector2f(550, 570), sf::Color::Red);
        setText(topText, "TOP 5 Scores", gameData.iFont, 80, sf::Vector2f(370, 0), sf::Color::White);

        while (gameData.window.isOpen()) {

            auto event = sf::Event();
            while (gameData.window.pollEvent(event)) {
                if (event.type == sf::Event::Closed)
                    gameData.window.close();
                else if (event.type == sf::Event::MouseButtonPressed) {
                    if (event.mouseButton.button == sf::Mouse::Left) {
                        auto mousePos = sf::Mouse::getPosition(gameData.window);
                        if (backText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                            return;
                        }
                    }
                }
            }

            gameData.window.clear(sf::Color::Black);
            for (auto tmp : vec) {
                gameData.window.draw(tmp);
            }
            gameData.window.draw(backText);
            gameData.window.draw(topText);
            gameData.window.display();
        }
    }
    else{
        auto bfile = std::ofstream("assets\\best.txt", std::ios::app);
        bfile<<gameData.score<<" ";
    }
}
auto escInfo(GameData& gameData) -> void{
    sf::Text setSize, small, medium, setFont, big, arial, roboto, coffeespark, save, pressEnter;
    setText(setSize ,"Quick setting font size:", gameData.iFont, 40, sf::Vector2f(400 , 60), sf::Color::White);
    setText(small ,"Lctrl + 1 - Set small font size", gameData.iFont, 30, sf::Vector2f(410 , 110), sf::Color::White);
    setText(medium ,"Lctrl + 2 - Set medium font size", gameData.iFont, 30, sf::Vector2f(410 , 160), sf::Color::White);
    setText(big ,"Lctrl + 3 - Set big font size", gameData.iFont, 30, sf::Vector2f(410,  210), sf::Color::White);
    setText(setFont ,"Quick setting font:", gameData.iFont, 40, sf::Vector2f(400 , 310), sf::Color::White);
    setText(arial ,"Lctrl + Q - Set Arial font", gameData.iFont, 30, sf::Vector2f(410 , 360), sf::Color::White);
    setText(roboto ,"Lctrl + W - Set Roboto font", gameData.iFont, 30, sf::Vector2f(410 , 410), sf::Color::White);
    setText(coffeespark ,"Lctrl + E - Set CoffeeSpark font ", gameData.iFont, 30, sf::Vector2f(410 , 460), sf::Color::White);
    setText(save ,"Lctrl + S - Save Game ", gameData.iFont, 30, sf::Vector2f(410 , 550), sf::Color::White);
    setText(pressEnter ,"Press Enter", gameData.iFont, 50, sf::Vector2f(530, 650),sf::Color::White);
    while (gameData.window.isOpen() && !sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)) {
        gameData.window.clear();
        gameData.window.draw(setSize);
        gameData.window.draw(small);
        gameData.window.draw(medium);
        gameData.window.draw(big);
        gameData.window.draw(setFont);
        gameData.window.draw(arial);
        gameData.window.draw(roboto);
        gameData.window.draw(coffeespark);
        gameData.window.draw(save);
        gameData.window.draw(pressEnter);
        gameData.window.display();
    }
};
auto game(GameData& gameData) -> void{

    gameData.gFont.loadFromFile(gameData.gFontName);

    auto lives = int();
    std::vector<sf::Text> word(6);
    if (gameData.state!=GameState::LOADING) {
        gameData.Y = 0;
        for (auto &w: word) {
            w = setWord(gameData);
            gameData.Y += 100;
        }
        gameData.score = 0;
        lives = 5;
    }
    else{
        std::string t;
        auto file = std::ifstream("assets\\save.txt");
        gameData.ssIndex = 0;
        gameData.savedGame.clear();
        while (file >> t){
            gameData.savedGame.push_back(t);
        }
        if(gameData.savedGame.size()==22) {
            gameData.gFontName=gameData.savedGame[sIndex(gameData)];
            gameData.gFont.loadFromFile(gameData.gFontName);
            gameData.wSize=std::stoi(gameData.savedGame[sIndex(gameData)]);
            gameData.score = std::stoi(gameData.savedGame[sIndex(gameData)]);
            lives = std::stoi(gameData.savedGame[sIndex(gameData)]);
            for (auto& w: word) {
                w = setSaved(gameData);
            }
        }
        else {
            gameData.state=GameState::STARTING;
            game(gameData);
            return;
        }
    }

    auto img = sf::Texture();
    img.loadFromFile("assets\\heart.png");
    auto heart = sf::Sprite(img);
    heart.setPosition(5,650);
    heart.setScale(0.05f,0.05f);

    auto velocity = sf::Vector2f(0.25f, 0);

    sf::String playerInput;
    sf::Text playerText, saveText;
    setText(playerText, "", gameData.iFont, 50, sf::Vector2f(5,620), sf::Color::White);
    setText(saveText, "esc - controls", gameData.iFont,30, sf::Vector2f(500, 680), sf::Color::White);

    while (gameData.window.isOpen() && lives>0) {

        //Increase speed
        if(gameData.score>=50) velocity=sf::Vector2f(0.35f, 0);
        if(gameData.score>=200) velocity=sf::Vector2f(0.5f, 0);
        if(gameData.score>=600) velocity=sf::Vector2f(0.7f, 0);

        auto event = sf::Event();

        while (gameData.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                gameData.window.close();
        }
        //Quick settings
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl)){
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                gameData.wSize = int(fontSize::SMALL);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                gameData.wSize = int(fontSize::MEDIUM);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                gameData.wSize = int(fontSize::BIG);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) {
                gameData.gFontName="assets\\Arial.ttf";
                gameData.gFont.loadFromFile(gameData.gFontName);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
                gameData.gFontName="assets\\Roboto.ttf";
                gameData.gFont.loadFromFile(gameData.gFontName);
            }
            else if(sf::Keyboard::isKeyPressed(sf::Keyboard::E)) {
                gameData.gFontName="assets\\CoffeeSpark.ttf";
                gameData.gFont.loadFromFile(gameData.gFontName);
            }
                //Save game
            else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)){
                auto file = std::ofstream("assets\\save.txt");
                file<<gameData.gFontName<<" "<<gameData.wSize<<" "<<gameData.score<<" "<<lives<<" ";
                for(auto tmp : word){
                    std::string s = tmp.getString();
                    auto p = tmp.getPosition();
                    file<<s<<" "<<p.x<<" "<<p.y<<" ";
                }
                file.close();
                gameData.state=GameState::SAVING_GAME;
                gameOver(gameData);
                return;
            }
            for (auto &w: word) {
                w.setCharacterSize(gameData.wSize);
                w.setFont(gameData.gFont);
            }
        }
        else if (sf::Keyboard::isKeyPressed((sf::Keyboard::Escape))) {
            escInfo(gameData);
        }
            //Player input
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            for (auto& tmp : word) {
                if(tmp.getString()==playerText.getString()){
                    gameData.score+=tmp.getString().getSize();
                    tmp.setString(loadWord(gameData));
                    auto position = tmp.getPosition();
                    position.x = -tmp.getGlobalBounds().width-10;
                    tmp.setPosition(position);
                }
            }
            playerInput="";
            playerText.setString("");
        }
            //https://en.sfml-dev.org/forums/index.php?topic=19965.0
        else if (event.type == sf::Event::TextEntered ){
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::BackSpace)){
                if(!playerInput.isEmpty()){
                    playerInput.erase(playerInput.getSize()-1);
                    playerText.setString(playerInput);
                }
            }
            else {
                playerInput += event.text.unicode;
                playerText.setString(playerInput);
            }
        }

        //Move words
        for (auto& w : word) {
            auto position = w.getPosition();
            position += velocity;
            if (position.x > gameData.window.getSize().x) {
                lives--;
                position.x=-500;
                w.setString(loadWord(gameData));
            }
            w.setPosition(position);
        }
        //Draw words
        gameData.window.clear(sf::Color::Black);
        for (auto tmp : word) {
            gameData.window.draw(tmp);
        }
        //Draw lives
        for (int i = 0; i < lives; ++i) {
            gameData.window.draw(heart);
            heart.setPosition((1200-i*75),650);
        }
        //Draw score
        gameData.window.draw(setScore(gameData));
        //Draw save info
        gameData.window.draw(saveText);
        //Draw player text
        gameData.window.draw(playerText);
        gameData.window.display();
    }
    gameData.state=GameState::SAVING_SCORE;
    bestScore(gameData);
    gameOver(gameData);
}
auto settings(GameData& gameData) -> void{

    sf::Font testFont, arial, roboto, coffeespark;
    testFont.loadFromFile(gameData.gFontName);;
    arial.loadFromFile("assets\\Arial.ttf");
    roboto.loadFromFile("assets\\Roboto.ttf");
    coffeespark.loadFromFile("assets\\CoffeeSpark.ttf");

    sf::Text arialText, robotoText, coffeesparkText, backText, smallText, midText, bigText;
    setText(arialText, "Arial", arial, 50, sf::Vector2f(350, 145), sf::Color::Red);
    setText(robotoText, "Roboto", roboto, 50, sf::Vector2f(310, 270), sf::Color::Red);
    setText(coffeesparkText, "Coffee Spark", coffeespark, 50, sf::Vector2f(250, 395), sf::Color::Red);
    setText(smallText, "Small", testFont, 50, sf::Vector2f(720, 150), sf::Color::Red);
    setText(midText, "Medium", testFont, 75, sf::Vector2f(650, 255), sf::Color::Red);
    setText(bigText, "Big", testFont, 100, sf::Vector2f(710, 360), sf::Color::Red);
    setText(backText, "Back", gameData.iFont, 70, sf::Vector2f(550, 570), sf::Color::Red);

    while (gameData.window.isOpen()) {
        auto ac = gameData.gFontName=="assets\\Arial.ttf" ? sf::Color::Green : sf::Color::White ;
        auto rc = gameData.gFontName=="assets\\Roboto.ttf" ? sf::Color::Green : sf::Color::White;
        auto cc = gameData.gFontName=="assets\\CoffeeSpark.ttf" ? sf::Color::Green : sf::Color::White;
        arialText.setFillColor(ac);
        robotoText.setFillColor(rc);
        coffeesparkText.setFillColor(cc);
        auto ss = gameData.wSize==int(fontSize::SMALL)? sf::Color::Green : sf::Color::White ;
        auto ms = gameData.wSize==int(fontSize::MEDIUM) ? sf::Color::Green : sf::Color::White;
        auto bs = gameData.wSize==int(fontSize::BIG) ? sf::Color::Green : sf::Color::White;
        smallText.setFillColor(ss);
        midText.setFillColor(ms);
        bigText.setFillColor(bs);
        auto event = sf::Event();
        while (gameData.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameData.window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePos = sf::Mouse::getPosition(gameData.window);
                    if (arialText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        gameData.gFontName="assets\\Arial.ttf";
                        testFont.loadFromFile(gameData.gFontName);
                    }
                    else if (robotoText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        gameData.gFontName="assets\\Roboto.ttf";
                        testFont.loadFromFile(gameData.gFontName);
                    }
                    else if (coffeesparkText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        gameData.gFontName="assets\\CoffeeSpark.ttf";
                        testFont.loadFromFile(gameData.gFontName);
                    }
                    else if (smallText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        gameData.wSize=int(fontSize::SMALL);
                    }
                    else if (midText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        gameData.wSize=int(fontSize::MEDIUM);
                    }
                    else if (bigText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        gameData.wSize=int(fontSize::BIG);
                    }
                    else if (backText.getGlobalBounds().contains({static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)})) {
                        return;
                    }
                }
            }
        }
        gameData.window.clear(sf::Color::Black);
        gameData.window.draw(arialText);
        gameData.window.draw(robotoText);
        gameData.window.draw(coffeesparkText);
        gameData.window.draw(backText);
        gameData.window.draw(smallText);
        gameData.window.draw(midText);
        gameData.window.draw(bigText);
        gameData.window.display();
    }
}
auto menu(GameData& gameData) -> void{

    sf::Text playText, loadText, bestText, settText, exText;
    setText(playText, "Play", gameData.iFont, 70, sf::Vector2f(550, 60), sf::Color::Red);
    setText(loadText, "Load game", gameData.iFont, 70, sf::Vector2f(470, 185), sf::Color::Red);
    setText(bestText, "Best scores", gameData.iFont, 70, sf::Vector2f(450, 310), sf::Color::Red);
    setText(settText, "Settings", gameData.iFont, 70, sf::Vector2f(490, 435), sf::Color::Red);
    setText(exText, "Exit", gameData.iFont, 70, sf::Vector2f(550, 550), sf::Color::Red);

    while (gameData.window.isOpen()) {
        auto event = sf::Event();
        while (gameData.window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                gameData.window.close();
            }
            else if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) {
                    auto mousePos = sf::Mouse::getPosition(gameData.window);
                    if (playText.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                        gameData.state=GameState::STARTING;
                        game(gameData);
                    }
                    else if (loadText.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                        gameData.state=GameState::LOADING;
                        game(gameData);
                    }
                    else if (bestText.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})) {
                        gameData.state=GameState::SHOWING_SCORES;
                        bestScore(gameData);
                    }
                    else if(settText.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        settings(gameData);
                    }
                    else if(exText.getGlobalBounds().contains({static_cast<float>(mousePos.x),static_cast<float>(mousePos.y)})){
                        return;
                    }
                }
            }
        }
        gameData.window.clear(sf::Color::Black);
        gameData.window.draw(playText);
        gameData.window.draw(loadText);
        gameData.window.draw(bestText);
        gameData.window.draw(settText);
        gameData.window.draw(exText);
        gameData.window.display();
    }
}