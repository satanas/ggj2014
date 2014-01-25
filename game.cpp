#include <vector>
#include "game.hpp"
#include "objects.hpp"

#define MAX_FRAME_SAMPLES 30
#define RIGID_BODY 0x01

extern float SCALE;

Game::Game(sf::RenderWindow& _window, b2World& _world) : window(_window), world(_world) {
    frames_count = 0;
    fps = 0.0f;
    width = (int)window.getSize().x;
    height = (int)window.getSize().y;
}

int Game::start() {
    int current_ground_texture = 0;
    char fps_buff[15];

    sf::Clock clock;

    sf::Font font;
    if (!font.loadFromFile("sansation.ttf")) {
        return EXIT_FAILURE;
    }

    sf::Text fps_text;
    fps_text.setFont(font);
    fps_text.setCharacterSize(18);
    fps_text.setColor(sf::Color::White);

    //std::vector<sf::RenderTexture> groundTexture;

    sf::Texture ground;
    ground.loadFromFile("box.png");

    RigidBody body = RigidBody(world, 0, 568, 128, 32, ground);
    RigidBody body2 = RigidBody(world, 128, 128, 128, 32, ground);
    RigidBody body3 = RigidBody(world, 384, 384, 64, 64, ground);

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

        body.draw(window);
        body2.draw(window);
        body3.draw(window);

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

void Game::createRigidGround(int x, int y, int tiles_width, int tiles_height) {
}

Game::~Game() {}
