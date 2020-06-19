#pragma once
#include "../glm/glm.hpp"
#include <stdlib.h>

using namespace glm;

class Ray
{
public:
	Ray();
	Ray(vec3 orig, vec3 dir);
	~Ray();

	vec3 getOrigin() const;
	vec3 getDirection() const;
	vec3 getPointAlongRay(float value);
	Ray getRandomCloseCopy(int seed);
private:
	vec3 origin;
	vec3 direction;
};

