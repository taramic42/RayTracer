#include "stdafx.h"
#include "Scene.h"

Scene::Scene()
{
}

Scene::Scene(string filePath)
{
	//Open file
	ifstream scenefile;
	
	scenefile.open(filePath);

	//Close if file does not exist
	if (!scenefile) {
		cout << "Could not open file: " << filePath << endl;
		system("pause");
		exit(0);
	}
	
	scene_name = filePath;

	vector<string> lineList;
	string temp;

	while (!scenefile.eof()) {
		getline(scenefile, temp);
		lineList.push_back(temp);
	}

	for (int i = 0; i < lineList.size();i++) {
		if (lineList[i].compare("mesh") == 0) {
			loadMesh(lineList, i);
		}
		else if (lineList[i].compare("light") == 0) {
			loadLight(lineList, i);
		}
		else if (lineList[i].compare("sphere") == 0) {
			loadSphere(lineList, i);;
		}
		else if (lineList[i].compare("plane") == 0) {
			loadPlane(lineList,i);
		}
		else if (lineList[i].compare("camera") == 0) {
			loadCamera(lineList,i);
		}
		else if (lineList[i].compare("triangle") == 0) {
			loadTriangle(lineList, i);
		}
	}

}


Scene::~Scene()
{
	for (int i = 0; i < object_list.size();i++) {
		delete object_list.getItem(i);
	}
}

void Scene::draw()
{
	CImg<float> image(cam.getWidth(), cam.getHeight(), 1, 3, 0);
	
	int width = cam.getWidth();
	int height = cam.getHeight();

	Ray currentRay = Ray(cam.getPosition(), vec3(-((float)width) / 2.0f, ((float)height) / 2.0f, -cam.getFocalLength()));
	Ray offsetRay;
	for (int x = 0; x < width; x++) {
		for (int y = 0; y < height; y++) {

			currentRay = Ray(cam.getPosition(), vec3(-((float)width) / 2.0f + x, ((float)height) / 2.0f - y, -cam.getFocalLength()));
			vec3 color = vec3(0, 0, 0);

			for (int jitter = 0; jitter < 10; jitter++) {

				offsetRay = currentRay.getRandomCloseCopy(jitter);

				int hold = object_list.getIndexOfClosest(offsetRay);

				if (hold >= 0) {

					for (int i = 0; i < light_list.size();i++) {
						color += light_list[i].getColorContribution(hold, offsetRay, object_list);
					}
				}

			}

			if ((x + 1)*(y + 1) == ((width*height) / 2))
				cout << "Half way through" << endl;

			image(x, y, 0) = clamp(color.x / 10.0f, 0.0f, 1.0f) * 255;
			image(x, y, 1) = clamp(color.y / 10.0f, 0.0f, 1.0f) * 255;
			image(x, y, 2) = clamp(color.z / 10.0f, 0.0f, 1.0f) * 255;

		}

	}
	
	CImgDisplay window(image, &scene_name[0]);

	while (!window.is_closed()) {
		window.wait();
	}

	image.save(&(scene_name+".bmp")[0]);
}

void Scene::loadLight(vector<string> lines, int startIndex)
{
	//int size = 4;
	string header;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	//Position
	stringstream ss(lines[startIndex+1]);

	ss >> header;
	ss >> position.x;
	ss >> position.y;
	ss >> position.z;

	//Ambient
	ss.str(lines[startIndex + 2]);
	ss.clear();

	ss >> header;
	ss >> ambient.x;
	ss >> ambient.y;
	ss >> ambient.z;

	//Diffuse
	ss.str(lines[startIndex + 3]);
	ss.clear();

	ss >> header;
	ss >> diffuse.x;
	ss >> diffuse.y;
	ss >> diffuse.z;

	//Specular
	ss.str(lines[startIndex + 4]);
	ss.clear();

	ss >> header;
	ss >> specular.x;
	ss >> specular.y;
	ss >> specular.z;

	//Build light and add to list

	light_list.push_back(Light(position, ambient, diffuse, specular));

}

void Scene::loadCamera(vector<string> lines, int startIndex)
{
	//int size = 4;
	string header;
	vec3 position;
	float fov;
	float f;
	float a;

	//Postion
	header = lines[startIndex + 1].substr(5);
	stringstream ss(header);

	ss >> position.x;
	ss >> position.y;
	ss >> position.z;
	

	//FOV
	header = lines[startIndex + 2].substr(5);
	ss.str(header);
	ss.clear();

	ss >> fov;
	
	//F
	header = lines[startIndex + 3].substr(3);
	ss.str(header);
	ss.clear();

	ss >> f;

	//A
	header = lines[startIndex + 4].substr(3);
	ss.str(header);
	ss.clear();

	ss >> a;

	//Build camera
	
	cam = Camera(position,fov,f,a);
	
}

