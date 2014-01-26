#include "game.hpp"

static const int TILE_SIZE = 32;

int main(int, char const**) {
    int width = 800;
    int height = 600;

    srand(time(NULL));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::View view;
    view.reset(sf::FloatRect(0, 0, width, height));

    sf::RenderWindow window(sf::VideoMode(width, height), "GGJ 2014", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    Game game(window, view);
    game.start();

    return EXIT_SUCCESS;
}
