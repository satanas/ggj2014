#include "game.hpp"
#include "objects.hpp"

#define MAX_FRAME_SAMPLES 30

static float SCALE = 32.0f;
static const int TILE_SIZE = 32;

Game::Game(sf::RenderWindow& _window) : window(_window) {
    frames_count = 0;
    fps = 0.0f;
}

int Game::start() {
    char fps_buff[15];

    b2Vec2 gravity(0.0f, 10.0f);
    b2World world(gravity);
    sf::Clock clock;

    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text fps_text;
    fps_text.setFont(font);
    fps_text.setCharacterSize(18);
    fps_text.setColor(sf::Color::White);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        sprintf(fps_buff, "FPS: %3.2f", framesPerSecond(clock));
        fps_text.setString(sf::String(fps_buff));

        //if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        //    int MouseX = sf::Mouse::getPosition(window).x;
        //    int MouseY = sf::Mouse::getPosition(window).y;
        //}
        world.Step(1.0f/60.f, 8, 3);

        window.clear(sf::Color::Black);
        window.draw(fps_text);
        window.display();
    }
    return EXIT_SUCCESS;
}

float Game::framesPerSecond(sf::Clock& clock) {
    frames_count++;
    if (frames_count >= MAX_FRAME_SAMPLES) {
        fps = ((float)frames_count / (float)clock.getElapsedTime().asMilliseconds()) * 1000;
        clock.restart();
        frames_count = 0;
    }
    return fps;
}

void Game::createGround(int x, int y, int tiles_width, int tiles_height) {
}

Game::~Game() {}
