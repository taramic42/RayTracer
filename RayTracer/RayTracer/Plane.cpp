#include "stdafx.h"
#include "Plane.h"


float Plane::denominator(Ray r)
{
	return dot(r.getDirection(), normal);
}

float Plane::numerator(Ray r)
{
	return -dot((r.getOrigin()), normal) + dot(position, normal);
}

Plane::Plane():Entity("Plane")
{
	position = vec3(0,0,0);
	normal = vec3(0, 0, 0);
	ambient = vec3(0, 0, 0);
	diffuse = vec3(0, 0, 0);
	specular = vec3(0, 0, 0);
	shinyness = 0.0f;

}

Plane::Plane(vec3 pos, vec3 norm, vec3 amb, vec3 diff, vec3 spec, float shine):Entity("Plane")
{
	position = pos;
	normal = norm;
	ambient = amb;
	diffuse = diff;
	specular = spec;
	shinyness = shine;
	d = -dot(normal,position);
	
}


Plane::~Plane()
{
}

bool Plane::collidedWithRay(Ray r)
{
	float denom = denominator(r);

	if (abs(denom)<0.00005f)
		return false;
		
	return((numerator(r) / denom) > 0.0f);
}

float Plane::distanceFromPoint(Ray r)
{
	vec3 difference = fragPosition(r) - r.getOrigin();

	return sqrt(dot(difference,difference));
}

vec3 Plane::fragPosition(Ray r)
{
	float denom= denominator(r);

	if (abs(denom)>0.00005f) {

		float t = numerator(r) / denom;

		return r.getPointAlongRay(t);
	}

}

vec3 Plane::getNormal(Ray r)
{
	return normal;
}

vec3 Plane::getAmbient()
{
	return ambient;
}

vec3 Plane::getDiffuse()
{
	return diffuse;
}

vec3 Plane::getSpecular()
{
	return specular;
}

float Plane::getShinyness()
{
	return shinyness;
}
