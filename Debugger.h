#ifndef DEBUGGER_H
#define DEBUGGER_H
#include "glm/glm.hpp"


namespace Debugger {
	void PrintVector(glm::vec1 vector);
	void PrintVector(glm::vec2 vector);
	void PrintVector(glm::vec3 vector);
	void PrintVector(glm::vec4 vector);

	void PrintVector(glm::vec1 vector, const char* message);
	void PrintVector(glm::vec2 vector, const char* message);
	void PrintVector(glm::vec3 vector, const char* message);
	void PrintVector(glm::vec4 vector, const char* message);

	void PrintVector(glm::ivec1 vector);
	void PrintVector(glm::ivec2 vector);
	void PrintVector(glm::ivec3 vector);
	void PrintVector(glm::ivec4 vector);

	void PrintVector(glm::ivec1 vector, const char* message);
	void PrintVector(glm::ivec2 vector, const char* message);
	void PrintVector(glm::ivec3 vector, const char* message);
	void PrintVector(glm::ivec4 vector, const char* message);


	void PrintNumber(short num);
	void PrintNumber(int num);
	void PrintNumber(long num);
	void PrintNumber(float num);
	void PrintNumber(double num);

	void PrintNumber(short num, const char* message);
	void PrintNumber(int num, const char* message);
	void PrintNumber(long num, const char* message);
	void PrintNumber(float num, const char* message);
	void PrintNumber(double num, const char* message);

}

#endif