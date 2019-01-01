#pragma once
#ifndef BLOCK_H_
#define BLOCK_H_

#include <glm/glm.hpp>

class Block {
protected:
	static unsigned int ID_counter;
private:
	glm::vec3 color;
	glm::vec2 position;
	glm::vec2 dimensions;
	unsigned int ID;
public:
	Block();
	Block(glm::vec2 position);
	Block(glm::vec2 position, glm::vec2 dimensions);
	Block(glm::vec3 color, glm::vec2 position, glm::vec2 dimensions);
	void set_color(glm::vec3 color);
	void set_position(glm::vec2 position);
	void set_dimensions(glm::vec2 dimensions);
	unsigned int get_ID();
	glm::vec3 get_color();
	glm::vec2 get_position();
	glm::vec2 get_dimensions();
	void draw_block();
};

#endif