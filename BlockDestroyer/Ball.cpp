#include "pch.h"
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include <vector>
#include "Pad.h"
#include "Block.h"
#include "Border.h"
#include "Ball.h"

Ball::Ball(Pad *owner_pad) {
	this->color = glm::vec3(1.0, 1.0, 1.0);
	this->radius = 4.0;
	this->position = glm::vec2(owner_pad->get_position().x, 1 + owner_pad->get_position().y + this->radius + owner_pad->get_dimensions().y / 2.0);
	this->last_bounce_position = this->position;
	this->direction_vector = glm::vec2(10, 60);
	this->speed = 400.0;
	this->on_pad = true;
	this->owner_pad = owner_pad;
	this->can_hit_pad = false;
}

Ball::Ball(Pad *owner_pad, float radius) {
	this->color = glm::vec3(1.0, 1.0, 1.0);
	this->radius = radius;
	this->position = glm::vec2(owner_pad->get_position().x, 1 + owner_pad->get_position().y + this->radius + owner_pad->get_dimensions().y / 2.0);
	this->last_bounce_position = this->position;
	this->direction_vector = glm::vec2(1.5, 3.0);
	this->speed = 400.0;
	this->on_pad = true;
	this->owner_pad = owner_pad;
	this->can_hit_pad = false;
}

Ball::Ball(Pad *owner_pad, glm::vec3 color, float radius) {
	this->color = color;
	this->radius = radius;
	this->position = glm::vec2(owner_pad->get_position().x, 1 + owner_pad->get_position().y + this->radius + owner_pad->get_dimensions().y / 2.0);
	this->last_bounce_position = this->position;
	this->direction_vector = glm::vec2(1.5, 3.0);
	this->speed = 400.0;
	this->on_pad = true;
	this->owner_pad = owner_pad;
	this->can_hit_pad = false;
}

void Ball::set_color(glm::vec3 color) {
	this->color = color;
}

void Ball::set_position(glm::vec2 position) {
	this->position = position;
}

void Ball::set_radius(float radius) {
	this->radius = radius;
}

void Ball::set_direction_vector(glm::vec2 direction_vector) {
	this->direction_vector = direction_vector;
}

void Ball::set_speed(float speed) {
	this->speed = speed;
}

void Ball::set_last_bounce_position(glm::vec2 last_bounce_position) {
	this->last_bounce_position = last_bounce_position;
}

glm::vec3 Ball::get_color() {
	return this->color;
}

glm::vec2 Ball::get_position() {
	return this->position;
}

float Ball::get_radius() {
	return this->radius;
}

glm::vec2 Ball::get_direction_vector() {
	return this->direction_vector;
}

float Ball::get_speed() {
	return this->speed;
}

glm::vec2 Ball::get_last_bounce_position() {
	return this->last_bounce_position;
}

void Ball::reset_position() {
	this->position = glm::vec2(owner_pad->get_position().x, owner_pad->get_position().y + owner_pad->get_dimensions().y / 2.0);
}

void Ball::draw_ball() {
	glColor3f(this->color.x, this->color.y, this->color.z);
	glBegin(GL_TRIANGLE_FAN);
	for (int i = 0; i < 360; i += 20) {
		GLfloat radians = i * PI / 180.0f;
		glVertex2f(cos(radians) * this->radius + this->position.x, sin(radians) * this->radius + this->position.y);
	}
	glEnd();
}

void Ball::change_trajectory(int mode) {
	if (mode == 0) {
		return;
	}
	else if (mode == 1) {
		this->direction_vector.x = this->direction_vector.x * (-1);
		this->can_hit_pad = true;
	}
	else if (mode == 2) {
		this->direction_vector.y = this->direction_vector.y * (-1);
		this->can_hit_pad = true;
	}
}

void Ball::change_trajectory_pad(float bounce_spot) {

	if (this->can_hit_pad) {

		float bounce_spot_x = bounce_spot;

		if (bounce_spot < -0.8f) {
			bounce_spot_x = -0.8f;
		}
		else if (bounce_spot > 0.8f) {
			bounce_spot_x = 0.8f;
		}

		float arc_len = bounce_spot_x * this->owner_pad->get_dimensions().x / 2.0f;
		float ang = arc_len / this->owner_pad->get_radius();

		this->direction_vector.x = cos(PI / 2.0f - ang);
		this->direction_vector.y = sin(PI / 2.0f - ang);

		if (this->direction_vector.y < 0) {
			this->direction_vector.y *= -1;
		}
		this->can_hit_pad = false;
	}
}

