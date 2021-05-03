#include "Input.h"


//only used once
namespace Input {
	//use for private methods and variables
	namespace {
		GLFWwindow* window;
		std::vector<int> keysPressed;
		std::vector<int> keysReleased;
		std::vector<int> keysHeld;

		std::vector<int> mouseButtonPressed;
		std::vector<int> mouseButtonReleased;
		std::vector<int> mouseButtonHeld;

		glm::vec2 scrollDelta;
		glm::vec2 mousePosition;

		bool mouseOverUI = false;

		void MouseCallback(GLFWwindow* window, double xpos, double ypos) {
			mousePosition = glm::vec2(xpos, ypos);
		}

		void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset) {
			scrollDelta = glm::vec2(xOffset, yOffset);
		}

		void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
			if (action == GLFW_PRESS) {
				keysPressed.push_back(key);
				keysHeld.push_back(key);
			}
			else if (action == GLFW_RELEASE) {
				keysReleased.push_back(key);

				//TODO:Make faster
				for (unsigned int i = 0; i < keysHeld.size(); ++i) {
					if (keysHeld[i] == key) {
						keysHeld.erase(keysHeld.begin() + i);
					}
				}
			}
		}

		void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
			if (action == GLFW_PRESS) {
				mouseButtonPressed.push_back(button);
				mouseButtonHeld.push_back(button);
			}
			else if (action == GLFW_RELEASE) {
				mouseButtonReleased.push_back(button);

				//TODO:Make faster
				for (unsigned int i = 0; i < mouseButtonHeld.size(); ++i) {
					if (mouseButtonHeld[i] == button) {
						mouseButtonHeld.erase(mouseButtonHeld.begin() + i);
					}
				}
			}
		}

	}

	//put public methods and variables here

	void InitInput(GLFWwindow* window) {
		Input::window = window;
		scrollDelta = glm::vec2(0.0f, 0.0f);
		//init callbacks
		glfwSetCursorPosCallback(window, MouseCallback);
		glfwSetKeyCallback(window, KeyCallback);
		glfwSetScrollCallback(window, ScrollCallback);
		glfwSetMouseButtonCallback(window, MouseButtonCallback);
	}


	void ProcessInput() {
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
			glfwSetWindowShouldClose(window, true);
		}
	}

	glm::vec2 GetScrollDelta() {
		return scrollDelta;
	}
	glm::vec2 GetMousePosition() {
		return mousePosition;
	}

	void ClearOldInputs() {
		keysPressed.clear();
		keysReleased.clear();
		mouseButtonPressed.clear();
		mouseButtonReleased.clear();
		scrollDelta = glm::vec2(0.0f, 0.0f);
	}

	bool GetKeyPressed(int key) {
		for (unsigned int i = 0; i < keysPressed.size(); ++i) {
			if (key == keysPressed[i]) {
				return true;
			}
		}
		return false;
	}

	bool GetKeyReleased(int key) {
		for (unsigned int i = 0; i < keysReleased.size(); ++i) {
			if (key == keysReleased[i]) {
				return true;
			}
		}
		return false;
	}

	bool GetKeyHeld(int key) {
		for (unsigned int i = 0; i < keysHeld.size(); ++i) {
			if (key == keysHeld[i]) {
				return true;
			}
		}
		return false;
	}


	bool GetMouseButtonPressed(int button) {
		for (unsigned int i = 0; i < mouseButtonPressed.size(); ++i) {
			if (button == mouseButtonPressed[i]) {
				return true;
			}
		}
		return false;
	}

	bool GetMouseButtonReleased(int button) {
		for (unsigned int i = 0; i < mouseButtonReleased.size(); ++i) {
			if (button == mouseButtonReleased[i]) {
				return true;
			}
		}
		return false;
	}

	bool GetMouseButtonHeld(int button) {
		for (unsigned int i = 0; i < mouseButtonHeld.size(); ++i) {
			if (button == mouseButtonHeld[i]) {
				return true;
			}
		}
		return false;
	}

	void MouseIsOverUI() {
		mouseOverUI = true;
	}
	void MouseNotOverUI() {
		mouseOverUI = false;
	}
	bool GetMouseOverUI() {
		return mouseOverUI;
	}
}