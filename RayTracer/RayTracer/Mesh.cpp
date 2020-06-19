#include "stdafx.h"
#include "Mesh.h"

Triangle* Mesh::getClosest(Ray r)
{
	vector<Triangle*> hitList;

	for (int i = 0; i < triangle_mesh.size(); i++) {
		if (triangle_mesh[i].collidedWithRay(r))
			hitList.push_back(&triangle_mesh[i]);
	}

	if (hitList.size() == 0)
		return NULL;

	int closest = -1;
	float distance;

	for (int i = 0; i < hitList.size(); i++) {
		float temp = hitList[i]->distanceFromPoint(r);
		if (temp > 0 && (closest==-1||temp < distance)) {
			distance = temp;
			closest = i;
		}
	}
	if (closest == -1)
		return NULL;

	return hitList[closest];
}

Mesh::Mesh():Entity("Mesh")
{
	ambient = vec3(0,0,0);
	diffuse = vec3(0, 0, 0);
	specular = vec3(0, 0, 0);
	shinyness = 0.0f;
}

Mesh::Mesh(const char* filename, vec3 amb, vec3 diff, vec3 spec, float shiny) :Entity("Mesh")
{
	vector<vec3> vertices;
	vector<vec3> dump1;
	vector<vec2> dump2;

	loadOBJ(filename,vertices,dump1,dump2);

	for (int i = 0; i < vertices.size(); i += 3) {
		triangle_mesh.push_back(Triangle(vertices[i], vertices[i + 1], vertices[i + 2], vec3(0), vec3(0), vec3(0), 0.0f));
	}

	ambient = amb;
	diffuse = diff;
	specular = spec;
	shinyness = shiny;
}

Mesh::~Mesh()
{
}

bool Mesh::collidedWithRay(Ray r)
{

	for (int i = 0; i < triangle_mesh.size(); i++) {
		if (triangle_mesh[i].collidedWithRay(r))
			return true;
	}

	return false;
}

float Mesh::distanceFromPoint(Ray r)
{
	return getClosest(r)->distanceFromPoint(r);
}

vec3 Mesh::fragPosition(Ray r)
{
	return getClosest(r)->fragPosition(r);
}

vec3 Mesh::getNormal(Ray r)
{
	return getClosest(r)->getNormal(r);
}

vec3 Mesh::getAmbient()
{
	return ambient;
}

vec3 Mesh::getDiffuse()
{
	return diffuse;
}

vec3 Mesh::getSpecular()
{
	return specular;
}

float Mesh::getShinyness()
{
	return shinyness;
}

//Had to move this here from ogjloader.h due to linking error I couldn't solve
bool Mesh::loadOBJ(const char * path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec3>& out_normals, std::vector<glm::vec2>& out_uvs)
{
	std::vector<int> vertexIndices, uvIndices, normalIndices;
	std::vector<glm::vec3> temp_vertices;
	std::vector<glm::vec2> temp_uvs;
	std::vector<glm::vec3> temp_normals;

	FILE * file;
	int _errno = fopen_s(&file, path, "r");
	if (_errno != 0) {
		printf("Impossible to open the file ! Are you in the right path ?\n");
		getchar();
		return false;
	}

	while (1) {

		char lineHeader[128];
		// read the first word of the line
		int res = fscanf_s(file, "%s", lineHeader, 128);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

				   // else : parse lineHeader

		if (strcmp(lineHeader, "v") == 0) {
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(lineHeader, "vt") == 0) {
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}
		else if (strcmp(lineHeader, "vn") == 0) {
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(lineHeader, "f") == 0) {
			int vertexIndex[3], uvIndex[3], normalIndex[3];
			bool uv, norm = true;
			char line[128];
			fgets(line, 128, file);
			//vertex, uv, norm
			int matches = sscanf_s(line, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9) {
				//vertex, norm
				matches = sscanf_s(line, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
				if (matches != 6) {
					//vertex, uv
					matches = sscanf_s(line, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
					if (matches != 6) {
						//vertex
						matches = sscanf_s(line, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
						if (matches != 6) {
							printf("File can't be read by our simple parser. 'f' format expected: d/d/d d/d/d d/d/d || d/d d/d d/d || d//d d//d d//d\n");
							printf("Character at %d", ftell(file));
							return false;
						}
						uv, norm = false;
					}
					else {
						norm = false;
					}
				}
				else {
					uv = false;
				}
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			if (norm) {
				normalIndices.push_back(normalIndex[0]);
				normalIndices.push_back(normalIndex[1]);
				normalIndices.push_back(normalIndex[2]);
			}
			if (uv) {
				uvIndices.push_back(uvIndex[0]);
				uvIndices.push_back(uvIndex[1]);
				uvIndices.push_back(uvIndex[2]);
			}
		}
		else {
			char clear[1000];
			fgets(clear, 1000, file);
		}

	}
	std::cout << "Vertex indices: " << vertexIndices.size() << std::endl;
	std::cout << "UV indices: " << uvIndices.size() << std::endl;
	std::cout << "Normal indices: " << normalIndices.size() << std::endl;
	// For each vertex of each triangle
	for (unsigned int i = 0; i<vertexIndices.size(); i++) {
		if (uvIndices.size() != 0) {
			if (i < uvIndices.size()) {
				unsigned int uvIndex = abs(uvIndices[i]);
				glm::vec2 uv = temp_uvs[uvIndex - 1];
				out_uvs.push_back(uv);
			}
		}
		if (normalIndices.size() != 0) {
			if (i < normalIndices.size()) {
				unsigned int normalIndex = abs(normalIndices[i]);
				glm::vec3 normal = temp_normals[normalIndex - 1];
				out_normals.push_back(normal);
			}
		}

		unsigned int vertexIndex = abs(vertexIndices[i]);
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		out_vertices.push_back(vertex);
	}

	return true;
}
