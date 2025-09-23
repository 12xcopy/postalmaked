
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>
#include <SDL_video.h>

#include "gltest.h"
//note: animations have a GetAtTime 

extern struct gltest_point_s*  ms_pPts2;

typedef struct gltest_point_s pt_t;
//gltest. serves to test opengl while also having the regular software renderer window on the side


static SDL_Window* two;
static void* glx;
void gltest_init()
{
	two = SDL_CreateWindow("GL Test",8,8,400,300,SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_ShowWindow(two);
	glx = SDL_GL_CreateContext(two);
	SDL_GL_MakeCurrent(two,glx);
	glClearColor(0.4,0,0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}

void gltest_preparerender()
{
	if (!two)
	{
		gltest_init();
	}
	SDL_GL_MakeCurrent(two,glx);
	glClearColor(0.4,0,0,1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	// disable backface culling
	glDisable(GL_CULL_FACE);
}

void gltest_postrender()
{
	SDL_GL_SwapWindow(two);
}

//note: points are already in screen space

// This is to be converted to modern gl later
void gltest_render(int x, int y,struct gltest_mesh_s* mesh)
{
	int loldebugbreak = 1;
	const int sw = 600;
	const int sh = 480;

	int trico = mesh->m_sNum;
	uint16_t* indecies = mesh->m_pArray;


	int rawset_len = trico;

	for (int i=0;i<rawset_len;i++)
	{

		int seeker = i*3;

		//note: this promotes a uint16 to int32
		int p1 = indecies[seeker];
		int p2 = indecies[seeker+1];
		int p3 = indecies[seeker+2];

		pt_t pt1 = ms_pPts2[p1];
		pt_t pt2 = ms_pPts2[p2];
		pt_t pt3 = ms_pPts2[p3];

		pt1.v[0] += x - (sw / 2.0f);
		pt2.v[0] += x - (sw / 2.0f);
		pt3.v[0] += x - (sw / 2.0f);
		pt1.v[1] += y - (sh / 2.0f);
		pt2.v[1] += y - (sh / 2.0f);
		pt3.v[1] += y - (sh / 2.0f);

		pt1.v[0] /= (sw / 2.0f);
		pt1.v[1] /= (sh / 2.0f);
		pt2.v[0] /= (sw / 2.0f);
		pt2.v[1] /= (sh / 2.0f);
		pt3.v[0] /= (sw / 2.0f);
		pt3.v[1] /= (sh / 2.0f);

		glBegin(GL_TRIANGLES);
		glColor3f(0.3,0.8,0.6);
		glVertex2f(pt1.v[0],-pt1.v[1]);
		glVertex2f(pt2.v[0],-pt2.v[1]);
		glVertex2f(pt3.v[0],-pt3.v[1]);
		glEnd();
		loldebugbreak++;
	}

}