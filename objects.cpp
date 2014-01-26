#include "objects.hpp"

extern float SCALE;

RigidBody::RigidBody(b2World& _world, int x, int y, int _width, int _height, sf::Texture& _texture) : world(_world), texture(_texture) {
    width = _width;
    height = _height;
    float m_x = (x + ((float)width/2))/SCALE;
    float m_y = (y + ((float)height/2))/SCALE;
    m_width = ((float)width/2)/SCALE;
    m_height = ((float)height/2)/SCALE;

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(m_x, m_y);
    bodyDef.type = b2_staticBody;
    body = world.CreateBody(&bodyDef);

    b2PolygonShape shape;
    shape.SetAsBox(m_width, m_height);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.0f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    int maxX = width / SCALE;
    int maxY = height / SCALE;
    for (int i=0; i<maxX; i++) {
        for (int j=0; j<maxY; j++) {
            sf::Sprite sp(texture);
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
    player_width = 32;
    player_height = 32;
    remaining_jump_step = 0;
    jumping = false;
    float m_x = (x + ((float)player_width / 2)) / SCALE;
    float m_y = (y + ((float)player_height / 2)) / SCALE;

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(m_x, m_y);
    bodyDef.type = b2_dynamicBody;
    body = world.CreateBody(&bodyDef);
    body->SetFixedRotation(true);

    b2PolygonShape shape;
    shape.SetAsBox((player_width / 2) / SCALE, (player_height / 2) / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.1f;
    fixtureDef.friction= 0.0f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    sprite.setTexture(texture);
    sprite.setOrigin(player_width / 2, player_height / 2);
}

void Player::draw(sf::RenderWindow& window) {
    sprite.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    sprite.setRotation(body->GetAngle() * 180/b2_pi);
    //printf("%s\n", typeid(sprite).name());
    window.draw(sprite);
}

void Player::move(int direction) {
    b2Vec2 vel = body->GetLinearVelocity();
    if (direction == Player::DIRECTION_LEFT) {
        vel.x = -5;
        //body->ApplyForce(b2Vec2(0, 5), body->GetWorldCenter(), true);
    } else if (direction == Player::DIRECTION_RIGHT) {
        vel.x = 5;
        //body->ApplyForce(b2Vec2(0, -5), body->GetWorldCenter(), true);
    } else if (direction == Player::DIRECTION_NONE) {
        vel.x = 0;
        //body->SetLinearVelocity(vel);
    }
    body->SetLinearVelocity(vel);
}

void Player::jump() {
    if (!jumping) {
        remaining_jump_step = 6;
        jumping = true;
    }
}

void Player::update() {
    b2Vec2 vel = body->GetLinearVelocity();

    if (remaining_jump_step > 0) {
        body->ApplyForce(b2Vec2(0, -10), body->GetWorldCenter(), true);
        remaining_jump_step--;
    }

    if (vel.y != 0.0) {
        jumping = true;
    } else {
        jumping = false;
    }
}

sf::Vector2f Player::get_center() {
    b2Vec2 m_center = body->GetWorldCenter();
    sf::Vector2f center;
    center.x = SCALE * m_center.x;
    center.y = SCALE * m_center.y;
    return center;
}

Player::~Player() {}
