#pragma once
#include "Entity.h"
class Sphere: public Entity
{
private:
	vec3 position;
	vec3 ambientColor;
	vec3 diffuseColor;
	vec3 specularColor;
	float shinyness;
	float radius;

	float getDiscriminant(Ray r, int option);

public:
	Sphere();
	Sphere(vec3 pos, vec3 amb, vec3 diff, vec3 spec, float rad, float alpha);
	~Sphere();

	vec3 getPosition();
	float getRadius();

	bool collidedWithRay(Ray r);
	float distanceFromPoint(Ray r);
	vec3 fragPosition(Ray r);
	vec3 getNormal(Ray r);

	vec3 getAmbient();
	vec3 getDiffuse();
	vec3 getSpecular();
	float getShinyness();

};

