#include "stdafx.h"
#include "Camera.h"


Camera::Camera()
{
}

Camera::Camera(vec3 pos, float feildOv, float focal, float aR)
{
	position = pos;
	fov = feildOv;
	focal_length = focal;
	aspectRatio = aR;
	height = 2*focal_length*tan(fov/720*2*3.1415926);
	width = aspectRatio*height;
}


Camera::~Camera()
{
}

Ray Camera::getCurrentRay()
{
	return current_ray;
}

void Camera::setRay(Ray r)
{
	current_ray = r;
}

vec3 Camera::getPosition()
{
	return position;
}

float Camera::getWidth()
{
	return width;
}

float Camera::getHeight() 
{
	return height;
}

float Camera::getFOV()
{
	return fov;
}

float Camera::getFocalLength()
{
	return focal_length;
}

float Camera::getAspectRatio()
{
	return aspectRatio;
}
