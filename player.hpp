#ifndef PLAYER_H
#define PLAYER_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Player {
    public:
        static const int DIRECTION_NONE = 0;
        static const int DIRECTION_LEFT = -1;
        static const int DIRECTION_RIGHT = 1;
        static const int GREEN = 0;
        static const int BLUE = 1;
        static const int RED = 2;
        static const int ALIVE = 1;
        static const int DYING = 0;
        static const int DEAD = -1;

        Player(b2World& _world, int x, int y, std::vector<sf::Texture>& _textures);
        ~Player();

        void draw(sf::RenderWindow& window);
        void move(int direction);
        void jump();
        void stop();
        void update();
        void set_green();
        void set_blue();
        void set_red();
        int get_current_character();
        int get_status();
        void die();
        sf::Vector2f get_center();
        sf::Vector2f get_position();

    private:
        int width, height, remaining_jump_step, texture_index;
        bool jumping;
        int status;
        b2World& world;
        b2Body* body;
        sf::Sprite sprite;
        sf::Clock clock;
        std::vector<sf::Texture>& textures;
};

#endif