int Ball::check_collision_border(Border *border) {

	float ball_x = this->position.x;
	float ball_y = this->position.y;
	float border_x_left = border->get_position().x - border->get_dimensions().x / 2.0f;
	float border_x_right = border->get_position().x + border->get_dimensions().x / 2.0f;
	float border_y_up = border->get_position().y + border->get_dimensions().y / 2.0f;
	float border_y_down = border->get_position().y - border->get_dimensions().y / 2.0f;

	if ((this->direction_vector.x > 0.0f) && (this->direction_vector.y > 0.0f)) {
		if (ball_x + this->radius >= border_x_right) {
			return 1;
		}
		if (ball_y + this->radius >= border_y_up) {
			return 2;
		}
	}
	else if ((this->direction_vector.x < 0.0f) && (this->direction_vector.y > 0.0f)) {
		if (ball_x - this->radius <= border_x_left) {
			return 1;
		}
		if (ball_y + this->radius >= border_y_up) {
			return 2;
		}
	}
	else if ((this->direction_vector.x > 0.0f) && (this->direction_vector.y < 0.0f)) {
		if (ball_x + this->radius >= border_x_right) {
			return 1;
		}
		if (ball_y - this->radius <= border_y_down) {
			return 2;
		}
	}
	else if ((this->direction_vector.x < 0.0f) && (this->direction_vector.y < 0.0f)) {
		if (ball_x - this->radius <= border_x_left) {
			return 1;
		}
		if (ball_y - this->radius <= border_y_down) {
			return 2;
		}
	}
	return 0;
}

float Ball::check_collision_pad(Pad *pad) {

	float ball_x = this->position.x;
	float ball_y = this->position.y;
	float pad_x_left = pad->get_position().x - pad->get_dimensions().x / 2.0f;
	float pad_x_right = pad->get_position().x + pad->get_dimensions().x / 2.0f;
	float pad_y_up = pad->get_position().y + pad->get_dimensions().y / 2.0f;
	float pad_y_down = pad->get_position().y - pad->get_dimensions().y / 2.0f;

	if (this->direction_vector.y < 0) {
		if ((ball_x + this->radius >= pad_x_left) && (ball_x - this->radius <= pad_x_right)
			&& (ball_y - this->radius <= pad_y_up) && (ball_y + this->radius >= pad_y_down)) {
			return (this->get_position().x - pad->get_position().x) / (pad->get_dimensions().x / 2.0f);
		}
	}
	return -2.0f;
}

int Ball::check_collision_block(Block *block) {

	float ball_x = this->position.x;
	float ball_y = this->position.y;
	float block_x_left = block->get_position().x - block->get_dimensions().x / 2.0f;
	float block_x_right = block->get_position().x + block->get_dimensions().x / 2.0f;
	float block_y_up = block->get_position().y + block->get_dimensions().y / 2.0f;
	float block_y_down = block->get_position().y - block->get_dimensions().y / 2.0f;

	if ((ball_x + this->radius >= block_x_left) && (ball_x - this->radius <= block_x_right)
		&& (ball_y - this->radius <= block_y_up) && (ball_y + this->radius >= block_y_down)) {
		if ((ball_y - this->radius <= block_y_up) && (ball_x >= block_x_left) && (ball_x <= block_x_right)) {
			return 2;
		}
		if ((ball_y + this->radius >= block_y_down) && (ball_x >= block_x_left) && (ball_x <= block_x_right)) {
			return 2;
		}
		if ((ball_x - this->radius <= block_x_right) && (ball_y <= block_y_up) && (ball_y >= block_y_down)) {
			return 1;
		}
		if ((ball_x + this->radius >= block_x_left) && (ball_y <= block_y_up) && (ball_y >= block_y_down)) {
			return 1;
		}
	}
	return 0;
}

bool Ball::check_game_over() {

	if (this->position.y < owner_pad->get_position().y - owner_pad->get_dimensions().y / 2.0f) {
		return true;
	}
	return false;
}

void Ball::calculate_position(float current_time) {
	this->position.x = this->last_bounce_position.x +
		((this->direction_vector.x * speed * current_time) / (fabs(this->direction_vector.x) + fabs(this->direction_vector.y)));
	this->position.y = this->last_bounce_position.y +
		((this->direction_vector.y * speed * current_time) / (fabs(this->direction_vector.x) + fabs(this->direction_vector.y)));
}
