#pragma once
#ifndef BORDER_H_
#define BORDER_H_

#include <glm/glm.hpp>

class Border {
private:
	glm::vec3 color;
	glm::vec2 dimensions;
	glm::vec2 position;
public:
	Border();
	Border(glm::vec2 position, glm::vec2 dimensions);
	Border(glm::vec3 color, glm::vec2 position, glm::vec2 dimensions);
	void set_color(glm::vec3 color);
	void set_dimensions(glm::vec2 dimensions);
	void set_position(glm::vec2 position);
	glm::vec3 get_color();
	glm::vec2 get_dimensions();
	glm::vec2 get_position();
	void draw_border();
};

#endif
