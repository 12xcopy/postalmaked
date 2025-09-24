
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>
#include <SDL_video.h>

#include "gltest.h"
#include "postalrenwrap.h"
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
// copy of internal palette
uint8_t PAL_r[256];
uint8_t PAL_g[256];
uint8_t PAL_b[256];

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

	psaucGetPaletteEntries(0,256,PAL_r,PAL_g,PAL_b,1);
}

void gltest_postrender()
{
	SDL_GL_SwapWindow(two);
	int w,h;
	SDL_GetWindowSize(two,&w,&h);
	//actually the viewport might want to be moved since postal doesnt render at 0,0
	glViewport(0,0,w,h);
}

struct renderdata
{
	struct gltest_meshmeta_s* meta;
};
typedef uint32_t ARGB_t;

union ARGB_u
{
	uint8_t v[4];
	struct {
		uint8_t a;
		uint8_t r;
		uint8_t g;
		uint8_t b;
	} col;
};

struct glcolor_s
{
	float r;
	float g;
	float b;
	float a;
};

ARGB_t palindex_to_argb(int index)
{
	union ARGB_u un;
	un.col.a = 0xff;
	un.col.r = PAL_r[index];
	un.col.g = PAL_g[index];
	un.col.b = PAL_b[index];
	return *((ARGB_t*)(&un));
}

struct glcolor_s argb_to_glcolor(ARGB_t c)
{
	struct glcolor_s color;
	union ARGB_u un = *(union ARGB_u*)&c;

	uint8_t red = un.col.r;
	uint8_t grn = un.col.g;
	uint8_t blu = un.col.b;
	uint8_t alp = un.col.a;

	color.r = (float)red / 255.0f;
	color.g = (float)grn / 255.0f;
	color.b = (float)blu / 255.0f;
	color.a = (float)alp / 255.0f;
	return color;
}


//note: points are already in screen space

// This is to be converted to modern gl later
void gltest_render_internal(int x, int y,struct gltest_mesh_s* mesh,struct renderdata rd)
{
	const int sw = 600;
	const int sh = 480;

	int trico = mesh->m_sNum;
	uint16_t* indecies = mesh->m_pArray;
	struct glcolor_s dcolor = {0.3,0.8,0.6,1.0};

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

		if (rd.meta)
		{
			int entry = rd.meta->colors_elements[i];
			ARGB_t pcolor = palindex_to_argb(entry);
			dcolor = argb_to_glcolor(pcolor);
		}

		glBegin(GL_TRIANGLES);
		glColor3f(dcolor.r,dcolor.g,dcolor.b);
		glVertex2f(pt1.v[0],-pt1.v[1]);
		glVertex2f(pt2.v[0],-pt2.v[1]);
		glVertex2f(pt3.v[0],-pt3.v[1]);
		glEnd();
	}

}


void gltest_renderwm(int x, int y,struct gltest_mesh_s* mesh,struct gltest_meshmeta_s* meta)
{
	struct renderdata rd;
	rd.meta=meta;
	gltest_render_internal(x,y,mesh,rd);
}

void gltest_render(int x, int y,struct gltest_mesh_s* mesh)
{
	struct renderdata rd;
	rd.meta=0;
	gltest_render_internal(x,y,mesh,rd);
}