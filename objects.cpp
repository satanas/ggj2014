#include <vector>
#include "objects.hpp"
#include "player.hpp"

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
    // Define moving settings outside
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

void MoveablePlatform::set_movement(int _orientation, int starting_direction, int from_point1, int to_point2) {
    orientation = _orientation;
    direction = starting_direction;
    c1 = from_point1;
    c2 = to_point2;
    m_c1 = float(c1) / SCALE;
    m_c2 = float(c2) / SCALE;
}

void MoveablePlatform::draw(sf::RenderWindow& window) {
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator)
        window.draw(*iterator);
}

void MoveablePlatform::update_textures() {
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator)
        iterator->setTexture(textures[texture_index]);
}

void MoveablePlatform::render_textures() {
    float x_offset = 0, y_offset = 0;

    b2Vec2 m_pos = body->GetPosition();
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator) {
        sf::Vector2f sprite_pos = iterator->getPosition();
        x_offset = sprite_pos.x - (last_m_pos.x * SCALE);
        y_offset = sprite_pos.y - (last_m_pos.y * SCALE);
        iterator->setPosition(x_offset + (m_pos.x * SCALE), y_offset + (m_pos.y * SCALE));
    }
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

    } else if (orientation == VERTICAL) {
        if (direction == UP) {
            if (pos.y <= m_c1) {
                direction = DOWN;
                vel.y = speed;
            } else {
                vel.y = -speed;
            }
        } else if (direction == DOWN) {
            if (pos.y >= m_c2) {
                direction = UP;
                vel.y = -speed;
            } else {
                vel.y = speed;
            }
        }

    }
    body->SetLinearVelocity(vel);
    render_textures();
}

MoveablePlatform::~MoveablePlatform() {}

InvisiblePlatform::InvisiblePlatform(b2World& _world, int x, int y, int _width, int _height, std::vector<sf::Texture>& _textures) : world(_world), textures(_textures) {
    width = _width;
    height = _height;
    texture_index = Player::GREEN;
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
            sf::Sprite sp(textures[texture_index]);
            sp.setPosition((i * SCALE) + x, (j * SCALE) + y);
            sprites.push_back(sp);
        }
    }
}

void InvisiblePlatform::activate() {
    if (texture_index == Player::RED) return;
    texture_index = Player::RED;
    body->SetActive(false);
    update_textures();
}

void InvisiblePlatform::deactivate() {
    if (texture_index == Player::GREEN) return;
    texture_index = Player::GREEN;
    body->SetActive(true);
    update_textures();
}

void InvisiblePlatform::update_textures() {
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator)
        iterator->setTexture(textures[texture_index]);
}

void InvisiblePlatform::draw(sf::RenderWindow& window) {
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator)
        window.draw(*iterator);
}

InvisiblePlatform::~InvisiblePlatform() {}


Door::Door(b2World& _world, int x, int y, sf::Texture& _texture) : world(_world), texture(_texture) {
    width = 64;
    height = 64;
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
    fixtureDef.isSensor = true;
    body->CreateFixture(&fixtureDef);

    sprite.setTexture(texture);
    sprite.setOrigin(width / 2, height / 2);
    sprite.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
}

void Door::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

Door::~Door() {}
