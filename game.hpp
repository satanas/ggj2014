#ifndef GAME_H
#define GAME_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Game {
    public:
        Game(sf::RenderWindow& _window, sf::View& _view);
        ~Game();

        int start();
    private:
        int frames_count, width, height;
        float fps;
        sf::RenderWindow& window;
        sf::View& view;
        //b2World& world;

        float framesPerSecond(sf::Clock& clock);
        void createRigidGround(int x, int y, int width, int height);
};
#endif
