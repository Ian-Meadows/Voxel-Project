#ifndef ERROR_HANDLER_H
#define ERROR_HANDLER_H
#include "OpenGL_Includer.h"
#include <iostream>


namespace ErrorHandler
{
    void Fatal(const char* format , ...);
    void Warning(const char* warning);
    void ErrCheck(const char* where);
}


#endif