#include "game.hpp"

int main(int, char const**) {
    int width = 800;
    int height = 600;

    srand(time(NULL));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(width, height), "GGJ 2014", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    Game game(window);
    game.start();

    return 0;
}
