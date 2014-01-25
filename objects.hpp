#ifndef OBJECTS_H
#define OBJECTS_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class RigidBody {
    public:
        RigidBody(b2World& _world, int x, int y, int _width, int _height, sf::Texture& _texture);
        ~RigidBody();
        int x, y, width, height;
        float mWidth, mHeight;

        //sf::Sprite& getSprite();
        void draw(sf::RenderWindow& window);

    private:
        b2World& world;
        b2Body* body;
        sf::Sprite sprite;
        sf::Texture& texture;
        sf::RenderTexture* groundTexture;
        std::vector<sf::Sprite> sprites;
};

#endif
