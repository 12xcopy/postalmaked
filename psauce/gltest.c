
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL_video.h>

#include "gltest.h"

//gltest. serves to test opengl while also having the regular software renderer window on the side


static SDL_Window* two;
static void* glx;
void gltest_init()
{
	two = SDL_CreateWindow("GL Test",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,400,300,SDL_WINDOW_OPENGL);
	SDL_ShowWindow(two);
	glx = SDL_GL_CreateContext(two);
	SDL_GL_MakeCurrent(two,glx);
	glClearColor(0.4,0,0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}


void gltest_render(int x, int y,struct gltest_mesh_s* mesh)
{
	int loldebugbreak = 1;
	if (!two)
	{
		gltest_init();
	}

	SDL_GL_MakeCurrent(two,glx);

}