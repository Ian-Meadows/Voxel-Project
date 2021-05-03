#include "Debugger.h"
#include <iostream>

namespace Debugger {
	namespace {

	}

	//vecs
	void PrintVector(glm::vec1 vector) {
		std::cout << "X: " << vector.x << std::endl;
	}
	void PrintVector(glm::vec2 vector) {
		std::cout << "X: " << vector.x << " Y: " << vector.y << std::endl;
	}
	void PrintVector(glm::vec3 vector) {
		std::cout << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << std::endl;
	}
	void PrintVector(glm::vec4 vector) {
		std::cout << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << " W: " << vector.w << std::endl;
	}


	void PrintVector(glm::vec1 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << std::endl;
	}
	void PrintVector(glm::vec2 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << " Y: " << vector.y << std::endl;
	}
	void PrintVector(glm::vec3 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << std::endl;
	}
	void PrintVector(glm::vec4 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << " W: " << vector.w << std::endl;
	}



	//ivecs
	void PrintVector(glm::ivec1 vector) {
		std::cout << "X: " << vector.x << std::endl;
	}
	void PrintVector(glm::ivec2 vector) {
		std::cout << "X: " << vector.x << " Y: " << vector.y << std::endl;
	}
	void PrintVector(glm::ivec3 vector) {
		std::cout << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << std::endl;
	}
	void PrintVector(glm::ivec4 vector) {
		std::cout << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << " W: " << vector.w << std::endl;
	}


	void PrintVector(glm::ivec1 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << std::endl;
	}
	void PrintVector(glm::ivec2 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << " Y: " << vector.y << std::endl;
	}
	void PrintVector(glm::ivec3 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << std::endl;
	}
	void PrintVector(glm::ivec4 vector, const char* message) {
		std::cout << message << ": " << "X: " << vector.x << " Y: " << vector.y << " Z: " << vector.z << " W: " << vector.w << std::endl;
	}


	void PrintNumber(short num) {
		std::cout << num << std::endl;
	}
	void PrintNumber(int num) {
		std::cout << num << std::endl;
	}
	void PrintNumber(long num) {
		std::cout << num << std::endl;
	}
	void PrintNumber(float num) {
		std::cout << num << std::endl;
	}
	void PrintNumber(double num) {
		std::cout << num << std::endl;
	}


	void PrintNumber(short num, const char* message) {
		std::cout << message << ": " << num << std::endl;
	}
	void PrintNumber(int num, const char* message) {
		std::cout << message << ": " << num << std::endl;
	}
	void PrintNumber(long num, const char* message) {
		std::cout << message << ": " << num << std::endl;
	}
	void PrintNumber(float num, const char* message) {
		std::cout << message << ": " << num << std::endl;
	}
	void PrintNumber(double num, const char* message) {
		std::cout << message << ": " << num << std::endl;
	}
}