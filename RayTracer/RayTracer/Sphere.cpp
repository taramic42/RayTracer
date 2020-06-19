#include "stdafx.h"
#include "Sphere.h"


float Sphere::getDiscriminant(Ray r, int option)
{
	vec3 offset = r.getOrigin() - position;

	float a = dot(r.getDirection(), r.getDirection());

	if (option == 1)
		return a;

	float b = 2.0f*dot(offset, r.getDirection());

	if (option == 2)
		return b;

	float c = dot(offset, offset) - radius * radius;

	if (option == 3)
		return c;

	float discriminant = b * b - 4.0f*a*c;

	return discriminant;
}

Sphere::Sphere():Entity("Sphere")
{
	position = vec3(0,0,0);
	ambientColor = vec3(0, 0, 0);
	diffuseColor = vec3(0, 0, 0);
	specularColor = vec3(0, 0, 0);
	radius = 0.0f;
	shinyness = 0.0f;
}

Sphere::Sphere(vec3 pos, vec3 amb, vec3 diff, vec3 spec, float rad, float alpha):Entity("Sphere")
{
	position = pos;
	ambientColor = amb;
	diffuseColor = diff;
	specularColor = spec;
	radius = rad;
	shinyness = alpha;
}


Sphere::~Sphere()
{
}

vec3 Sphere::getPosition()
{
	return position;
}

float Sphere::getRadius()
{
	return radius;
}

bool Sphere::collidedWithRay(Ray r)
{
	float discriminant = getDiscriminant(r,0);

	return (discriminant > 0);

}

float Sphere::distanceFromPoint(Ray r)
{
	
	vec3 difference = fragPosition(r) - r.getOrigin();

	return sqrt(dot(difference, difference));

}

vec3 Sphere::fragPosition(Ray r)
{
	float discriminant = getDiscriminant(r,0);

	vec3 fragPos;

	if (discriminant > 0) {
		float a = getDiscriminant(r, 1);

		float b = getDiscriminant(r, 2);

		float value = (-b - sqrt(discriminant)) / (2.0*a);

		fragPos = r.getPointAlongRay(value);

		return fragPos;

	}
	return vec3(0,0,0);
}

vec3 Sphere::getNormal(Ray r)
{
	vec3 fragPos = fragPosition(r);

	if(fragPos == vec3(0,0,0))
		return vec3(0, 0, 0);

	vec3 normal = fragPos - position;

	return normal;
}

vec3 Sphere::getAmbient()
{
	return ambientColor;
}

vec3 Sphere::getDiffuse()
{
	return diffuseColor;
}

vec3 Sphere::getSpecular()
{
	return specularColor;
}

float Sphere::getShinyness()
{
	return shinyness;
}
