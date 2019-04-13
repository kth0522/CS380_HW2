#include <Geometry.hpp>
#include <stdlib.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include <math.h>

Geometry::Geometry()
{
}


Geometry::~Geometry()
{
}

//vertices of background cube
glm::vec4 vertices[8] = {
	/*   5 -- 6
	*  /|   /|
	* 1(4)-2 7
	* |    |/
	* 0 -- 3
	*/
    glm::vec4(-20.0f, -20.0f, -8.0f, 1.0f),
    glm::vec4(-20.0f, 20.0f, -8.0f, 1.0f),
    glm::vec4(20.0f, 20.0f, -8.0f, 1.0f),
    glm::vec4(20.0f, -20.0f, -8.0f, 1.0f),
    glm::vec4(-20.0f, -20.0f, -10.0f, 1.0f),
    glm::vec4(-20.0f, 20.0f, -10.0f, 1.0f),
    glm::vec4(20.0f, 20.0f, -10.0f, 1.0f),
    glm::vec4(20.0f, -20.0f, -10.0f, 1.0f)
};

glm::vec3 Geometry::ComputeNormal(glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c)
{
    glm::vec3 normal = glm::normalize(glm::cross(a_b.xyz() - a_a.xyz(), a_c.xyz() - a_a.xyz()));
    return normal;
}

// TODO: Fill up Geometry::Quad (Slide No. 9)
void Geometry::Quad(Engine::Mesh* mesh, glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c, glm::vec4 a_d)
{//Quad glm::vec4 version
    /* a -- d
     * |    |
     * b -- c
     */
    // Compute normal for quad
    glm::vec4 n = glm::vec4(ComputeNormal(a_a, a_b, a_c), 0.0f);
    // Triangle 1, Vertex a
    mesh->AddVertexData(a_a);
    mesh->AddVertexData(n);
    // Triangle 1, Vertex b
    mesh->AddVertexData(a_b);
    mesh->AddVertexData(n);
    // Triangle 1, Vertex c
    mesh->AddVertexData(a_c);
    mesh->AddVertexData(n);
    // Triangle 2, Vertex a
    mesh->AddVertexData(a_a);
    mesh->AddVertexData(n);
    // Triangle 2, Vertex c
    mesh->AddVertexData(a_c);
    mesh->AddVertexData(n);
    // Triangle 2, Vertex d
    mesh->AddVertexData(a_d);
    mesh->AddVertexData(n);
}

void Geometry::Quad(Engine::Mesh* mesh, int a_a, int a_b, int a_c, int a_d)
{
	/* a -- d
	 * |    |
	 * b -- c
	 */
	 // Compute normal for quad
	glm::vec4 n = glm::vec4(ComputeNormal(vertices[a_a], vertices[a_b], vertices[a_c]), 0.0f);
	// Triangle 1, Vertex a
	mesh->AddVertexData(vertices[a_a]);
	mesh->AddVertexData(n);
	// Triangle 1, Vertex b
	mesh->AddVertexData(vertices[a_b]);
	mesh->AddVertexData(n);
	// Triangle 1, Vertex c
	mesh->AddVertexData(vertices[a_c]);
	mesh->AddVertexData(n);
	// Triangle 2, Vertex a
	mesh->AddVertexData(vertices[a_a]);
	mesh->AddVertexData(n);
	// Triangle 2, Vertex c
	mesh->AddVertexData(vertices[a_c]);
	mesh->AddVertexData(n);
	// Triangle 2, Vertex d
	mesh->AddVertexData(vertices[a_d]);
	mesh->AddVertexData(n);
}

void Geometry::Triple(Engine::Mesh* mesh, glm::vec4 a_a, glm::vec4 a_b, glm::vec4 a_c) {
//modified Quad, triangle version 
/*  a 
 * |  \   
 * b -- c
 */
	glm::vec4 n = glm::vec4(ComputeNormal(a_a, a_b, a_c), 0.0f);
	// Triangle, Vertex a
	mesh->AddVertexData(a_a);
	mesh->AddVertexData(n);
	// Triangle, Vertex b
	mesh->AddVertexData(a_b);
	mesh->AddVertexData(n);
	// Triangle, Vertex c
	mesh->AddVertexData(a_c);
	mesh->AddVertexData(n);

}

