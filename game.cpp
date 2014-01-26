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

    sf::Texture ground_green;
    ground_green.loadFromFile("box-green.png");
    sf::Texture ground_red;
    ground_red.loadFromFile("box-red.png");
    sf::Texture ground_blue;
    ground_blue.loadFromFile("box-blue.png");

    std::vector<sf::Texture> ground_textures;
    ground_textures.push_back(ground_green);
    ground_textures.push_back(ground_blue);
    ground_textures.push_back(ground_red);

    sf::Texture player_green_texture;
    player_green_texture.loadFromFile("player-green.png");
    sf::Texture player_red_texture;
    player_red_texture.loadFromFile("player-red.png");
    sf::Texture player_blue_texture;
    player_blue_texture.loadFromFile("player-blue.png");

    std::vector<sf::Texture> player_textures;
    player_textures.push_back(player_green_texture);
    player_textures.push_back(player_blue_texture);
    player_textures.push_back(player_red_texture);

    StaticPlatform body = StaticPlatform(world, 0, 568, 256, 32, ground_green);
    StaticPlatform body2 = StaticPlatform(world, 128, 128, 128, 32, ground_green);
    StaticPlatform body3 = StaticPlatform(world, 416, 416, 64, 32, ground_green);
    StaticPlatform body4 = StaticPlatform(world, 0, 0, 568, 32, ground_green);
    StaticPlatform body5 = StaticPlatform(world, 288, 480, 64, 32, ground_green);
    StaticPlatform body6 = StaticPlatform(world, 568, 480, 64, 32, ground_green);
    MoveablePlatform body7 = MoveablePlatform(world, 696, 480, 64, 32, ground_textures);
    StaticPlatform body8 = StaticPlatform(world, 824, 480, 64, 32, ground_green);
    StaticPlatform body9 = StaticPlatform(world, 1024, 568, 256, 32, ground_green);

    MoveablePlatform body10 = MoveablePlatform(world, 96, 320, 96, 32, ground_textures);

    //std::vector<sf::Texture> player_textures;
    Player player = Player(world, 32, 256, player_textures);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed) {
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                    player.move(Player::DIRECTION_LEFT);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                    player.move(Player::DIRECTION_RIGHT);
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
                    player.jump();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
                    player.set_green();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
                    player.set_red();
                if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num3))
                    player.set_blue();
            }
            if (event.type == sf::Event::KeyReleased) {
                if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                    player.move(Player::DIRECTION_NONE);
                }
            }
        }

        // Save last position of moveable platforms
        body10.save_last_position();

        // Simulate physics
        world.Step(1.0f/60.f, 8, 3);

        if (player.get_current_character() == Player::BLUE) {
            //body7.activate();
            //body7.update();
            body10.activate();
            body10.update();
        } else {
            //body7.deactivate();
            body10.deactivate();
        }

        sprintf(fps_buff, "FPS: %3.2f", framesPerSecond(clock));
        fps_text.setString(sf::String(fps_buff));

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
        body10.draw(window);

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
