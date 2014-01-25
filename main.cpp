#include "game.hpp"

float SCALE = 32.0f;
static const int TILE_SIZE = 32;

int main(int, char const**) {
    int width = 800;
    int height = 600;

    srand(time(NULL));

    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(width, height), "GGJ 2014", sf::Style::Default, settings);
    window.setFramerateLimit(60);

    b2Vec2 gravity(0.0f, 15.0f);
    b2World world(gravity);

    Game game(window, world);
    game.start();

    return 0;
}
