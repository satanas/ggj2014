#include "level.hpp"
#include "game.hpp"

Game::Game(sf::RenderWindow& _window, sf::View& _view) : window(_window), view(_view) {
    lives = 0;
}

int Game::start() {
    Level level(window, view, lives, 1);

    while(1) {
        int result = level.run();
        if (result == Level::PLAYER_DEAD) {
            lives--;
            if (lives < 0) {
                bool _continue = over();
                if (_continue) {
                    lives = 3;
                    level.first();
                    continue;
                } else
                    return QUIT;
            } else {
                continue;
            }
        } else if (result == Level::CLOSE)
            return QUIT;
    }
    return QUIT;
}

Game::~Game() {}

bool Game::over() {
    sf::Clock clock;
    sf::Time elapsed;

    sf::Font regular_font;
    regular_font.loadFromFile("sansation.ttf");

    sf::Text title;
    title.setString("Game Over");
    title.setFont(regular_font);
    title.setCharacterSize(48);
    title.setColor(sf::Color::White);
    title.setPosition(300, 240);

    sf::Text instructions;
    instructions.setString("Press Escape to exit or Return to continue");
    instructions.setFont(regular_font);
    instructions.setCharacterSize(16);
    instructions.setColor(sf::Color::White);
    instructions.setPosition(270, 300);

    while (1) {
        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
                return false;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
                return false;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
                return true;
        }

        window.clear(sf::Color::Black);
        window.draw(title);
        window.draw(instructions);
        window.display();
    }
}
