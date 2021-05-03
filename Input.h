#ifndef INPUT_H
#define INPUT_H

#include "OpenGL_Includer.h"
#include "glm/glm.hpp"
#include <iostream>
#include <vector>

enum KeyCode{
	A = GLFW_KEY_A,
	B = GLFW_KEY_B,
	C = GLFW_KEY_C,
	D = GLFW_KEY_D,
	E = GLFW_KEY_E,
	F = GLFW_KEY_F,
	G = GLFW_KEY_G,
	H = GLFW_KEY_H,
	I = GLFW_KEY_I,
	J = GLFW_KEY_J,
	K = GLFW_KEY_K,
	L = GLFW_KEY_L,
	M = GLFW_KEY_M,
	N = GLFW_KEY_N,
	O = GLFW_KEY_O,
	P = GLFW_KEY_P,
	Q = GLFW_KEY_Q,
	R = GLFW_KEY_R,
	S = GLFW_KEY_S,
	T = GLFW_KEY_T,
	U = GLFW_KEY_U,
	V = GLFW_KEY_V,
	W = GLFW_KEY_W,
	X = GLFW_KEY_X,
	Y = GLFW_KEY_Y,
	Z = GLFW_KEY_Z,
	ALPHA_1 = GLFW_KEY_1,
	ALPHA_2 = GLFW_KEY_2,
	ALPHA_3 = GLFW_KEY_3,
	ALPHA_4 = GLFW_KEY_4,
	ALPHA_5 = GLFW_KEY_5,
	ALPHA_6 = GLFW_KEY_6,
	ALPHA_7 = GLFW_KEY_7,
	ALPHA_8 = GLFW_KEY_8,
	ALPHA_9 = GLFW_KEY_9,
	ALPHA_0 = GLFW_KEY_0,
	UP_ARROW = GLFW_KEY_UP,
	DOWN_ARROW = GLFW_KEY_DOWN,
	LEFT_ARROW = GLFW_KEY_LEFT,
	RIGHT_ARROW = GLFW_KEY_RIGHT,
	SPACE = GLFW_KEY_SPACE,
	LEFT_SHIFT = GLFW_KEY_LEFT_SHIFT,
	ESCAPE = GLFW_KEY_ESCAPE
};

namespace Input {
	void InitInput(GLFWwindow*);
	void ProcessInput();
	void ClearOldInputs();

	bool GetKeyPressed(int key);
	bool GetKeyReleased(int key);
	bool GetKeyHeld(int key);

	bool GetMouseButtonPressed(int button);
	bool GetMouseButtonReleased(int button);
	bool GetMouseButtonHeld(int button);

	glm::vec2 GetScrollDelta();
	glm::vec2 GetMousePosition();

	void MouseIsOverUI();
	void MouseNotOverUI();
	bool GetMouseOverUI();
}


#endif