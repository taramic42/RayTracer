#pragma once
#include "Entity.h"
#include "Ray.h"
#include <vector>

using namespace std;

class EntityList
{
private:
	vector<Entity*> list;

public:
	EntityList();
	~EntityList();

	void addEntity(Entity *e);
	Entity* getItem(int index);
	Entity* getClosest(Ray r);
	int getIndexOfClosest(Ray r, int exclude = -1);

	int size();
};

