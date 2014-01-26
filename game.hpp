#ifndef GAME_H
#define GAME_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Game {
    public:
        static const int QUIT = 0;

        Game(sf::RenderWindow& _window, sf::View& _view);
        ~Game();

        int start();
    private:
        int lives;
        sf::RenderWindow& window;
        sf::View& view;

        bool over();
};
#endif
