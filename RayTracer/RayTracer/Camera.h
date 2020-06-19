#pragma once
#include "Ray.h"

class Camera
{
public:
	Camera();
	Camera(vec3 pos, float feildOv, float focal, float aR);
	~Camera();

	Ray getCurrentRay();
	void setRay(Ray r);
	vec3 getPosition();
	float getWidth();
	float getHeight();
	float getFOV();
	float getFocalLength();
	float getAspectRatio();

private:
	Ray current_ray;
	vec3 position;
	float width;
	float height;
	float fov;
	float focal_length;
	float aspectRatio;

};

