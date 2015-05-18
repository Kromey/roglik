#include <cstddef>

#include "entity/managers/PositionManager.h"

#define MAPBUFFER 5
#define NOVAL -1

bool operator==(const PositionComponent& lhs, const PositionComponent& rhs)
{
	//A position is the same if x1==x2 and y1==y2, but this is so obvious I
	//really don't know why I'm writing a comment to tell you that...
	return (lhs.x == rhs.x) && (lhs.y == rhs.y);
}

bool operator!=(const PositionComponent& lhs, const PositionComponent& rhs)
{
	//No reason to duplicate code, just invert the equality operator!
	return !(lhs == rhs);
}

const PositionComponent PositionManager::NULL_POS = { -1, -1 };

PositionManager::PositionManager()
{
}

int PositionManager::getX(Entity e)
{
	//Get the Entity's position and return the X component
	return getComponent(e).x;
}

void PositionManager::setX(Entity e, int x)
{
	//Get the current position
	PositionComponent pos = getComponent(e);

	//Update the X coordinate
	pos.x = x;

	//Set the new position
	setComponent(e, pos);
}

int PositionManager::getY(Entity e)
{
	//Get the Entity's position and return the Y component
	return getComponent(e).y;
}

void PositionManager::setY(Entity e, int y)
{
	//Get the current position
	PositionComponent pos = getComponent(e);

	//Update the Y coordinate
	pos.y = y;

	//Set the new position
	setComponent(e, pos);
}

bool PositionManager::isPositionOccupied(PositionComponent pos)
{
	return NULL_ENTITY != getEntityAtPosition(pos);
}

bool PositionManager::isPositionOccupied(int x, int y)
{
	//Build a PositionComponent from our x,y
	PositionComponent pos = { x, y };
	//Now use that in our already-written method
	return isPositionOccupied(pos);
}

Entity PositionManager::getEntityAtPosition(PositionComponent pos)
{
	//Scour our Entity positions for a matching position
	int idx;
	for(Entity i = 0; i < _entity_map.size(); i++)
	{
		idx = _entity_map[i];
		if(idx != NOVAL)
		{
			if(pos == _components[idx])
			{
				return i;
			}
		}
	}

	//We found no matching Entity
	return NULL_ENTITY;
}

Entity PositionManager::getEntityAtPosition(int x, int y)
{
	//Build a PositionComponent from our x,y
	PositionComponent pos = { x, y };
	//Now use that in our already-written method
	return getEntityAtPosition(pos);
}

