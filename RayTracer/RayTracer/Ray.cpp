#include "stdafx.h"
#include "Ray.h"


Ray::Ray()
{
	origin = vec3();
	direction = vec3();
}

Ray::Ray(vec3 orig, vec3 dir)
{
	origin = orig;
	direction = dir;
}


Ray::~Ray()
{
}

vec3 Ray::getOrigin() const
{
	return origin;
}

vec3 Ray::getDirection() const
{
	return direction;
}

vec3 Ray::getPointAlongRay(float value)
{
	return origin+direction*value;
}

Ray Ray::getRandomCloseCopy(int seed) 
{
	float offsetX;
	float offsetY;
	float offsetZ;

	srand(seed);

	offsetX = (rand() % 100) / 100.0f - 0.5f;
	offsetY = (rand() % 100) / 100.0f - 0.5f;
	offsetZ = (rand() % 100) / 100.0f - 0.5f;

    vec3 target = direction+origin;
    
	vec3 offDir = vec3(target.x + offsetX, target.y + offsetY, target.z + offsetZ);

	return Ray(origin, offDir-origin);

}