// TODO: Fill up Geometry::GenerateCube (Slide No. 8)
void Geometry::GenerateCube(Engine::Mesh* mesh)
{
    /*   5 -- 6
     *  /|   /|
     * 1(4)-2 7
     * |    |/
     * 0 -- 3
     */
    mesh->AddAttribute(4); // for position
    mesh->AddAttribute(4); // for normal

    // Add four quad for generating a cube
    Quad(mesh, 1, 0, 3, 2);
    Quad(mesh, 2, 3, 7, 6);
    Quad(mesh, 3, 0, 4, 7);
    Quad(mesh, 6, 5, 1, 2);
    Quad(mesh, 4, 5, 6, 7);
    Quad(mesh, 5, 4, 0, 1);

    mesh->SetNumElements(36);
    mesh->CreateMesh();
    return;
}

void Geometry::GenerateTriangleMesh(Engine::Mesh* mesh)
{
    mesh->AddAttribute(4);

    glm::vec3 position_data[] = {
        glm::vec3(-1.0f, -1.0f, 0.0f),
        glm::vec3(1.0f, -1.0f, 0.0f),
        glm::vec3(0.0f,1.0f, 0.0f)
    };

    for (int i = 0; i < 3; i++)
    {
        mesh->AddVertexData(position_data[i]);
        mesh->AddVertexData(1.0f);
		
    }
    mesh->SetNumElements(3);
    mesh->CreateMesh();
    return;
}