void Scene::loadSphere(vector<string> lines, int startIndex)
{
	//int size = 6;
	string header;
	vec3 position;
	float radius;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shinyness;

	//Position
	stringstream ss(lines[startIndex + 1]);

	ss >> header;
	ss >> position.x;
	ss >> position.y;
	ss >> position.z;

	//Radius
	ss.str(lines[startIndex+2]);
	ss.clear();

	ss >> header;
	ss >> radius;

	//Ambient
	ss.str(lines[startIndex + 3]);
	ss.clear();

	ss >> header;
	ss >> ambient.x;
	ss >> ambient.y;
	ss >> ambient.z;

	//Diffuse
	ss.str(lines[startIndex + 4]);
	ss.clear();

	ss >> header;
	ss >> diffuse.x;
	ss >> diffuse.y;
	ss >> diffuse.z;

	//Specular
	ss.str(lines[startIndex + 5]);
	ss.clear();

	ss >> header;
	ss >> specular.x;
	ss >> specular.y;
	ss >> specular.z;

	//Shinyness
	ss.str(lines[startIndex + 6]);
	ss.clear();

	ss >> header;
	ss >> shinyness;

	//Build sphere
	object_list.addEntity(new Sphere(position, ambient, diffuse, specular, radius, shinyness));
}

void Scene::loadPlane(vector<string> lines, int startIndex)
{
	//int size = 6;
	string header;
	vec3 normal;
	vec3 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shinyness;

	//Normal
	stringstream ss(lines[startIndex + 1]);

	ss >> header;
	ss >> normal.x;
	ss >> normal.y;
	ss >> normal.z;

	//Position
	ss.str(lines[startIndex + 2]);
	ss.clear();

	ss >> header;
	ss >> position.x;
	ss >> position.y;
	ss >> position.z;

	//Ambient
	ss.str(lines[startIndex + 3]);
	ss.clear();

	ss >> header;
	ss >> ambient.x;
	ss >> ambient.y;
	ss >> ambient.z;

	//Diffuse
	ss.str(lines[startIndex + 4]);
	ss.clear();

	ss >> header;
	ss >> diffuse.x;
	ss >> diffuse.y;
	ss >> diffuse.z;

	//Specular
	ss.str(lines[startIndex + 5]);
	ss.clear();

	ss >> header;
	ss >> specular.x;
	ss >> specular.y;
	ss >> specular.z;

	//Shinyness
	ss.str(lines[startIndex + 6]);
	ss.clear();

	ss >> header;
	ss >> shinyness;

	//Build plane

	object_list.addEntity(new Plane(position, normal, ambient, diffuse, specular, shinyness));
}

void Scene::loadTriangle(vector<string> lines, int startIndex)
{
	//int size = 7;
	string header;
	vec3 vertex1;
	vec3 vertex2;
	vec3 vertex3;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shinyness;

	//Vertex1
	stringstream ss(lines[startIndex + 1]);

	ss >> header;
	ss >> vertex1.x;
	ss >> vertex1.y;
	ss >> vertex1.z;

	//vertex2
	ss.str(lines[startIndex + 2]);
	ss.clear();

	ss >> header;
	ss >> vertex2.x;
	ss >> vertex2.y;
	ss >> vertex2.z;

	//vertex3
	ss.str(lines[startIndex + 3]);
	ss.clear();

	ss >> header;
	ss >> vertex3.x;
	ss >> vertex3.y;
	ss >> vertex3.z;

	//Ambient
	ss.str(lines[startIndex + 4]);
	ss.clear();

	ss >> header;
	ss >> ambient.x;
	ss >> ambient.y;
	ss >> ambient.z;

	//Diffuse
	ss.str(lines[startIndex + 5]);
	ss.clear();

	ss >> header;
	ss >> diffuse.x;
	ss >> diffuse.y;
	ss >> diffuse.z;

	//Specular
	ss.str(lines[startIndex + 6]);
	ss.clear();

	ss >> header;
	ss >> specular.x;
	ss >> specular.y;
	ss >> specular.z;

	//Shinyness
	ss.str(lines[startIndex + 7]);
	ss.clear();

	ss >> header;
	ss >> shinyness;

	//Build Triangle
	object_list.addEntity(new Triangle(vertex1, vertex2, vertex3, ambient, diffuse, specular, shinyness));

}

void Scene::loadMesh(vector<string> lines, int startIndex)
{
	//int size = 5;
	string header;
	string filePath;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shinyness;

	//Filename
	stringstream ss(lines[startIndex+1]);

	ss >> header;

	if (header.find(".") >= 0) {
		filePath = "../" + header;
	}
	else {
		ss >> filePath;
		filePath = "../" + filePath;
	}

	//Ambient
	ss.str(lines[startIndex + 2]);
	ss.clear();

	ss >> header;
	ss >> ambient.x;
	ss >> ambient.y;
	ss >> ambient.z;

	//Diffuse
	ss.str(lines[startIndex + 3]);
	ss.clear();

	ss >> header;
	ss >> diffuse.x;
	ss >> diffuse.y;
	ss >> diffuse.z;

	//Specular
	ss.str(lines[startIndex + 4]);
	ss.clear();

	ss >> header;
	ss >> specular.x;
	ss >> specular.y;
	ss >> specular.z;

	//Shinyness
	ss.str(lines[startIndex + 5]);
	ss.clear();

	ss >> header;
	ss >> shinyness;

	//Build mesh
	object_list.addEntity(new Mesh(&filePath[0],ambient,diffuse,specular,shinyness));

}
