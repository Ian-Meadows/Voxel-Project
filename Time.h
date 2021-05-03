#ifndef TIME_H
#define TIME_H
#include "OpenGL_Includer.h"
#include <iostream>

namespace Time {
	double GetFPS();
	double GetDeltaTime();
	double GetTime();

	//bool is for debug purposes. if true fps will print every second
	void Init(bool);

	void Update();
}

#endif