void Geometry::GenerateLine(Engine::Mesh* mesh)
{
    mesh->SetDrawMode(GL_LINES);
    mesh->AddAttribute(4);
    mesh->AddVertexData(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
    mesh->AddVertexData(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
    mesh->SetNumElements(2);
    mesh->CreateMesh();
    return;
}


void Geometry::GenerateStar(Engine::Mesh* mesh)
{
	mesh->AddAttribute(4);
	mesh->AddAttribute(4);

	glm::vec4 position_data[] = {
		glm::vec4(1.0f * 2.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(-0.5f * 2.0f, sqrt(0.75f) * 2.0f, 0.0f, 1.0f),
		glm::vec4(-0.5f * 2.0f, -sqrt(0.75f) * 2.0f, 0.0f, 1.0f),
		glm::vec4(-1.0f * 2.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.5f * 2.0f, -sqrt(0.75f) * 2.0f, 0.0f, 1.0f),
		glm::vec4(0.5f * 2.0f, sqrt(0.75f) * 2.0f, 0.0f, 1.0f)
	};
	glm::vec4 n = glm::vec4(ComputeNormal(position_data[0], position_data[1], position_data[2]), 0.0f);
	for (int i = 0; i < 6; i++)
	{
		mesh->AddVertexData(position_data[i]);
		mesh->AddVertexData(n);
	}

	mesh->SetNumElements(6);
	mesh->CreateMesh();

	return;
}

void Geometry::GenerateCone(Engine::Mesh* mesh, float radius, float height) {
	//generate Cone mesh
	mesh->AddAttribute(4); // for position
	mesh->AddAttribute(4); // for normal

	float pi = 3.14159265359f;

	std::vector<glm::vec4> verticeList = std::vector<glm::vec4>();
	
	glm::vec4 center = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); //bottom circle's center
	glm::vec4 top = glm::vec4(0.0f, 0.0f, height, 1.0f);  //cone's top tip

	float rotate_unit = (2 * pi) / 40.0f;

	float theta = 0;
	for (int i = 0; i < 40; i++) {
		float x = radius * cos(theta);
		float y = radius * sin(theta);
		verticeList.push_back(glm::vec4(x, y, 0.0f, 1.0f));
		theta += rotate_unit;
	}

	for (int i = 0; i < 39; i++) {
		Triple(mesh, center, verticeList[i + 1], verticeList[i]);
		Triple(mesh, top, verticeList[i], verticeList[i + 1]);
	}
	Triple(mesh, center, verticeList[0], verticeList[38]);
	Triple(mesh, top, verticeList[38], verticeList[0]);

	mesh->SetNumElements(80 * 3);
	mesh->CreateMesh();

	return;
}

void Geometry::GenerateCylinder(Engine::Mesh* mesh, float radius, float height) {
	//create cylinder mesh
	mesh->AddAttribute(4); // for position
	mesh->AddAttribute(4); // for normal

	std::vector<glm::vec4> verticeList_1 = std::vector<glm::vec4>();
	std::vector<glm::vec4> verticeList_2 = std::vector<glm::vec4>();

	float pi = 3.14159265359f;

	glm::vec4 center_1 = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); //bottom circle center
	glm::vec4 center_2 = glm::vec4(0.0f, 0.0f, height, 1.0f); //top circle center

	float rotate_unit = (2 * pi) / 40.0f;

	float theta = 0;
	for (int i = 0; i < 40; i++) {
		float x = radius * cos(theta);
		float y = radius * sin(theta);
		verticeList_1.push_back(glm::vec4(x, y, 0.0f, 1.0f));
		verticeList_2.push_back(glm::vec4(x, y, height, 1.0f));
		theta += rotate_unit;
	}

	for (int i = 0; i < 39; i++) {
		Triple(mesh, center_1, verticeList_1[i+1], verticeList_1[i]);
		Quad(mesh, verticeList_2[i], verticeList_1[i], verticeList_1[i + 1], verticeList_2[i+1]);
		Triple(mesh, center_2, verticeList_2[i], verticeList_2[i+1]);
	}
	Triple(mesh, center_1, verticeList_1[0], verticeList_1[38]);
	Quad(mesh, verticeList_2[38], verticeList_1[38], verticeList_1[0], verticeList_2[0]);
	Triple(mesh, center_2, verticeList_2[38], verticeList_2[0]);

	mesh->SetNumElements(3 * 40 * 2 + 4 * 40*2);
	mesh->CreateMesh();

	return;

}

glm::vec4 vec3_to_vec4(glm::vec3 vector) {
	//convert vec3 to vec4
	float x = vector.x;
	float y = vector.y;
	float z = vector.z;
	return glm::vec4(x, y, z, 1.5f);
}
void Geometry::GenerateBackgroundMeshType1(Engine::Mesh* mesh)
{	//hw1 imported bacground object, slightly modified with Triple function
	//layout 0: vec4 pos := (x,y,z,w)
	mesh->AddAttribute(4);
	//layout 1: vec4 normal 
	mesh->AddAttribute(4);

	glm::vec3 position_data[] = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, sqrt(2)*1.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, sqrt(2)*1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(-sqrt(2)*1.0f, 0.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-sqrt(2)*1.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f,1.0f),
		glm::vec3(0.0f, -sqrt(2)*1.0f, 1.0f),

		
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, -sqrt(2)*1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f)
		
	};

	for (int i = 0; i < 6; i++) {
		Triple(mesh, vec3_to_vec4(position_data[3*i]), vec3_to_vec4(position_data[3*i+1]), vec3_to_vec4(position_data[3*i+2]));
	}
		
	mesh->SetNumElements(18);
	mesh->CreateMesh();

	return;
}

