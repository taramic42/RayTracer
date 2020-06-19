#pragma once
#include "../glm/glm.hpp"
#include "Entity.h"

class Triangle: public Entity
{
private:
	vec3 vertex1;
	vec3 vertex2;
	vec3 vertex3;
	vec3 normal;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shinyness;

	float area(vec3 a, vec3 b, vec3 c);
	float denominator(vec3 point, vec3 norm, Ray r);
	float numerator(vec3 point, vec3 norm, Ray r);

public:
	Triangle();
	Triangle(vec3 vert1, vec3 vert2, vec3 vert3, vec3 amb, vec3 diff, vec3 spec, float shiny);
	~Triangle();

	bool collidedWithRay(Ray r);
	float distanceFromPoint(Ray r);
	vec3 fragPosition(Ray r);
	vec3 getNormal(Ray r);

	vec3 getAmbient();
	vec3 getDiffuse();
	vec3 getSpecular();
	float getShinyness();

	void setNormal(vec3 norm);
};

