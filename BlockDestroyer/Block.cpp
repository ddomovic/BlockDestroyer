#include "pch.h"
#include <iostream>
#include <GL/glut.h>
#include "Block.h"

unsigned int Block::ID_counter;

Block::Block() {
	this->ID = ID_counter++;
	this->color = glm::vec3(1.0, 0.0, 0.0);
	this->position = glm::vec2(0.0, 100.0);
	this->dimensions = glm::vec2(20.0, 10.0);
}

Block::Block(glm::vec2 position) {
	this->ID = ID_counter++;
	this->color = glm::vec3(1.0, 0.0, 0.0);
	this->position = position;
	this->dimensions = glm::vec2(20.0, 10.0);
}

Block::Block(glm::vec2 position, glm::vec2 dimensions) {
	this->ID = ID_counter++;
	this->color = glm::vec3(1.0, 0.0, 0.0);
	this->position = position;
	this->dimensions = dimensions;
}

Block::Block(glm::vec3 color, glm::vec2 position, glm::vec2 dimensions) {
	this->ID = ID_counter++;
	this->color = color;
	this->position = position;
	this->dimensions = dimensions;
}

void Block::set_color(glm::vec3 color) {
	this->color = color;
}

void Block::set_position(glm::vec2 position) {
	this->position = position;
}

void Block::set_dimensions(glm::vec2 dimensions) {
	this->dimensions = dimensions;
}

unsigned int Block::get_ID() {
	return this->ID;
}

glm::vec3 Block::get_color() {
	return this->color;
}

glm::vec2 Block::get_position() {
	return this->position;
}

glm::vec2 Block::get_dimensions() {
	return this->dimensions;
}

void Block::draw_block() {
	glColor3f(this->color.x, this->color.y, this->color.z);
	glBegin(GL_QUADS);
	glVertex2f(this->position.x - this->dimensions.x / 2.0f, this->position.y - this->dimensions.y / 2.0f);
	glVertex2f(this->position.x - this->dimensions.x / 2.0f, this->position.y + this->dimensions.y / 2.0f);
	glVertex2f(this->position.x + this->dimensions.x / 2.0f, this->position.y + this->dimensions.y / 2.0f);
	glVertex2f(this->position.x + this->dimensions.x / 2.0f, this->position.y - this->dimensions.y / 2.0f);
	glEnd();
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_LINE_LOOP);
	glVertex2f(this->position.x - this->dimensions.x / 2.0f, this->position.y - this->dimensions.y / 2.0f);
	glVertex2f(this->position.x - this->dimensions.x / 2.0f, this->position.y + this->dimensions.y / 2.0f);
	glVertex2f(this->position.x + this->dimensions.x / 2.0f, this->position.y + this->dimensions.y / 2.0f);
	glVertex2f(this->position.x + this->dimensions.x / 2.0f, this->position.y - this->dimensions.y / 2.0f);
	glEnd();
}