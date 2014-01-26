#ifndef OBJECTS_H
#define OBJECTS_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class StaticPlatform {
    public:
        StaticPlatform(b2World& _world, int x, int y, int _width, int _height, sf::Texture& _texture);
        ~StaticPlatform();
        int x, y, width, height;
        float m_width, m_height;

        void draw(sf::RenderWindow& window);

    private:
        b2World& world;
        b2Body* body;
        sf::Texture& texture;
        std::vector<sf::Sprite> sprites;
};

class MoveablePlatform {
    public:
        static const int HORIZONTAL = 1;
        static const int VERTICAL = -1;
        static const int LEFT = -2;
        static const int RIGHT = 2;
        static const int UP = 3;
        static const int DOWN = -3;

        MoveablePlatform(b2World& _world, int x, int y, int _width, int _height, std::vector<sf::Texture>& _textures);
        ~MoveablePlatform();

        void draw(sf::RenderWindow& window);
        void set_orientation(int orientation);
        void set_direction(int direction);
        void set_range(int c1, int c2);
        void set_speed(int _speed);
        void set_delay(int delay);
        void activate();
        void deactivate();
        void update();
        void save_last_position();

    private:
        int x, y, width, height, speed, current_speed, direction, c1, c2, delay, orientation;
        float m_width, m_height, m_c1, m_c2;
        int texture_index;
        b2World& world;
        b2Body* body;
        b2Vec2 last_m_pos;
        sf::Clock clock;
        std::vector<sf::Texture>& textures;
        std::vector<sf::Sprite> sprites;

        void update_textures();
        void render_textures();
};

class Player {
    public:
        static const int DIRECTION_NONE = 0;
        static const int DIRECTION_LEFT = -1;
        static const int DIRECTION_RIGHT = 1;
        static const int GREEN = 0;
        static const int BLUE = 1;
        static const int RED = 2;

        //Player(b2World& _world, int x, int y, sf::Texture& _texture);
        Player(b2World& _world, int x, int y, std::vector<sf::Texture>& _textures);
        ~Player();

        void draw(sf::RenderWindow& window);
        void move(int direction);
        void jump();
        void update();
        void set_green();
        void set_blue();
        void set_red();
        int get_current_character();
        sf::Vector2f get_center();

    private:
        int player_width, player_height, remaining_jump_step, texture_index;
        bool jumping;
        b2World& world;
        b2Body* body;
        sf::Sprite sprite;
        //sf::Texture& texture;
        std::vector<sf::Texture>& textures;
};

#endif
