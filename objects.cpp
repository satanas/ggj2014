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
    //bodyDef.position = b2Vec2((float)x/SCALE, (float)y/SCALE);
    bodyDef.position = b2Vec2(m_x, m_y);
    bodyDef.type = b2_staticBody;
    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(mWidth, mHeight);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    int maxX = width / SCALE;
    int maxY = height / SCALE;
    for (int i=0; i<maxX; i++) {
        for (int j=0; j<maxY; j++) {
            sf::Sprite sp(texture);
            printf("otro: %s\n", typeid(sp).name());
            sp.setPosition((i * SCALE) + x, (j * SCALE) + y);
            sprites.push_back(sp);
        }
    }
}

void RigidBody::draw(sf::RenderWindow& window) {
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator) {
        //printf("%s\n", typeid(*iterator).name());
        window.draw(*iterator);
    }
}

RigidBody::~RigidBody() {}

Player::Player(b2World& _world, int x, int y, sf::Texture& _texture) : world(_world), texture(_texture) {
    playerWidth = 32;
    playerHeight = 32;
    float m_x = (x + ((float)playerWidth / 2)) / SCALE;
    float m_y = (y + ((float)playerHeight / 2)) / SCALE;

    b2BodyDef bodyDef;
    //bodyDef.position = b2Vec2((float)x / SCALE, (float)y / SCALE);
    bodyDef.position = b2Vec2(m_x, m_y);
    bodyDef.type = b2_dynamicBody;
    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox((playerWidth / 2) / SCALE, (playerHeight / 2) / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.1f;
    fixtureDef.friction= 0.7f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    sprite.setTexture(texture);
    sprite.setOrigin(playerWidth / 2, playerHeight / 2);
}

void Player::draw(sf::RenderWindow& window) {
    printf("x: %f, y: %f\n", SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    sprite.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    sprite.setRotation(body->GetAngle() * 180/b2_pi);
    //printf("%s\n", typeid(sprite).name());
    window.draw(sprite);
    fflush(stdout);
}

Player::~Player() {}
