#pragma once
#include <iostream>
#include "../glm/glm.hpp"
#include "Ray.h"
//Entity is the parent class of all possible objects that can be part of the scene
//These objects include camera, light, plane, sphere and mesh
//Physical objects should have a bool method that can determine if they get hit
//Camera should always return false as it never needs to be hit by a ray
//Light would need to return true only if nothing is between it and the reflected ray shot from the camera

using namespace glm;

class Entity
{
private:
	std::string type;

public:
	Entity();
	Entity(std::string shape);
	~Entity();

	std::string getType();

	virtual bool collidedWithRay(Ray r) = 0;
	virtual float distanceFromPoint(Ray r) = 0;
	virtual vec3 fragPosition(Ray r) = 0;
	virtual vec3 getNormal(Ray r) = 0;

	virtual vec3 getAmbient() = 0;
	virtual vec3 getDiffuse() = 0;
	virtual vec3 getSpecular() = 0;
	virtual float getShinyness() = 0;

};

