#include "level.hpp"
#include "game.hpp"

Game::Game(sf::RenderWindow& _window, sf::View& _view) : window(_window), view(_view) {}

int Game::start() {
    Level level(window, view, 1);
    level.run();
    return 0;
}

Game::~Game() {}
