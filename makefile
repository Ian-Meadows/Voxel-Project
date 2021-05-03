# Voxel Project
EXE=voxel_project

# Main target
all: $(EXE)

#  Msys/MinGW
ifeq "$(OS)" "Windows_NT"
CFLG=-O3 -Wall -DUSEGLEW
LIBS=-lglfw3 -lglew32 -lglu32 -lopengl32 -lm
CLEAN=rm -f *.exe *.o *.a
else
#  OSX
ifeq "$(shell uname)" "Darwin"
CFLG=-O3 -Wall -Wno-deprecated-declarations -DAPPLE_GL4 -DUSEGLEW
LIBS=-lglfw3 -lglew -framework Cocoa -framework OpenGL -framework IOKit
#  Linux/Unix/Solaris
else
CFLG=-O3 -Wall
LIBS=-lglfw -lGLU -lGL -lm
endif
#  OSX/Linux/Unix/Solaris
CLEAN=rm -f $(EXE) *.o *.a
endif


# Dependencies
main.o: main.cpp
Print.o: Print.cpp
Debugger.o: Debugger.cpp
Window.o: Window.cpp OpenGL_Includer.h
ErrorHandler.o: ErrorHandler.cpp OpenGL_Includer.h
Shader.o: Shader.cpp OpenGL_Includer.h
Input.o: Input.cpp OpenGL_Includer.h
Scene.o: Scene.cpp OpenGL_Includer.h
Time.o: Time.cpp OpenGL_Includer.h
Camera.o: Camera.cpp OpenGL_Includer.h
TextureAtlas.o: TextureAtlas.cpp OpenGL_Includer.h
World.o: World.cpp OpenGL_Includer.h
Chunk.o: Chunk.cpp OpenGL_Includer.h
Light.o: Light.cpp OpenGL_Includer.h
LightHandler.o: LightHandler.cpp OpenGL_Includer.h
MovingLight.o: MovingLight.cpp OpenGL_Includer.h
BlockLight.o: BlockLight.cpp OpenGL_Includer.h

#blocks
Block.o: 
	g++ -c $(CFLG) Blocks/Block.cpp
Cobblestone.o: 
	g++ -c $(CFLG) Blocks/Cobblestone.cpp
Air.o: 
	g++ -c $(CFLG) Blocks/Air.cpp
Grass.o: 
	g++ -c $(CFLG) Blocks/Grass.cpp
Stone.o: 
	g++ -c $(CFLG) Blocks/Stone.cpp
Diamond.o: 
	g++ -c $(CFLG) Blocks/Diamond.cpp
LightBlock.o: 
	g++ -c $(CFLG) Blocks/LightBlock.cpp


#  Create archive
OpenGL_Includer.a: Print.o Window.o ErrorHandler.o Shader.o Input.o Scene.o Time.o Camera.o TextureAtlas.o Chunk.o World.o Light.o LightHandler.o MovingLight.o BlockLight.o
	ar -rcs $@ $^


# Compile rules
.c.o:
	gcc -c $(CFLG)  $<

#
.cpp.o:
	g++ -c $(CFLG)  $<



#  Link
voxel_project:main.o Debugger.o Block.o Cobblestone.o Air.o Grass.o Stone.o Diamond.o LightBlock.o OpenGL_Includer.a
	g++ -O3 -o $@ $^  $(LIBS)


#  Clean
clean:
	$(CLEAN)