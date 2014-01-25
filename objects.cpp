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

    //groundTexture->create(width, height);

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

//sf::Sprite& RigidBody::getSprite() {
void RigidBody::draw(sf::RenderWindow& window) {
    //groundTexture->clear(sf::Color::Red);

    //int max = sprites.size();
    //for (int i=0; i<max; i++) {
    //    groundTexture->draw(*sprites[i]);
    //}
    std::vector<sf::Sprite>::iterator iterator;
    for (iterator = sprites.begin(); iterator != sprites.end(); ++iterator) {
        //printf("%s\n", typeid(*iterator).name());
        //groundTexture->draw(*iterator);
        window.draw(*iterator);
    }
    //groundTexture->display();

    //sprite.setTexture(groundTexture->getTexture());
    //sprite.setTexture(texture);
    //sprite.setOrigin(0, 0);
    //sprite.setPosition(SCALE * body->GetPosition().x, SCALE * body->GetPosition().y);
    //window.draw(sprite);
    //return sprite;
}

RigidBody::~RigidBody() {}
