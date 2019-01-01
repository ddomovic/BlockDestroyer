#pragma once
#ifndef PAD_H_
#define PAD_H_

#include <glm/glm.hpp>

#define PI 3.14159265358979323846264338327950288f

class Pad {
private:
	glm::vec3 color;
	glm::vec2 position;
	glm::vec2 starting_position;
	glm::vec2 dimensions;
	bool has_ball;
	float radius;
public:
	Pad();
	Pad(glm::vec2 position, glm::vec2 dimensions);
	Pad(glm::vec3 color, glm::vec2 position, glm::vec2 dimensions);
	void set_color(glm::vec3 color);
	void set_position(float x);
	void set_position(glm::vec2 position);
	void set_dimensions(glm::vec2 dimensions);
	void set_starting_position(glm::vec2 position);
	void set_has_ball(bool has_ball);
	glm::vec3 get_color();
	glm::vec2 get_position();
	glm::vec2 get_dimensions();
	glm::vec2 get_starting_position();
	bool get_has_ball();
	float get_radius();
	void draw_pad();
	void launch_ball();
	void reset_position();
};

#endif
