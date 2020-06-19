#pragma once
#include "EntityList.h"
#include "Light.h"
#include "Camera.h"
#include "../../CImg.h"
#include "../glm/glm.hpp"
#include "Sphere.h"
#include "Plane.h"
#include "Mesh.h"
#include "Triangle.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;
using namespace cimg_library;

class Scene
{
private:
	EntityList object_list;
	vector<Light> light_list;
	Camera cam;
	string scene_name;

	void loadLight(vector<string> lines, int startIndex);
	void loadCamera(vector<string> lines, int startIndex);
	void loadSphere(vector<string> lines, int startIndex);
	void loadPlane(vector<string> lines, int startIndex);
	void loadTriangle(vector<string> lines, int startIndex);
	void loadMesh(vector<string> lines, int startIndex);

public:
	Scene();
	Scene(string filePath);
	~Scene();

	void draw();
};
