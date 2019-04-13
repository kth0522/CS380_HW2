#include <Snowman.hpp>
Snowman::Snowman()
{

}

Snowman::~Snowman()
{

}


void Snowman::rotate_body_left() //rotate total body to left
{
	body->SetOrientation(glm::rotate(body->GetOrientation(), glm::radians(-0.5f), glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Snowman::rotate_body_right() { //rotate total body to right
	body->SetOrientation(glm::rotate(body->GetOrientation(), glm::radians(0.5f), glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Snowman::go_left() { //go left
	body->SetPosition(body->GetPosition()+glm::vec3(-0.1f, 0.0f, 0.0f));
}

void Snowman::go_right() {//go right
	body->SetPosition(body->GetPosition() + glm::vec3(0.1f, 0.0f, 0.0f));

}

void Snowman::go_front() {//go front
	body->SetPosition(body->GetPosition() + glm::vec3(0.0f, 0.0f, 0.1f));

}

void Snowman::go_back() {//go back
	body->SetPosition(body->GetPosition() + glm::vec3(0.0f, 0.0f, -0.1f));

}

void Snowman::rotate_head()
{
	head->SetOrientation(glm::rotate(head->GetOrientation(), glm::radians(1.0f), glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Snowman::make_angry() {//tilt the snowman's eyebrow to make him angry
	glm::vec3 left_brow_origin = left_brow->GetPosition();
	glm::vec3 right_brow_origin = right_brow->GetPosition();
	left_brow->SetPosition(-left_brow_origin);
	right_brow->SetPosition(-right_brow_origin);

	left_brow->SetOrientation(glm::rotate(left_brow->GetOrientation(), glm::radians(-1.0f), glm::vec3(1.0f,0.0f, 1.0f)));
	right_brow->SetOrientation(glm::rotate(right_brow->GetOrientation(), glm::radians(1.0f), glm::vec3(-1.0f, 0.0f, 1.0f)));
	left_brow->SetPosition(left_brow_origin);
	right_brow->SetPosition(right_brow_origin);

}

void Snowman::make_walk() { //swing the snowman's legs just like he his walking
	glm::vec3 left_leg_origin = left_leg->GetPosition();
	glm::vec3 right_leg_origin = right_leg->GetPosition();
	
	if(direction){
		left_leg->SetPosition(-left_leg_origin);
		left_leg->SetOrientation(glm::rotate(left_leg->GetOrientation(), glm::radians(0.5f), glm::vec3(1.0f, 0.0f, 0.0f)));
		left_leg->SetPosition(left_leg_origin);

		right_leg->SetPosition(-right_leg_origin);
		right_leg->SetOrientation(glm::rotate(right_leg->GetOrientation(), glm::radians(-0.5f), glm::vec3(1.0f, 0.0f, 0.0f)));
		right_leg->SetPosition(right_leg_origin);
		if (walk_process != 100) {
			walk_process += 1;
		}
		else {
			walk_process = 0;
			direction = !direction;
		}
		
	}else{
		left_leg->SetPosition(-left_leg_origin);
		left_leg->SetOrientation(glm::rotate(left_leg->GetOrientation(), glm::radians(-0.5f), glm::vec3(1.0f, 0.0f, 0.0f)));
		left_leg->SetPosition(left_leg_origin);

		right_leg->SetPosition(-right_leg_origin);
		right_leg->SetOrientation(glm::rotate(right_leg->GetOrientation(), glm::radians(0.5f), glm::vec3(1.0f, 0.0f, 0.0f)));
		right_leg->SetPosition(right_leg_origin);
		if (walk_process != 100) {
			walk_process += 1;
		}
		else {
			walk_process = 0;
			direction = !direction;
		}
	
	}
	
	
}