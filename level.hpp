#ifndef LEVEL_H
#define LEVEL_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Level {
    public:
        static const int COMPLETED = 0x01;
        static const int PLAYER_DEAD = 0x02;
        static const int ERROR_LOADING_RESOURCES = -0x01;

        Level(sf::RenderWindow& _window, sf::View& _view, int level);
        ~Level();

        int run();
        void clear();
        void next();
        void restart();

    private:
        int current_level, frames_count;
        float fps;
        sf::Font regular_font;
        sf::View& view;
        sf::RenderWindow& window;

        float framesPerSecond(sf::Clock& clock);
        void stage_animation();
};

#endif
