// RayTracer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "../../CImg.h"
#include "Sphere.h"
#include "Plane.h"
#include "Camera.h"
#include "Light.h"
#include "Triangle.h"
#include "EntityList.h"
#include "Scene.h"
#include <sstream>

using namespace cimg_library;

int main()
{

	Scene test = Scene("../evaluate_scene6.txt");

	std::cout << "Scene Loaded" << std::endl;

	test.draw();

    return 0;
}

