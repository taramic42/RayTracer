#pragma once
#include "Entity.h"

class Plane:public Entity
{
private:
	vec3 position;
	vec3 normal;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shinyness;
	float d;

	float denominator(Ray r);
	float numerator(Ray r);

public:
	Plane();
	Plane(vec3 pos, vec3 norm, vec3 amb, vec3 diff, vec3 spec, float shine);
	~Plane();

	bool collidedWithRay(Ray r);
	float distanceFromPoint(Ray r);
	vec3 fragPosition(Ray r);
	vec3 getNormal(Ray r);

	vec3 getAmbient();
	vec3 getDiffuse();
	vec3 getSpecular();
	float getShinyness();

};

