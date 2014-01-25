#ifndef OBJECTS_H
#define OBJECTS_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class RigidBody {
    public:
        RigidBody(b2World& _world, int x, int y, int _width, int _height);
        ~RigidBody();
        int x, y, width, height;

        sf::Sprite getSprite();

    private:
        b2World& world;
        b2Body* body;
        sf::Sprite sprite;
};

#endif
