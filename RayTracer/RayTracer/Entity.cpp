#include "stdafx.h"
#include "Entity.h"


Entity::Entity()
{
}

Entity::Entity(std::string shape)
{
	type = shape;
}


Entity::~Entity()
{
}

std::string Entity::getType()
{
	return type;
}
