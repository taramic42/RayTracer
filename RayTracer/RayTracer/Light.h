#pragma once
#include "../glm/glm.hpp"
#include "EntityList.h"
#include <vector>

using namespace glm;
using namespace std;

class Light
{
private:
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
public:
	Light();
	Light(vec3 pos, vec3 amb, vec3 diff, vec3 spec);
	~Light();

	void setPostion(vec3 pos);
	void setAmbient(vec3 amb);
	void setDiffuse(vec3 diff);
	void setSpecular(vec3 spec);

	vec3 getPosition();
	vec3 getAmbient();
	vec3 getDiffuse();
	vec3 getSpecular();

	vec3 getColorContribution(int listIndex, Ray &cameraToFragment, EntityList list);

};

