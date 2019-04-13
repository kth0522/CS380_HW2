#pragma once

#include <vector>
#define GLM_FORCE_SWIZZLE
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <Mesh.hpp>

class Triangle {
private:
public:
	//Three points of the triangle
	glm::vec3 a;
	glm::vec3 b;
	glm::vec3 c;
	Triangle(glm::vec3 _a, glm::vec3 _b, glm::vec3 _c);
};

class Triangle_List {
private:
public:
	Triangle_List();
	int len = 0; //size of the Triangle_List
	std::vector<Triangle> list; //list of triangle


	void append(Triangle triangle); //append one triangle into list
	int size();
};

class Geometry
{
private:

protected:
	Geometry *parent;
	std::vector<Geometry *> children;
public:
	Geometry();
	~Geometry();
	void GenerateCube(Engine::Mesh* mesh);
	void Quad(Engine::Mesh* mesh, int a_a, int a_b, int a_c, int a_d);
	void Triple(Engine::Mesh * mesh, glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c);
	glm::vec3 ComputeNormal(glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c);
	void Quad(Engine::Mesh * mesh, glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c, glm::vec4 a_d);
	void GenerateTriangleMesh(Engine::Mesh* mesh);
	void GenerateLine(Engine::Mesh* mesh);
	void GenerateStar(Engine::Mesh* mesh);

	void GenerateCone(Engine::Mesh * mesh, float radius, float height);

	void GenerateCylinder(Engine::Mesh * mesh, float radius, float height);

	void GenerateBackgroundMeshType1(Engine::Mesh * mesh);

	void GenerateBackgroundMeshType2(Engine::Mesh * mesh);

	void GenerateSphere(Engine::Mesh * mesh, float radius);

	std::vector<glm::vec3> g_vertex_buffer_data; //buffer of vertices.
	Triangle_List triangle_list = Triangle_List(); //list of the triangles that includes all part of snowflake

	void koch_line(glm::vec3 a, glm::vec3 b, int iter);

	void GenerateSnowflake(Engine::Mesh * mesh);
		
	void AddChild(Geometry *geometry);
};

class VertexList {
private:

protected:

public:
	VertexList();
	~VertexList();
};



/*
 * Implement Fractal class to generate Koch snowflakes mesh (generate snowflake mesh using triangle list).
 * Koch snowflake: https://en.wikipedia.org/wiki/Koch_snowflake
 */
class Fractal
{
private:
public:
	Fractal();
	~Fractal();
	std::vector<glm::vec3> g_vertex_buffer_data; //buffer of vertices.
	Triangle_List triangle_list = Triangle_List(); //list of the triangles that includes all part of snowflake
	glm::vec4 color = glm::vec4((rand() % 100) / 100.0f, (rand() % 100) / 100.0f, (rand() % 100) / 100.0f, 1.0f); //randomize the snowflake's color
	void koch_line(glm::vec3 a, glm::vec3 b, int iter); //make one side of koch snowflake
	void GenerateSnowflake(Engine::Mesh* mesh);
};

