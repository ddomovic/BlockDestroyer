#pragma once
#ifndef BALL_H_
#define BALL_H_

#include <glm/glm.hpp>

#define PI 3.14159265358979323846264338327950288f

class Ball {
private:
	glm::vec3 color;
	glm::vec2 position;
	float radius;
	glm::vec2 direction_vector;
	float speed;
	bool on_pad;
	class Pad *owner_pad;
	glm::vec2 last_bounce_position;
	bool can_hit_pad;
public:
	Ball(class Pad *owner_pad);
	Ball(class Pad *owner_pad, float radius);
	Ball(class Pad *owner_pad, glm::vec3 color, float radius);
	void set_color(glm::vec3 color);
	void set_position(glm::vec2 position);
	void set_radius(float radius);
	void set_direction_vector(glm::vec2 direction_vector);
	void set_speed(float speed);
	void set_last_bounce_position(glm::vec2 last_bounce_position);
	glm::vec3 get_color();
	glm::vec2 get_position();
	float get_radius();
	glm::vec2 get_direction_vector();
	float get_speed();
	glm::vec2 get_last_bounce_position();
	void change_trajectory(int mode);
	void change_trajectory_pad(float bounce_spot);
	void calculate_position(float current_time);
	void reset_position();
	int check_collision_border(class Border *border);
	float check_collision_pad(Pad *pad);
	int check_collision_block(class Block *block);
	void draw_ball();
	bool check_game_over();
};

#endif