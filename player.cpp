#include "player.hpp"

extern float SCALE;

Player::Player(b2World& _world, int x, int y, std::vector<sf::Texture>& _textures) : world(_world), textures(_textures) {
    player_width = 32;
    player_height = 64;
    remaining_jump_step = 0;
    texture_index = GREEN;
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
    fixtureDef.friction= 0.7f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    sprite.setTexture(textures[texture_index]);
    sprite.setOrigin(player_width / 2, player_height / 2);
}

Player::~Player() {}

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
    } else if (direction == Player::DIRECTION_RIGHT) {
        vel.x = 5;
    } else if (direction == Player::DIRECTION_NONE) {
        vel.x = 0;
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
        body->ApplyForce(b2Vec2(0, -25), body->GetWorldCenter(), true);
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

void Player::set_green() {
    texture_index = GREEN;
    sprite.setTexture(textures[texture_index]);
}

void Player::set_blue() {
    texture_index = BLUE;
    sprite.setTexture(textures[texture_index]);
}

void Player::set_red() {
    texture_index = RED;
    sprite.setTexture(textures[texture_index]);
}

int Player::get_current_character() {
    return texture_index;
}
