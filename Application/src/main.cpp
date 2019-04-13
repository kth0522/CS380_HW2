// STL
#include <iostream>
#include <math.h>
#include <stdlib.h>

// include opengl extension and application library
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>

// include Engine
#include <Camera.hpp>
#include <Mesh.hpp>
#include <Material.hpp>
#include <RenderObject.hpp>

// include application headers
#include <DefaultMaterial.hpp>
#include <PickingMaterial.hpp>
#include <LineMaterial.hpp>
#include <Geometry.hpp>
#include <Animation.hpp>
#include <picking.hpp>
#include <PickableObject.hpp>
#include <Snowman.hpp>

#define _USE_MATH_DEFINES

GLFWwindow* g_window;
float g_window_width = 1024.f;
float g_window_height = 768.f;
int g_framebuffer_width = 1024;
int g_framebuffer_height = 768;

//booleans for check state of the snowman
bool head_spin = false; 
bool right_spin = false;
bool left_spin = false;
bool go_left = false;
bool go_right = false;
bool go_front = false;
bool go_back = false;
bool is_angry = false;

// TODO: Fill up GLFW mouse button callback function
static void MouseButtonCallback(GLFWwindow* a_window, int a_button, int a_action, int a_mods)
{
    //example code for get x position and y position of mouse click
    if (a_button == GLFW_MOUSE_BUTTON_LEFT && a_action == GLFW_PRESS)
    {
        double xpos, ypos;
        glfwGetCursorPos(a_window, &xpos, &ypos);
        xpos = xpos / ((double)g_window_width) * ((double)g_framebuffer_width);
        ypos = ypos / ((double)g_window_height) * ((double)g_framebuffer_height);
        int target = pick((int)xpos, (int)ypos, g_framebuffer_width, g_framebuffer_height);
        std::cout << "Picked object index: " << target << std::endl;

		if (target == 1)
		{
			is_angry = !is_angry;\
			
		}
		if (target == 2)
		{
			is_angry = !is_angry;
		}
    }
	if (a_button == GLFW_MOUSE_BUTTON_LEFT && a_action == GLFW_RELEASE)
	{
		//if release the button reset the is_angry
		double xpos, ypos;
		glfwGetCursorPos(a_window, &xpos, &ypos);
		xpos = xpos / ((double)g_window_width) * ((double)g_framebuffer_width);
		ypos = ypos / ((double)g_window_height) * ((double)g_framebuffer_height);
		int target = pick((int)xpos, (int)ypos, g_framebuffer_width, g_framebuffer_height);
		std::cout << "Picked object index: " << target << std::endl;

		if (target == 1)
		{
			is_angry = !is_angry;
		}
		if (target == 2)
		{
			is_angry = !is_angry;
		}
	}
}





// TODO: Fill up GLFW cursor position callback function
static void CursorPosCallback(GLFWwindow* a_window, double a_xpos, double a_ypos)
{

}

static void KeyboardCallback(GLFWwindow* a_window, int a_key, int a_scancode, int a_action, int a_mods)
{
    if (a_action == GLFW_PRESS)
    {
        switch (a_key)
        {
        case GLFW_KEY_H:
            std::cout << "CS380 Homework 2" << std::endl;
            std::cout << "keymaps:" << std::endl;
            std::cout << "h\t\t Help command" << std::endl;
			std::cout << "Q : rotate left" << std::endl;
			std::cout << "E : rotate right" << std::endl;
            break;
		case GLFW_KEY_Q:
			std::cout << "Q pressed" << std::endl;
			left_spin = !left_spin;
			break;
		case GLFW_KEY_E:
			std::cout << "E pressed" << std::endl;
			right_spin = !right_spin;
			break;
		case GLFW_KEY_W:
			std::cout << "W pressed" << std::endl;
			go_front = !go_front;
			break;
		case GLFW_KEY_S:
			std::cout << "S pressed" << std::endl;
			go_back = !go_back;
			break;			
		case GLFW_KEY_A:
			std::cout << "A pressed" << std::endl;
			go_left = !go_left;
			break;
		case GLFW_KEY_D:
			std::cout << "D pressed" << std::endl;
			go_right = !go_right;
			break;
        default:
            break;
        }
	}
	else if (a_action == GLFW_RELEASE) {
		//if release the button, reset the state
		switch (a_key) {
		case GLFW_KEY_Q:
			std::cout << "Q relaesed" << std::endl;
			left_spin = !left_spin;
			break;
		case GLFW_KEY_E:
			std::cout << "E relaesed" << std::endl;
			right_spin = !right_spin;
			break;
		case GLFW_KEY_W:
			std::cout << "W relased" << std::endl;
			go_front = !go_front;
			break;
		case GLFW_KEY_S:
			std::cout << "S released" << std::endl;
			go_back = !go_back;
			break;
		case GLFW_KEY_A:
			std::cout << "A released" << std::endl;
			go_left = !go_left;
			break;
		case GLFW_KEY_D:
			std::cout << "D released" << std::endl;
			go_right = !go_right;
			break;
		default:
			break;

		}
	}
}