void Geometry::GenerateBackgroundMeshType2(Engine::Mesh* mesh)
{	//hw1 imported bacground object, slightly modified with Triple function
	//layout 0: vec4 pos := (x,y,z,w)
	mesh->AddAttribute(4);
	//layout 1: vec4 normal 
	mesh->AddAttribute(4);

	glm::vec3 position_data[] = {
		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(sqrt(2)*1.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),


		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, 1.0f, 1.0f),
		glm::vec3(0.0f, sqrt(2)*1.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, sqrt(2)*1.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, 1.0f, 1.0f),
		glm::vec3(-sqrt(2)*1.0f, 0.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-sqrt(2)*1.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(-1.0f, -1.0f,1.0f),
		glm::vec3(0.0f, -sqrt(2)*1.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(0.0f, -sqrt(2)*1.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),

		glm::vec3(0.0f, 0.0f, 1.0f),
		glm::vec3(1.0f, -1.0f, 1.0f),
		glm::vec3(sqrt(2)*1.0f, 0.0f, 1.0f)

	};

	for (int i = 0; i < 8; i++) {
		Triple(mesh, vec3_to_vec4(position_data[3 * i]), vec3_to_vec4(position_data[3 * i + 1]), vec3_to_vec4(position_data[3 * i + 2]));
	}

	mesh->SetNumElements(24);
	mesh->CreateMesh();

	return;
}

void Geometry::GenerateSphere(Engine::Mesh* mesh, float radius) {
	//generate sphere
	mesh->AddAttribute(4); // for position
	mesh->AddAttribute(4); // for normal
	
	float pi = 3.14159265359f;

	int numLatitude = 180.0f / 1.0f;
	int numLongitude = 360.0f / 4.0f;

	float latitude_unit = (2*pi)/numLatitude;
	float logitude_unit = (2*pi) / numLongitude;

	int numVertices = numLatitude * (numLongitude + 1) + 2;

	//save the vertice list of the each latitude
	std::vector<std::vector<glm::vec4>> latitude_list = std::vector<std::vector<glm::vec4>>();
	
	std::vector<glm::vec4> north_pole = std::vector<glm::vec4>();
	north_pole.push_back(glm::vec4(0.0f, 0.0f, radius, 1.0f));

	latitude_list.push_back(north_pole);

	
	float phi = (2 * pi) / 4;

	for (int lat = 0; lat < numLatitude; lat++) {
		std::vector<glm::vec4> temp_list = std::vector<glm::vec4>();
		float theta = 0;
		for (int lon = 0; lon < numLongitude; lon++) {
			float z = (radius* cos(phi))*cos(theta);
			float x = (radius* cos(phi))*sin(theta);
			float y = radius * sin(phi);
			temp_list.push_back(glm::vec4(x, y, z, 1.0f));
			theta += logitude_unit;
		}
		latitude_list.push_back(temp_list);
		phi -= latitude_unit;
	}

	std::vector<glm::vec4> south_pole = std::vector<glm::vec4>();
	south_pole.push_back(glm::vec4(0.0f, 0.0f, -radius, 1.0f));

	latitude_list.push_back(south_pole);

	for (int i = 0; i < numLatitude-1; i++) {
		if (i == 0) {//north pole side
			for (int temp = 0; temp < numLongitude-1; temp++) {
				Triple(mesh, latitude_list[i][0], latitude_list[i + 1][temp], latitude_list[i + 1][temp + 1]);
			}
			Triple(mesh, latitude_list[i][0], latitude_list[i + 1][numLongitude-1], latitude_list[i + 1][0]);			
		}
		else if (0 < i && i < numLatitude-2) {//middle side
			for (int temp = 0; temp < numLongitude - 1; temp++) {
				Quad(mesh, latitude_list[i][temp], latitude_list[i + 1][temp], latitude_list[i + 1][temp + 1], latitude_list[i][temp + 1]);
			}
			Quad(mesh, latitude_list[i][numLongitude - 1], latitude_list[i + 1][numLongitude - 1], latitude_list[i + 1][0], latitude_list[i][0]);
		}
		else {//south pole side
			for (int temp = 0; temp < numLongitude - 1; temp++) {
				Triple(mesh, latitude_list[i][temp], latitude_list[i+1][0], latitude_list[i][temp+1]);
			}
			Triple(mesh, latitude_list[i][0], latitude_list[i + 1][0], latitude_list[i][numLongitude - 1]);
		}
	}
	mesh->SetNumElements(numLongitude*2*3+(numLatitude)*numLongitude*6);
	mesh->CreateMesh();

	return;

}

//hw1 imported part
Fractal::Fractal()
{
	//add initial triangle to Fractal's triangle list.
	glm::vec3 a = glm::vec3(-0.5f, 0.0f, 3.0f);
	glm::vec3 c = glm::vec3(0.0f, sqrt(0.75), 3.0f);
	glm::vec3 b = glm::vec3(0.5f, 0.0f, 3.0f);

	Triangle initial_triangle = Triangle(a, b, c);
	triangle_list.append(initial_triangle);
}

Fractal::~Fractal()
{

}

float vector_len(glm::vec3 v) {
	float x = v.x;
	float y = v.y;
	float z = v.z;

	return sqrt(x*x + y * y + z * z);
}

void Geometry::koch_line(glm::vec3 a, glm::vec3 b, int iter)
{
	glm::vec3  b2a = b - a; //vector that points a to b
	glm::vec3 a1 = a + b2a / 3.0f; //first point of fractal's side

	float a1_len = vector_len(a1); //norm of a1
	glm::vec3 rot_axis = glm::vec3(a1.x, a1.y, a1_len * sqrt(3)); //to calculate rotation axis that parallel to z-axis and passing point a1

	glm::vec3 rot = glm::rotate(b2a, glm::radians(30.0f), rot_axis); //rotate the vector b2a to one point of new triangle

	std::vector<glm::vec3> points = std::vector<glm::vec3>(); //create set of points


	glm::vec3 c = a + rot * sqrt(3.0f) / 3.0f; //second point of fractal's side
	glm::vec3 b1 = a + b2a * 2.0f / 3.0f; //third point of fractal's side

	Triangle new_triangle = Triangle(a1, b1, c); //create new triangle and add it into triangle list
	triangle_list.append(new_triangle);

	points.push_back(a1);
	points.push_back(c);
	points.push_back(b1);

	for (size_t i = 0; i < points.size(); i++) {
		g_vertex_buffer_data.push_back(points[i]);
	}

	//do the koch_line recursively in 5 times
	if (iter < 5) {
		koch_line(a, points[0], iter + 1);
		koch_line(points[0], points[1], iter + 1);
		koch_line(points[1], points[2], iter + 1);
		koch_line(points[2], b, iter + 1);
	}
	points.clear();
}


void Geometry::GenerateSnowflake(Engine::Mesh* mesh)
{

	//layout 0: vec4 pos := (x,y,z,w)
	mesh->AddAttribute(4);
	//layout 1: vec4 color := (r,g,b,a)
	mesh->AddAttribute(4);

	std::vector<glm::vec3> initial_triangle = std::vector<glm::vec3>();

	
	initial_triangle.push_back(glm::vec3(-0.5f, 0.0f, 3.0f));
	initial_triangle.push_back(glm::vec3(0.0f, sqrt(0.75), 3.0f));
	initial_triangle.push_back(glm::vec3(0.5f, 0.0f, 3.0f));

	g_vertex_buffer_data = std::vector<glm::vec3>();

	for (size_t i = 0; i < initial_triangle.size(); i++) {
		g_vertex_buffer_data.push_back(initial_triangle[i]);
	}

	//do the koch_line function on the three side of initial trinangle
	koch_line(g_vertex_buffer_data[0], g_vertex_buffer_data[1], 0);
	koch_line(g_vertex_buffer_data[1], g_vertex_buffer_data[2], 0);
	koch_line(g_vertex_buffer_data[2], g_vertex_buffer_data[0], 0);

	int num_vertex = g_vertex_buffer_data.size();
	int num_triangle = triangle_list.size();

	
	
	Geometry::Triple(mesh, glm::vec4(0.0f, sqrt(0.75), 3.0f, 1.5f), glm::vec4(-0.5f, 0.0f, 3.0f, 1.5f), glm::vec4(0.5f, 0.0f, 3.0f, 1.5f));
	for (int i = 0; i < num_triangle; i++) {
		
		glm::vec4 a = vec3_to_vec4(triangle_list.list[i].a);
		glm::vec4 b = vec3_to_vec4(triangle_list.list[i].b);
		glm::vec4 c = vec3_to_vec4(triangle_list.list[i].c);
		Geometry::Triple(mesh, a, b, c);
	}


	mesh->SetNumElements(num_vertex);
	mesh->CreateMesh();

	return;
}

Triangle::Triangle(glm::vec3 _a, glm::vec3 _b, glm::vec3 _c)
{
	a = _a;
	b = _b;
	c = _c;
}

Triangle_List::Triangle_List()
{
}

void Triangle_List::append(Triangle triangle)
{
	list.push_back(triangle); //add new triangle to the list and increase len
	len += 1;
}

int Triangle_List::size()
{
	return len; //just return the len
}