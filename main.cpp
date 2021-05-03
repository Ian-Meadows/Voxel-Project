//This file is just the launcher file for the program. Window handles the rest of the functionality

#include "Window.h"





int main(int argc,char* argv[])
{

   Window::Init("Voxel Project: Ian Meadows", false, 600, 600);


   Window::Start();


   return 0;
}