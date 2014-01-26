#include "player.hpp"

extern float SCALE;

Player::Player(b2World& _world, int x, int y, std::vector<sf::Texture>& _textures) : world(_world), textures(_textures) {
    width = 32;
    height = 64;
    status = ALIVE;
    remaining_jump_step = 0;
    texture_index = GREEN;
    jumping = false;
    float m_x = (x + ((float)width / 2)) / SCALE;
    float m_y = (y + ((float)height / 2)) / SCALE;

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(m_x, m_y);
    bodyDef.type = b2_dynamicBody;
    body = world.CreateBody(&bodyDef);
    body->SetFixedRotation(true);

    b2PolygonShape shape;
    shape.SetAsBox((width / 2) / SCALE, (height / 2) / SCALE);
    b2FixtureDef fixtureDef;
    fixtureDef.density = 0.1f;
    fixtureDef.friction= 0.7f;
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);

    sprite.setTexture(textures[texture_index]);
    sprite.setOrigin(width / 2, height / 2);
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

void Player::stop() {
    b2Vec2 vel(0, 0);
    body->SetLinearVelocity(vel);
}

void Player::jump() {
    if (!jumping) {
        remaining_jump_step = 6;
        jumping = true;
    }
}

void Player::update() {
    if (status == ALIVE) {
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
    } else if (status == DYING) {
        sf::Time time_since_dead = clock.getElapsedTime();
        fflush(stdout);
        printf("Dying... %i\n", time_since_dead.asMilliseconds());
        if ((time_since_dead.asMilliseconds()) > 2000) {
            status = DEAD;
        }
    }
}

sf::Vector2f Player::get_center() {
    b2Vec2 m_center = body->GetWorldCenter();
    sf::Vector2f center;
    center.x = SCALE * m_center.x;
    center.y = SCALE * m_center.y;
    return center;
}

sf::Vector2f Player::get_position() {
    b2Vec2 m_pos = body->GetPosition();
    sf::Vector2f pos;
    pos.x = SCALE * m_pos.x;
    pos.y = SCALE * m_pos.y;
    return pos;
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

int Player::get_status() {
    return status;
}

void Player::die() {
    if (status != ALIVE) return;

    stop();
    status = DYING;
    body->SetActive(false);
    clock.restart();
}
