#include <vector>
#include "game.hpp"
#include "objects.hpp"

#define MAX_FRAME_SAMPLES 30
#define RIGID_BODY 0x01

extern float SCALE;

Game::Game(sf::RenderWindow& _window, b2World& _world, sf::View& _view) : window(_window), world(_world), view(_view) {
    frames_count = 0;
    fps = 0.0f;
    width = (int)window.getSize().x;
    height = (int)window.getSize().y;
}

int Game::start() {
    sf::Vector2f target_center;
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

    sf::Texture ground;
    ground.loadFromFile("box.png");

    sf::Texture player_texture;
    player_texture.loadFromFile("player.png");

    RigidBody body = RigidBody(world, 0, 568, 256, 32, ground);
    RigidBody body2 = RigidBody(world, 128, 128, 128, 32, ground);
    RigidBody body3 = RigidBody(world, 416, 416, 64, 32, ground);
    RigidBody body4 = RigidBody(world, 0, 0, 568, 32, ground);
    RigidBody body5 = RigidBody(world, 288, 480, 64, 32, ground);
    RigidBody body6 = RigidBody(world, 568, 480, 64, 32, ground);
    RigidBody body7 = RigidBody(world, 696, 480, 64, 32, ground);
    RigidBody body8 = RigidBody(world, 824, 480, 64, 32, ground);
    RigidBody body9 = RigidBody(world, 1024, 568, 256, 32, ground);
    Player player = Player(world, 32, 256, player_texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                    player.move(Player::DIRECTION_LEFT);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    player.move(Player::DIRECTION_RIGHT);
                }
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                    player.jump();
                }
            }
            if (event.type == sf::Event::KeyReleased) {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    player.move(Player::DIRECTION_NONE);
                }
            }
        }

        sprintf(fps_buff, "FPS: %3.2f", framesPerSecond(clock));
        fps_text.setString(sf::String(fps_buff));

        world.Step(1.0f/60.f, 8, 3);

        window.clear(sf::Color::Black);
        window.setView(view);
        player.update();
        target_center = player.get_center();
        view.setCenter(target_center.x, target_center.y);

        body.draw(window);
        body2.draw(window);
        body3.draw(window);
        body4.draw(window);
        body5.draw(window);
        body6.draw(window);
        body7.draw(window);
        body8.draw(window);
        body9.draw(window);

        player.draw(window);

        window.setView(window.getDefaultView());
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
