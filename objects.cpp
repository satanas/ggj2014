#include <vector>
#include "objects.hpp"

extern float SCALE;

StaticPlatform::StaticPlatform(b2World& _world, int x, int y, int _width, int _height, sf::Texture& _texture) : world(_world), texture(_texture) {
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

void StaticPlatform::draw(sf::RenderWindow& window) {
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator) {
        //printf("%s\n", typeid(*iterator).name());
        window.draw(*iterator);
    }
}

StaticPlatform::~StaticPlatform() {}

MoveablePlatform::MoveablePlatform(b2World& _world, int x, int y, int _width, int _height, std::vector<sf::Texture>& _textures) : world(_world), textures(_textures) {
    width = _width;
    height = _height;
    x = x;
    y = y;
    speed = 2;
    delay = 2000;
    orientation = HORIZONTAL;
    direction = LEFT;
    c1 = x;
    c2 = (x + width) * 2;
    m_c1 = float(c1) / SCALE;
    m_c2 = float(c2) / SCALE;
    texture_index = Player::GREEN;
    float m_x = (x + ((float)width/2))/SCALE;
    float m_y = (y + ((float)height/2))/SCALE;
    m_width = ((float)width/2)/SCALE;
    m_height = ((float)height/2)/SCALE;

    b2BodyDef bodyDef;
    bodyDef.position = b2Vec2(m_x, m_y);
    bodyDef.type = b2_kinematicBody;
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
            sf::Sprite sp;
            sp.setTexture(textures[texture_index]);
            sp.setPosition((i * SCALE) + x, (j * SCALE) + y);
            sprites.push_back(sp);
        }
    }
}

void MoveablePlatform::draw(sf::RenderWindow& window) {
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator) {
        //printf("%s\n", typeid(*iterator).name());
        window.draw(*iterator);
    }
}

void MoveablePlatform::update_textures() {
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator) {
        iterator->setTexture(textures[texture_index]);
    }
}

void MoveablePlatform::render_textures() {
    float x_offset = 0, y_offset = 0;
    //int maxX = width / SCALE;
    //int maxY = height / SCALE;

    //sprites.clear();
    //b2Vec2 m_pos = body->GetPosition();

    //for (int i=0; i<maxX; i++) {
    //    for (int j=0; j<maxY; j++) {
    //        sf::Sprite sp;
    //        sp.setTexture(textures[texture_index]);
    //        sp.setPosition((i * SCALE) + (m_pos.x * SCALE), (j * SCALE) + (m_pos.y * SCALE));
    //        sprites.push_back(sp);
    //    }
    //}

    b2Vec2 m_pos = body->GetPosition();
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator) {
        sf::Vector2f sprite_pos = iterator->getPosition();
        x_offset = sprite_pos.x - (last_m_pos.x * SCALE);
        //y_offset = sprite_pos.y - m_pos.y;
        iterator->setPosition(x_offset + (m_pos.x * SCALE), sprite_pos.y);
        //printf("m_pos_x: %f, last_m_pos_x: %f, sprite_pos_x: %f x_offset: %f\n", m_pos.x, last_m_pos.x, sprite_pos.x, x_offset);
        //fflush(stdout);

        //if (orientation == HORIZONTAL) {
        //    x_offset = (m_pos.x * SCALE) - pos.x;
        //    iterator->move(x_offset, 0);
        //} else {
        //    y_offset = (m_pos.y * SCALE) - pos.y;
        //    iterator->move(0, y_offset);
        //}
    }
    //printf("****\n");
}

void MoveablePlatform::activate() {
    if (texture_index == Player::BLUE) return;
    texture_index = Player::BLUE;
    update_textures();
}

void MoveablePlatform::deactivate() {
    if (texture_index == Player::GREEN) return;
    texture_index = Player::GREEN;
    b2Vec2 vel = body->GetLinearVelocity();
    vel.x = 0;
    vel.y = 0;
    body->SetLinearVelocity(vel);
    update_textures();
}

void MoveablePlatform::set_delay(int _delay) {
    delay = _delay;
}

void MoveablePlatform::save_last_position() {
    b2Vec2 pos = body->GetPosition();
    last_m_pos.x = pos.x;
    last_m_pos.y = pos.y;
}

void MoveablePlatform::update() {
    if (texture_index != Player::BLUE) return;

    b2Vec2 vel = body->GetLinearVelocity();
    b2Vec2 pos = body->GetPosition();

    if (orientation == HORIZONTAL) {
        if (direction == LEFT) {
            if (pos.x <= m_c1) {
                direction = RIGHT;
                vel.x = speed;
            } else {
                vel.x = -speed;
            }
        } else if (direction == RIGHT) {
            if (pos.x >= m_c2) {
                direction = LEFT;
                vel.x = -speed;
            } else {
                vel.x = speed;
            }
        }

    }
    body->SetLinearVelocity(vel);
    render_textures();
}

MoveablePlatform::~MoveablePlatform() {}

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

Player::~Player() {}
