#include "stdafx.h"
#include "EntityList.h"


EntityList::EntityList()
{
}


EntityList::~EntityList()
{
}

void EntityList::addEntity(Entity*e)
{
	list.push_back(e);
}

Entity* EntityList::getItem(int index)
{
	if(index>=0&&index<list.size())
		return list[index];

	return nullptr;
}

Entity * EntityList::getClosest(Ray r)
{
	int index = getIndexOfClosest(r);

	if(index>=0)
		return list[index];
	return nullptr;
}

int EntityList::getIndexOfClosest(Ray r, int exclude)
{
	int closest = -1;
	float distance = -1;
	float temp;

	for (int i = 0; i < list.size(); i++) {
		if (i!= exclude && list[i]->collidedWithRay(r)) {
			temp = list[i]->distanceFromPoint(r);
			if (temp>0 && (closest == -1 || temp < distance)) {
				distance = temp;
				closest = i;
			}
		}

	}
	return closest;
}

int EntityList::size()
{
	return list.size();
}
