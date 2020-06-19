#pragma once
#include "Entity.h"
#include "Triangle.h"
#include <vector>

using namespace std;

class Mesh: public Entity
{
private:
	vector<Triangle> triangle_mesh;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shinyness;

	Triangle* getClosest(Ray r);
public:
	Mesh();
	Mesh(const char* filename, vec3 amb, vec3 diff, vec3 spec, float shiny);
	~Mesh();

	bool collidedWithRay(Ray r);
	float distanceFromPoint(Ray r);
	vec3 fragPosition(Ray r);
	vec3 getNormal(Ray r);

	vec3 getAmbient();
	vec3 getDiffuse();
	vec3 getSpecular();
	float getShinyness();

	bool loadOBJ(const char * path, std::vector<glm::vec3> & out_vertices, std::vector<glm::vec3> & out_normals, std::vector<glm::vec2> & out_uvs);
};

