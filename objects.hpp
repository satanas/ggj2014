#ifndef OBJECTS_H
#define OBJECTS_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class RigidBody {
    public:
        RigidBody(b2World& _world, int x, int y, int _width, int _height, sf::Texture& _texture);
        ~RigidBody();
        int x, y, width, height;
        float m_width, m_height;

        void draw(sf::RenderWindow& window);

    private:
        b2World& world;
        b2Body* body;
        sf::Texture& texture;
        std::vector<sf::Sprite> sprites;
};

class Player {
    public:
        static const int DIRECTION_NONE = 0;
        static const int DIRECTION_LEFT = -1;
        static const int DIRECTION_RIGHT = 1;

        Player(b2World& _world, int x, int y, sf::Texture& _texture);
        ~Player();

        void draw(sf::RenderWindow& window);
        void move(int direction);
        void jump();
        void update();

    private:
        int player_width, player_height, remaining_jump_step;
        bool jumping;
        b2World& world;
        b2Body* body;
        sf::Sprite sprite;
        sf::Texture& texture;
};

#endif