int main(int argc, char** argv)
{
    // Initialize GLFW library
    if (!glfwInit())
    {
        return -1;
    }

    // Create window and OpenGL context
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    /* Create a windowed mode window and its OpenGL context */
    g_window = glfwCreateWindow(g_window_width, g_window_height, "HW2 - Do you want to build a snowman?", NULL, NULL);
    if (!g_window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(g_window);

    // Initialize GLEW library
    GLenum glew_error = glewInit();
    if (glew_error != GLEW_OK)
    {
        std::cout << "GLEW Error: " << glewGetErrorString(glew_error) << std::endl;
        exit(1);
    }


    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Accept fragment if it closer to the camera than the former one
    glDepthFunc(GL_LESS);

    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK); // Cull back-facing triangles -> draw only front-facing triangles

    glfwSetInputMode(g_window, GLFW_STICKY_KEYS, GL_TRUE);
    glfwSetMouseButtonCallback(g_window, MouseButtonCallback);
    glfwSetCursorPosCallback(g_window, CursorPosCallback);
    glfwSetKeyCallback(g_window, KeyboardCallback);

    // Initialize framebuffer object and picking textures
    pickingInitialize(g_framebuffer_width, g_framebuffer_width);

    Engine::Camera* main_camera = new Engine::Camera();
    main_camera->SetPosition(glm::vec3(0.0f, 0.0f, 7.5f));

    // TODO: Create mesh and material (in main.cpp) Slide No. 10 (Define cube mesh, material), No. 18 (Define pickable object)
	Geometry geometry = Geometry();

	//create meshes
	Engine::Mesh* background_mesh = new Engine::Mesh();
	geometry.GenerateCube(background_mesh);

	Engine::Mesh* back_object1_mesh = new Engine::Mesh();
	geometry.GenerateBackgroundMeshType2(back_object1_mesh);

	Engine::Mesh* back_object2_mesh = new Engine::Mesh();
	geometry.GenerateBackgroundMeshType1(back_object2_mesh);

	

	Engine::Mesh* snowflake_mesh = new Engine::Mesh();
	geometry.GenerateSnowflake(snowflake_mesh);
	//geometry.Quad(background_mesh, glm::vec4(-5.0f, 5.0f, -2.0f, 1.0f), glm::vec4(-5.0f, -5.0f, -2.0f, 1.0f), glm::vec4(5.0f, -5.0f, -2.0f, 1.0f), glm::vec4(5.0f, 5.0f, -2.0f, 1.0f));

	Engine::Mesh* nose_mesh = new Engine::Mesh();
	geometry.GenerateCone(nose_mesh, 0.2f, 1.0f);

	Engine::Mesh* cylinder_mesh = new Engine::Mesh();
	geometry.GenerateCylinder(cylinder_mesh, 0.2f, 0.1f);

	Engine::Mesh* brow_mesh = new Engine::Mesh();
	geometry.GenerateCylinder(brow_mesh, 0.05f, 0.5f);

	Engine::Mesh* arm_mesh = new Engine::Mesh();
	geometry.GenerateCylinder(arm_mesh, 0.1f, 1.5f);

	Engine::Mesh* arm_mesh_2 = new Engine::Mesh();
	geometry.GenerateCylinder(arm_mesh_2, 0.1f, 1.5f);

	Engine::Mesh* leg_mesh = new Engine::Mesh();
	geometry.GenerateCylinder(leg_mesh, 0.1f, 1.5f);

	Engine::Mesh* leg_mesh_2 = new Engine::Mesh();
	geometry.GenerateCylinder(leg_mesh_2, 0.1f, 1.5f);
	
    Engine::Mesh* sphere_mesh = new Engine::Mesh();
    geometry.GenerateSphere(sphere_mesh, 2.0f);

	Animation* animation = new Animation();

	Engine::Mesh* star_mesh = new Engine::Mesh();
	geometry.GenerateStar(star_mesh);
		
    DefaultMaterial* material = new DefaultMaterial();
    material->CreateMaterial();

	DefaultMaterial* material_2 = new DefaultMaterial();
	material_2->CreateMaterial();

    PickingMaterial* picking_material = new PickingMaterial();
    picking_material->CreateMaterial();

    PickableObject sphere1 = PickableObject(sphere_mesh, material);
    sphere1.SetPickingMat(picking_material);
    sphere1.SetPosition(glm::vec3(0.0f, 2.0f, 0.0f));
	sphere1.SetScale(glm::vec3(0.8f, 0.8f, 0.8f));
	//sphere1.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    sphere1.SetIndex(1);

    PickableObject sphere2 = PickableObject(sphere_mesh, material);
    sphere2.SetPickingMat(picking_material);
	//sphere2.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
    sphere2.SetPosition(glm::vec3(0.0f, -2.0f, 0.0f));
	
    sphere2.SetIndex(2);

	PickableObject nose = PickableObject(nose_mesh, material);
	nose.SetPickingMat(picking_material);
	nose.SetPosition(glm::vec3(0.0f, 0.45f, 1.5f));
	nose.SetIndex(3);

	PickableObject eye_1 = PickableObject(cylinder_mesh, material);
	eye_1.SetPickingMat(picking_material);
	eye_1.SetPosition(glm::vec3(0.50f, 0.45f, 1.5f));
	eye_1.SetIndex(4);

	PickableObject eye_2 = PickableObject(cylinder_mesh, material);
	eye_2.SetPickingMat(picking_material);
	eye_2.SetPosition(glm::vec3(-0.50f, 0.45f, 1.5f));
	eye_2.SetIndex(5);

	
	PickableObject left_arm = PickableObject(arm_mesh, material);
	left_arm.SetPickingMat(picking_material);
	left_arm.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(-1.0f, 1.0f, 0.0f)));
	left_arm.SetPosition(glm::vec3(2.0f, 0.0f, 0.0f));
	left_arm.SetIndex(6);
	

	PickableObject right_arm = PickableObject(arm_mesh_2, material);
	right_arm.SetPickingMat(picking_material);
	right_arm.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(1.0f, 1.0f, 0.0f)));
	right_arm.SetPosition(glm::vec3(-2.0f, 0.0f, 0.0f));
	right_arm.SetIndex(7);

	PickableObject left_leg = PickableObject(leg_mesh, material);
	left_leg.SetPickingMat(picking_material);
	left_leg.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	left_leg.SetPosition(glm::vec3(0.8f, -1.5f, 0.0f));
	left_leg.SetIndex(8);


	PickableObject right_leg = PickableObject(leg_mesh_2, material);
	right_leg.SetPickingMat(picking_material);
	right_leg.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(1.0f, 0.0f, 0.0f)));
	right_leg.SetPosition(glm::vec3(-0.8f, -1.5f, 0.0f));
	right_leg.SetIndex(9);

	PickableObject background = PickableObject(background_mesh, material_2);
	background.SetPickingMat(picking_material);
	background.SetIndex(10);

	PickableObject left_brow = PickableObject(brow_mesh, material);
	left_brow.SetPickingMat(picking_material);
	left_brow.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	
	left_brow.SetPosition(glm::vec3(0.3f, 0.75f, 1.5f));
	left_brow.SetIndex(11);

	PickableObject right_brow = PickableObject(brow_mesh, material);
	right_brow.SetPickingMat(picking_material);
	right_brow.SetOrientation(glm::rotate(glm::mat4(1.0f), glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
	
	right_brow.SetPosition(glm::vec3(-0.3f, 0.75f, 1.5f));
	right_brow.SetIndex(12);

	Engine::RenderObject custom2Render = Engine::RenderObject(back_object1_mesh, material);

	custom2Render.SetPosition(glm::vec3(3.0f, 2.0f, 0.0f));
	

	Engine::RenderObject custom1Render = Engine::RenderObject(back_object2_mesh, material);

	custom1Render.SetPosition(glm::vec3(-3.0f, 2.0f, 0.0f));
	




    // make hierachical snowman
	eye_1.AddParent(&sphere1);
	eye_2.AddParent(&sphere1);
	left_brow.AddParent(&sphere1);
	right_brow.AddParent(&sphere1);
	nose.AddParent(&sphere1);
	sphere1.AddParent(&sphere2);
	left_arm.AddParent(&sphere2);
	right_arm.AddParent(&sphere2);
	left_leg.AddParent(&sphere2);
	right_leg.AddParent(&sphere2);


	Snowman snowman = Snowman();
	//add each parts to snowman 
	snowman.eye_1 = &eye_1;
	snowman.left_brow = &left_brow;
	snowman.eye_2 = &eye_2;
	snowman.right_brow = &right_brow;
	snowman.nose = &nose;
	snowman.head = &sphere1;
	snowman.body = &sphere2;
	snowman.left_arm = &left_arm;
	snowman.right_arm = &right_arm;
	snowman.left_leg = &left_leg;
	snowman.right_leg = &right_leg;


	// Create snowflake objects
	for (int i = 0; i < 20; i++)
	{
		Engine::RenderObject* snowflake = new Engine::RenderObject(snowflake_mesh, material);
		snowflake->SetPosition(glm::vec3(-5.0f + 10.0f * ((rand() % 255) / 255.0f), 5.0f * ((rand() % 255) / 255.0f), 0.0f));
		snowflake->SetScale(glm::vec3(0.7f,0.7f, 0.7f));
		animation->AddObject(snowflake);
	}

    float prev_time = 0;

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(g_window) && glfwGetKey(g_window, GLFW_KEY_ESCAPE) != GLFW_PRESS)
    {
        float total_time = (float)glfwGetTime();
        float elapsed_time = total_time - prev_time;
        prev_time = total_time;

		//check the current state of the snowman and do proper action
		if (left_spin)
		{
			snowman.rotate_body_left();
			snowman.make_walk();
		}
		if (right_spin)
		{
			snowman.rotate_body_right();
			snowman.make_walk();
		}
		if (go_left) {
			snowman.go_left();
			snowman.make_walk();
		}
		if (go_right) {
			snowman.go_right();
			snowman.make_walk();
		}
		if (go_front) {
			snowman.go_front();
			snowman.make_walk();
		}
		if (go_back) {
			snowman.go_back();
			snowman.make_walk();
		}
		if (is_angry) {
			snowman.make_angry();
		}

        // First Pass: Object Selection (Slide No. 20)
        // this is for picking the object using mouse interaction
        // binding framebuffer
        glBindFramebuffer(GL_FRAMEBUFFER, picking_fbo);
        // Background: RGB = 0x000000 => objectID: 0
        glClearColor((GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render your objects that you want to select using mouse interaction here
		
        sphere1.RenderPicking(main_camera);
        sphere2.RenderPicking(main_camera);
		
		
        // Second Pass: Object Rendering (Slide No. 11)
        // Drawing object again
        glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glClearColor((GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f, (GLclampf) 0.0f);

        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // Todo: Render object with main camera in the loop
		
		material_2->UpdateColor(glm::vec4(0.3f, 0.0f, 0.8f, 1.0f));
		background.Render(main_camera);

        material->UpdateColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        sphere1.Render(main_camera);
        material->UpdateColor(glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
        sphere2.Render(main_camera);
		material->UpdateColor(glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));;
		nose.Render(main_camera);

		material->UpdateColor(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f));
		eye_1.Render(main_camera);
		eye_2.Render(main_camera);
		left_brow.Render(main_camera);
		right_brow.Render(main_camera);
		
		
		material->UpdateColor(glm::vec4(0.5f, 0.25f, 0.0f, 1.0f));
		left_arm.Render(main_camera);
		
		right_arm.Render(main_camera);
		
		left_leg.Render(main_camera);
		
		right_leg.Render(main_camera);


		material->UpdateColor(glm::vec4(0.95f, 1.0f, 0.0f, 1.0f));
		custom1Render.Render(main_camera);

		material->UpdateColor(glm::vec4(0.9776f, 0.2274f, 0.0823f, 1.0f));
		custom2Render.Render(main_camera);



		material->UpdateColor(glm::vec4(1.0f, 1.0f, 1.0f,1.0f));
		animation->Animate(main_camera, elapsed_time);
        /* Swap front and back buffers */
        glfwSwapBuffers(g_window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    // Delete resources
    delete main_camera;

    glfwTerminate();
    return 0;

}