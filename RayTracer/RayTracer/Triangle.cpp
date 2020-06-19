#include "stdafx.h"
#include "Triangle.h"


float Triangle::area(vec3 a, vec3 b, vec3 c)
{
	return 0.5*((b.x - a.x)*(c.y - a.y) - (c.x - a.x)*(b.y - a.y));
}

float Triangle::denominator(vec3 point, vec3 norm, Ray r)
{
	return dot(r.getDirection(), norm);
}

float Triangle::numerator(vec3 point, vec3 norm, Ray r)
{
	return dot((r.getOrigin()), norm)+dot(vertex1,norm);
}

Triangle::Triangle(): Entity("Triangle")
{
	vertex1 = vec3(0);
	vertex2 = vec3(0);
	vertex3 = vec3(0);
	normal = vec3(0);
	ambient = vec3(0);
	diffuse = vec3(0);
	specular = vec3(0);
	shinyness = 0.0f;
}

Triangle::Triangle(vec3 vert1, vec3 vert2, vec3 vert3, vec3 amb, vec3 diff, vec3 spec, float shiny):Entity("Triangle")
{

	vertex1 = vert1;
	vertex2 = vert2;
	vertex3 = vert3;
	normal = cross(vertex2-vertex1,vertex3-vertex1);
	ambient = amb;
	diffuse = diff;
	specular = spec;
	shinyness = shiny;
}


Triangle::~Triangle()
{
}

bool Triangle::collidedWithRay(Ray r)
{
	float denom = denominator(vertex1, normal, r);

	if (abs(denom) < 0.00005f) 
		return false;

	float t = numerator(vertex1, normal, r) / denom;

	if (t < 0)
		return false;

	vec3 p = r.getDirection()*t + r.getOrigin();

	vec3 edge0 = vertex2 - vertex1;
	vec3 edge1 = vertex3 - vertex2;
	vec3 edge2 = vertex1 - vertex3;
	vec3 C0 = p - vertex1;
	vec3 C1 = p - vertex2;
	vec3 C2 = p - vertex3;
	if (dot(normal, cross(edge0, C0)) > 0 && dot(normal, cross(edge1, C1)) > 0 && dot(normal, cross(edge2, C2)) > 0) 
		return true; // P is inside the triangle

	return false;
}

float Triangle::distanceFromPoint(Ray r)
{
	vec3 vector = fragPosition(r) - r.getOrigin();

	if (vector == -r.getOrigin())
		return -1;

	return sqrt(dot(vector, vector));
}

vec3 Triangle::fragPosition(Ray r)
{
	float denom = denominator(vertex1, normal, r);

	if (abs(denom) > 0.00005f) {
	
		float t = numerator(vertex1, normal, r)/denom;

		if (t > 0)
			return r.getDirection()*t + r.getOrigin();
	}

	return vec3(0);
}

vec3 Triangle::getNormal(Ray r)
{
	return normal;
}

vec3 Triangle::getAmbient()
{
	return ambient;
}

vec3 Triangle::getDiffuse()
{
	return diffuse;
}

vec3 Triangle::getSpecular()
{
	return specular;
}

float Triangle::getShinyness()
{
	return shinyness;
}

void Triangle::setNormal(vec3 norm)
{
	normal = norm;
}
