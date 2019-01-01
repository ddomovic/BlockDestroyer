#include "pch.h"
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "Pad.h"

Pad::Pad() {
	this->color = glm::vec3(0.0, 1.0, 0.0);
	this->position = glm::vec2(0.0, -100.0);
	this->starting_position = this->position;
	this->dimensions = glm::vec2(50, 20);
	this->has_ball = true;
	this->radius = ((this->dimensions.x / 2.0f) * 180) / (60 * PI);
}

Pad::Pad(glm::vec2 position, glm::vec2 dimensions) {
	this->color = glm::vec3(0.0, 1.0, 0.0);
	this->position = position;
	this->starting_position = this->position;
	this->dimensions = dimensions;
	this->has_ball = true;
	this->radius = ((this->dimensions.x / 2.0f) * 180) / (60 * PI);
}

Pad::Pad(glm::vec3 color, glm::vec2 position, glm::vec2 dimensions) {
	this->color = color;
	this->position = position;
	this->starting_position = this->position;
	this->dimensions = dimensions;
	this->has_ball = true;
	this->radius = ((this->dimensions.x / 2.0f) * 180) / (60 * PI);
}

void Pad::set_color(glm::vec3 color) {
	this->color = color;
}

void Pad::set_position(glm::vec2 position) {
	this->position = position;
}

void Pad::set_position(float x) {
	this->position.x = x;
}

void Pad::set_dimensions(glm::vec2 dimensions) {
	this->dimensions = dimensions;
}

void Pad::set_starting_position(glm::vec2 position) {
	this->starting_position = position;
}

void Pad::set_has_ball(bool has_ball) {
	this->has_ball = has_ball;
}

glm::vec3 Pad::get_color() {
	return this->color;
}

glm::vec2 Pad::get_position() {
	return this->position;
}

glm::vec2 Pad::get_dimensions() {
	return this->dimensions;
}

glm::vec2 Pad::get_starting_position() {
	return this->starting_position;
}

float Pad::get_radius() {
	return this->radius;
}

bool Pad::get_has_ball() {
	return this->has_ball;
}

void Pad::draw_pad() {
	glColor3f(this->color.x, this->color.y, this->color.z);
	glBegin(GL_QUADS);
	glVertex2f(this->position.x - this->dimensions.x / 2.0f, this->position.y - this->dimensions.y / 2.0f);
	glVertex2f(this->position.x - this->dimensions.x / 2.0f, this->position.y + this->dimensions.y / 2.0f);
	glVertex2f(this->position.x + this->dimensions.x / 2.0f, this->position.y + this->dimensions.y / 2.0f);
	glVertex2f(this->position.x + this->dimensions.x / 2.0f, this->position.y - this->dimensions.y / 2.0f);
	glEnd();
}

void Pad::reset_position() {
	this->position = this->starting_position;
}

void Pad::launch_ball() {
	this->has_ball = false;
}
