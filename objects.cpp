#include "objects.hpp"

extern float SCALE;

RigidBody::RigidBody(b2World& _world, int x, int y, int _width, int _height) : world(_world) {
    width = _width;
    height = _height;
    b2BodyDef bodyDef;
    float m_x = (x + ((float)width/2))/SCALE;
    float m_y = (y + ((float)height/2))/SCALE;
    float m_w = ((float)width/2)/SCALE;
    float m_h = ((float)height/2)/SCALE;
    bodyDef.position = b2Vec2((float)x/SCALE, (float)y/SCALE);
    bodyDef.type = b2_staticBody;
    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(m_w, m_h);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
    printf("x: %i, y: %i, m_x: %f, m_y: %f, m_w: %f, m_h: %f\n", x, y, m_x, m_y, m_w, m_h);
    fflush(stdout);
}

sf::Sprite RigidBody::getSprite() {
    sf::RenderTexture texture;
    texture.create(width, height);
    texture.clear(sf::Color::Red);
    texture.display();

    sprite.setTexture(texture.getTexture());
    sprite.setOrigin(0, 0);
    sprite.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    sprite.setRotation(180/b2_pi * body->GetAngle());
    return sprite;
}

RigidBody::~RigidBody() {}
