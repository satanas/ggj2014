#include <vector>
#include "level.hpp"
#include "objects.hpp"
#include "player.hpp"

#define MAX_FRAME_SAMPLES 30

float SCALE = 32.0f;

Level::Level(sf::RenderWindow& _window, sf::View& _view, int& lives, int level) : window(_window), view(_view), lives(lives) {
    current_level = level;
    frames_count = 0;
    fps = 0.0f;
}

Level::~Level() {}

int Level::run() {
    if(!regular_font.loadFromFile("sansation.ttf"))
        return ERROR_LOADING_RESOURCES;

    stage_animation();

    b2Vec2 gravity(0.0f, 15.0f);
    b2World world(gravity);

    sf::Clock clock;
    sf::Vector2f target_center;
    world_limits = sf::Vector2f(1376, 480);
    char fps_buff[15];

    sf::Text fps_text;
    fps_text.setFont(regular_font);
    fps_text.setPosition(0, 500);
    fps_text.setCharacterSize(18);
    fps_text.setColor(sf::Color::White);

    sf::Text lives_text;
    lives_text.setFont(regular_font);
    lives_text.setCharacterSize(18);
    lives_text.setColor(sf::Color::White);

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

    StaticPlatform body = StaticPlatform(world, 0, 96, 32, 224, ground_green);
    StaticPlatform body2 = StaticPlatform(world, 0, 320, 224, 128, ground_green);
    StaticPlatform body3 = StaticPlatform(world, 32, 96, 704, 32, ground_green);
    StaticPlatform body4 = StaticPlatform(world, 320, 320, 160, 128, ground_green);
    StaticPlatform body5 = StaticPlatform(world, 576, 320, 800, 128, ground_green);
    StaticPlatform body6 = StaticPlatform(world, 1024, 160, 96, 160, ground_green);
    StaticPlatform body8 = StaticPlatform(world, 736, 0, 672, 32, ground_green);
    StaticPlatform body9 = StaticPlatform(world, 1248, 32, 128, 128, ground_green);
    StaticPlatform body7 = StaticPlatform(world, 1376, 32, 32, 416, ground_green);
    StaticPlatform body12 = StaticPlatform(world, 736, 32, 32, 96, ground_green);

    InvisiblePlatform body11 = InvisiblePlatform(world, 704, 128, 32, 192, ground_textures);
    MoveablePlatform body10 = MoveablePlatform(world, 928, 160, 64, 32, ground_textures);
    body10.set_movement(MoveablePlatform::VERTICAL, MoveablePlatform::DOWN, 160, 256);

    Player player(world, 64, 288, player_textures);

    while (window.isOpen()) {
        sf::Event event;

        if (player.get_status() == Player::ALIVE) {
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
        } else if (player.get_status() == Player::DEAD) {
            return PLAYER_DEAD;
        }

        // Save last position of moveable platforms
        body10.save_last_position();

        // Simulate physics
        world.Step(1.0f/60.f, 8, 3);

        if (player.get_current_character() == Player::BLUE) {
            body10.activate();
            body10.update();
        } else {
            body10.deactivate();
        }

        if (player.get_current_character() == Player::RED) {
            body11.activate();
        } else {
            body11.deactivate();
        }

        sprintf(fps_buff, "FPS: %3.2f", framesPerSecond(clock));
        fps_text.setString(sf::String(fps_buff));
        sprintf(fps_buff, "x %i", lives);
        lives_text.setString(sf::String(fps_buff));

        window.clear(sf::Color::Black);

        player.update();
        check_boundaries(player);

        window.setView(view);
        if (player.get_status() == Player::ALIVE) {
            target_center = player.get_center();
            view.setCenter(target_center.x, target_center.y);
        }

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
        body11.draw(window);
        body12.draw(window);

        player.draw(window);

        window.setView(window.getDefaultView());
        window.draw(lives_text);
        window.draw(fps_text);
        window.display();
    }
    return EXIT_SUCCESS;
}

void Level::clear() {
}

void Level::next() {
    current_level++;
}

void Level::first() {
    current_level = 1;
}

void Level::restart() {
}

void Level::stage_animation() {
    sf::Clock clock;
    sf::Time elapsed;
    char level_buff[10];

    sprintf(level_buff, "Level - %i", current_level);
    sf::Text level_text;
    level_text.setString(sf::String(level_buff));
    level_text.setFont(regular_font);
    level_text.setCharacterSize(36);
    level_text.setColor(sf::Color::White);
    level_text.setPosition(330, 280);

    while (elapsed.asMilliseconds() < 3000) {
        elapsed = clock.getElapsedTime();

        window.clear(sf::Color::Black);
        window.draw(level_text);
        window.display();
    }
}

float Level::framesPerSecond(sf::Clock& clock) {
    frames_count++;
    if (frames_count >= MAX_FRAME_SAMPLES) {
        fps = ((float)frames_count / (float)clock.getElapsedTime().asMilliseconds()) * 1000;
        clock.restart();
        frames_count = 0;
    }
    return fps;
}

void Level::check_boundaries(Player& player) {
    if ((player.get_position().x > world_limits.x) || (player.get_position().y > world_limits.y))
        player.die();
}
