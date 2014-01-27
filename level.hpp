#ifndef LEVEL_H
#define LEVEL_H

#include "player.hpp"
#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Level {
    public:
        static const int COMPLETED = 0x01;
        static const int PLAYER_DEAD = 0x02;
        static const int CLOSE = 0x03;
        static const int ERROR_LOADING_RESOURCES = -0x01;

        Level(sf::RenderWindow& _window, sf::View& _view, int& lives, int level);
        ~Level();

        int run();
        void clear();
        void next();
        void restart();
        void first();

    private:
        int& lives;
        int current_level, frames_count;
        float fps;
        sf::Font regular_font;
        sf::View& view;
        sf::RenderWindow& window;
        sf::Vector2f world_limits;

        float framesPerSecond(sf::Clock& clock);
        void stage_animation();
        void check_boundaries(Player& player);
};

#endif
