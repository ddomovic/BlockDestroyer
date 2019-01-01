#include "pch.h"
#include <iostream>
#include <GL/glut.h>
#include <cmath>
#include "Border.h"

Border::Border() {
	this->color = glm::vec3(1.0, 0.0, 0.0);
	this->position = glm::vec2(0.0, 0.0);
	this->dimensions = glm::vec2(500.0, 500.0);
}

Border::Border(glm::vec2 position, glm::vec2 dimensions) {
	this->color = glm::vec3(1.0, 0.0, 0.0);
	this->position = position;
	this->dimensions = dimensions;
}

Border::Border(glm::vec3 color, glm::vec2 position, glm::vec2 dimensions) {
	this->color = color;
	this->position = position;
	this->dimensions = dimensions;
}

void Border::set_color(glm::vec3 color) {
	this->color = color;
}

void Border::set_position(glm::vec2 position) {
	this->position = position;
}

void Border::set_dimensions(glm::vec2 dimensions) {
	this->dimensions = dimensions;
}

glm::vec3 Border::get_color() {
	return this->color;
}

glm::vec2 Border::get_position() {
	return this->position;
}

glm::vec2 Border::get_dimensions() {
	return this->dimensions;
}

void Border::draw_border() {
	glColor3f(this->color.x, this->color.y, this->color.z);
	glBegin(GL_LINE_LOOP);
	glVertex2f(this->position.x - this->dimensions.x / 2.0, this->position.y - this->dimensions.y / 2.0);
	glVertex2f(this->position.x - this->dimensions.x / 2.0, this->position.y + this->dimensions.y / 2.0);
	glVertex2f(this->position.x + this->dimensions.x / 2.0, this->position.y + this->dimensions.y / 2.0);
	glVertex2f(this->position.x + this->dimensions.x / 2.0, this->position.y - this->dimensions.y / 2.0);
	glEnd();
}
