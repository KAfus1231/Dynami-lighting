#include "Entity.h"

Entity::Entity()
{
}

Entity::~Entity()
{
}

sf::RectangleShape Entity::getHitbox()
{
    return hitbox;
}
