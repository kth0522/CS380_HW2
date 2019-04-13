#pragma once

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <PickableObject.hpp>

class Snowman
{
private:

public:
    Snowman();
    ~Snowman();
	void rotate_body_left();
	void rotate_body_right();
	void go_left();
	void go_right();
	void go_front();
	void go_back();
	int walk_process = 0; //to determine how much snowman swing the legs
	bool direction = false; //to determine which direction to swing the legs
	PickableObject* body;
	PickableObject* head;
	PickableObject* nose;
	PickableObject* eye_1;
	PickableObject* left_brow;
	PickableObject* eye_2;
	PickableObject* right_brow;
	PickableObject* left_arm;
	PickableObject* right_arm;
	PickableObject* left_leg;
	PickableObject* right_leg;
	void rotate_head();
	
	void make_angry();

	void make_walk();
	
};