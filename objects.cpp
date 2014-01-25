#include "objects.hpp"

extern float SCALE;

RigidBody::RigidBody(b2World& _world, int x, int y, int _width, int _height, sf::Texture& _texture) : world(_world), texture(_texture) {
    width = _width;
    height = _height;
    float m_x = (x + ((float)width/2))/SCALE;
    float m_y = (y + ((float)height/2))/SCALE;
    mWidth = ((float)width/2)/SCALE;
    mHeight = ((float)height/2)/SCALE;

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2((float)x/SCALE, (float)y/SCALE);
    bodyDef.type = b2_staticBody;
    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(mWidth, mHeight);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
}

void RigidBody::draw(sf::RenderWindow& window) {
    sf::RenderTexture groundTexture;
    groundTexture.create(width, height);
    groundTexture.clear(sf::Color::Red);

    int maxX = width / SCALE;
    int maxY = height / SCALE;
    for (int i=0; i<maxX; i++) {
        for (int j=0; j<maxY; j++) {
            sf::Sprite sp(texture);
            sp.setPosition(i * SCALE, j * SCALE);
            groundTexture.draw(sp);
        }
    }
    groundTexture.display();

    sprite.setTexture(groundTexture.getTexture());
    sprite.setOrigin(0, 0);
    sprite.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    //sprite.setRotation(180/b2_pi * body->GetAngle());
    window.draw(sprite);
}

RigidBody::~RigidBody() {}
