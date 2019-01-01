#include "pch.h"
#include <iostream>
#include <GL/glut.h>
#include <string>
#include <sstream>
#include <fstream>
#include <glm/glm.hpp>
#include <stdlib.h>
#include <math.h>
#include <vector>
#include <glm/gtc/type_ptr.hpp>
#ifdef _unix
#include <unistd.h>
#endif
#include <GLFW/glfw3.h>
#ifdef _WIN32
#include <windows.h>
#endif
#include "Border.h"
#include "Block.h"
#include "Pad.h"
#include "Ball.h"

GLuint window;
GLuint width = 800, height = 600;
GLuint object;

std::vector<Block*> blocks;
Border *border;
Pad *pad;
Ball *ball;

int pad_x;
float start_time;
bool game_over = false;
bool victory = false;

void sleep(int millis) {
#ifdef _unix
	usleep(millis * 1000);
#endif
#ifdef _WIN32
	Sleep(millis);
#endif
}

void display_f() {

	glClearColor(0, 0, 0, 1);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glTranslatef(width / 2.0f, height / 2.0f, 0);

	if (game_over) {
		glRasterPos2f(0, 0);
		std::string string_ = "GAME OVER!";
		int len = (int)string_.length();
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string_[i]);
		}
		glFlush();
		sleep(2000);
		exit(0);
	}
	else if (victory) {
		sleep(100);
		glRasterPos2f(0, 0);
		std::string string_ = "VICTORY!";
		int len = (int)string_.length();
		for (int i = 0; i < len; i++) {
			glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, string_[i]);
		}
		glFlush();
		sleep(2000);
		exit(0);
	}
	else {
		game_over = ball->check_game_over();
		border->draw_border();
		pad->draw_pad();
		if (!pad->get_has_ball()) {
			int n = 0;
			float n2 = -2.0;
			if ((n = ball->check_collision_border(border)) > 0) {
			}
			else if ((n2 = ball->check_collision_pad(pad)) != -2.0) {
			}
			else {
				for (int i = 0; i < blocks.size(); i++) {
					if ((n = ball->check_collision_block(blocks[i])) > 0) {
						blocks.erase(blocks.begin() + i);
						if (blocks.size() <= 0) {
							victory = true;
						}
						break;
					}
				}
			}
			if (n > 0) {
				ball->change_trajectory(n);
				ball->set_last_bounce_position(ball->get_position());
				start_time = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
			}
			else if (n2 != -2.0) {
				ball->change_trajectory_pad(n2);
				ball->set_last_bounce_position(ball->get_position());
				start_time = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
			}
			ball->calculate_position(((GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0f) - start_time);
		}
		else {
			ball->set_position(glm::vec2(pad->get_position().x, ball->get_position().y));
		}
		ball->draw_ball();
		for (int i = 0; i < blocks.size(); i++) {
			blocks[i]->draw_block();
		}

		glFlush();
	}
}

void reshape_f(int w, int h) {

	width = w;
	height = h;

	//glDisable(GL_DEPTH_TEST);
	glViewport(0, 0, width, height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	//glOrtho(0, width, 0, height, -1000, 1024);
	//gluPerspective(45.0f, ((double)width/height), 0.1, 500.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(1.0f);
	glColor3f(0.0f, 0.0f, 0.0f);

}

void mouse_f(int button, int state, int x, int y) {

	if ((button == GLUT_LEFT_BUTTON) && (state == GLUT_DOWN)) {

	}
	else if ((button == GLUT_RIGHT_BUTTON) && (state == GLUT_DOWN)) {
		//reshape_f(width, height);
		//glFlush();
	}
	/*else {
		if (x > border->get_position().x + border->get_dimensions().x/2.0) {
			pad->set_position(border->get_position().x + border->get_dimensions().x/2.0);
		}
		else if (x < border->get_position().x - border->get_dimensions().x/2.0) {
			pad->set_position(border->get_position().x - border->get_dimensions().x/2.0);
		}
		else {
			pad->set_position(x);
		}
	}*/
}

void keyboard_f(unsigned char theKey, int mouseX, int mouseY) {
	switch (theKey) {
	case 'a':
		pad_x -= 10;
		if (pad_x - pad->get_dimensions().x / 2.0f < border->get_position().x - border->get_dimensions().x / 2.0f) {
			pad_x = border->get_position().x - border->get_dimensions().x / 2.0f + pad->get_dimensions().x / 2.0f;
			pad->set_position(border->get_position().x - border->get_dimensions().x / 2.0f + pad->get_dimensions().x / 2.0f);
		}
		else {
			pad->set_position(pad_x);
		}
		break;
	case 'd':
		pad_x += 10;
		if (pad_x + pad->get_dimensions().x / 2.0f > border->get_position().x + border->get_dimensions().x / 2.0f) {
			pad_x = border->get_position().x + border->get_dimensions().x / 2.0f - pad->get_dimensions().x / 2.0f;
			pad->set_position(border->get_position().x + border->get_dimensions().x / 2.0 - pad->get_dimensions().x / 2.0f);
		}
		else {
			pad->set_position(pad_x);
		}
		break;
	case 'e':
		if (pad->get_has_ball()) {
			pad->launch_ball();
			start_time = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0f;
			ball->set_last_bounce_position(glm::vec2(pad->get_position().x, ball->get_position().y));
		}
		break;
	}
}

void load_objects() {

	border = new Border();
	pad_x = border->get_position().x;
	pad = new Pad(glm::vec2(border->get_position().x, border->get_position().y - border->get_dimensions().y / 2.0f + 15), glm::vec2(70, 10));
	ball = new Ball(pad);
	for (int i = 0; i < 10; i++) {
		blocks.push_back(new Block(glm::vec2(-90 + i * 20, 100)));
	}
	for (int i = 0; i < 10; i++) {
		blocks.push_back(new Block(glm::vec2(-90 + i * 20, 200)));
	}
}

int main(int argc, char *argv[]) {

	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(width, height);
	glutInitWindowPosition(10, 10);
	glutInit(&argc, argv);

	load_objects();

	window = glutCreateWindow("Block Destroyer");
	//glutFullScreen();
	glutReshapeFunc(reshape_f);
	start_time = (GLfloat)glutGet(GLUT_ELAPSED_TIME) / 1000.0;
	glutDisplayFunc(display_f);
	glutIdleFunc(display_f);
	glutMouseFunc(mouse_f);
	glutKeyboardFunc(keyboard_f);
	glutMainLoop();

	return 0;
}
