#ifndef GAME_H
#define GAME_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Game {
    public:
        Game(sf::RenderWindow& _window);
        ~Game();

        int start();
    private:
        int frames_count;
        float fps;
        sf::RenderWindow& window;

        float framesPerSecond(sf::Clock& clock);
        void createGround(int x, int y, int width, int height);
};
#endif
