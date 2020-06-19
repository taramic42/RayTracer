#include "stdafx.h"
#include "Light.h"
#include "Ray.h"

Light::Light()
{
	position = vec3(0,0,0);
	ambient = vec3(0, 0, 0);
	diffuse = vec3(0, 0, 0);
	specular = vec3(0, 0, 0);
}

Light::Light(vec3 pos, vec3 amb, vec3 diff, vec3 spec)
{
	position = pos;
	ambient = amb;
	diffuse = diff;
	specular = spec;
}


Light::~Light()
{
}

void Light::setPostion(vec3 pos)
{
	position = pos;
}

void Light::setAmbient(vec3 amb)
{
	ambient = amb;
}

void Light::setDiffuse(vec3 diff)
{
	diffuse = diff;
}

void Light::setSpecular(vec3 spec)
{
	specular = spec;
}

vec3 Light::getPosition()
{
	return position;
}

vec3 Light::getAmbient()
{
	return ambient;
}

vec3 Light::getDiffuse()
{
	return diffuse;
}

vec3 Light::getSpecular()
{
	return specular;
}

vec3 Light::getColorContribution(int listIndex, Ray &cameraToFragment, EntityList list)
{
	//Light claculation utilizes the Phong illumination model
	Entity* object = list.getItem(listIndex);

	//Find fragment position to shoot a shadow ray
	vec3 fragPosition = object->fragPosition(cameraToFragment);

	//Make ray
	Ray shadowRay = Ray(fragPosition, position-fragPosition);
	float shadow_percent = 0.0f;

	//Get shadow index
	for (int jitter = 0; jitter < 20; jitter++) {
		int index = list.getIndexOfClosest(shadowRay.getRandomCloseCopy(jitter), listIndex);
		if (index < 0)
			shadow_percent += 0.05f;
	}

	vec3 sum = vec3(0, 0, 0);

	if (shadow_percent > 0) {
		//Phong calculation
		vec3 normal = normalize(object->getNormal(cameraToFragment));

		vec3 light_direction = normalize(fragPosition - position);

		vec3 reflectedLight = normalize(reflect(-light_direction, normal));

		float specularity = pow(max(dot(normalize(cameraToFragment.getDirection()), reflectedLight), 0.0f), object->getShinyness());

		vec3 specular_result = specularity * specular*object->getSpecular();

		float incident_degree = max(dot(normal, -light_direction), 0.0f);

		vec3 diffuse_result = diffuse * incident_degree*object->getDiffuse();

		sum = diffuse_result + specular_result;
	}

	vec3 ambient_result = ambient*object->getAmbient();

	return ambient_result + shadow_percent*sum;
}
