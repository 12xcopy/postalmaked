
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_video.h>
#include <SDL_video.h>

#include "gltest.h"
#include "postalrenwrap.h"
// note: animations have a GetAtTime

extern struct gltest_point_s *ms_pPts2;

typedef struct gltest_point_s pt_t;
// gltest. serves to test opengl while also having the regular software renderer window on
// the side

static SDL_Window *two;
static void *glx;
void gltest_init()
{
	two = SDL_CreateWindow("GL Test",
	    8,
	    8,
	    400,
	    300,
	    SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
	SDL_ShowWindow(two);
	glx = SDL_GL_CreateContext(two);
	SDL_GL_MakeCurrent(two, glx);
	glClearColor(0.4, 0, 0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);
}
// copy of internal palette
uint8_t PAL_r[256];
uint8_t PAL_g[256];
uint8_t PAL_b[256];

int DEPTH_MODE = GL_GREATER;
int DEPTH_DRAW = 0;

void gltest_preparerender()
{
	if (!two)
	{
		gltest_init();
	}
	SDL_GL_MakeCurrent(two, glx);

	int w, h;
	SDL_GetWindowSize(two, &w, &h);
	// actually the viewport might want to be moved since postal doesnt render at 0,0
	glViewport(0, 0, w, h);
	glClearColor(0.4, 0, 0, 1.0);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClear(GL_COLOR_BUFFER_BIT);

	// disable backface culling
	glDisable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glClearDepth(0.0);

	if (DEPTH_DRAW)
	{
		glDepthFunc(GL_ALWAYS);
	}
	else
	{
		glDepthFunc(DEPTH_MODE);
	}

	psaucGetPaletteEntries(0, 256, PAL_r, PAL_g, PAL_b, 1);

	gltest_render_background();
}

void gltest_postrender()
{
	SDL_GL_SwapWindow(two);
}

struct renderdata
{
	struct gltest_meshmeta_s *meta;
};
typedef uint32_t ARGB_t;

union ARGB_u
{
	uint8_t v[4];
	struct
	{
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
	return *((ARGB_t *)(&un));
}

struct glcolor_s argb_to_glcolor(ARGB_t c)
{
	struct glcolor_s color;
	union ARGB_u un = *(union ARGB_u *)&c;

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

float apply_zbufcap(float input)
{
	// depth buffer usually sits around 0 - 10000, but sometimes goes higher than that
	const float zbuffer_cap = 10000.0f;

	if (input < 0)
	{
		// what??
		return 0.0;
	}

	// input = zbuffer_cap -> i = 0.5
	// input = infinity -> i = 1.0
	float i = input / (zbuffer_cap + input);

	// i = 1.0 - i;

	if (i < 0 || i > 1)
	{
		printf("%.2f out of range (0 .. 1). Input was %.1f\n", i, input);
		return 1.0;
	}

	return i;
}

// note: points are already in screen space

// This is to be converted to modern gl later
void gltest_render_internal(int x, int y, struct gltest_mesh_s *mesh,
    struct renderdata rd)
{
	const int sw = 600;
	const int sh = 480;

	int trico		= mesh->m_sNum;
	uint16_t *indecies	= mesh->m_pArray;
	struct glcolor_s dcolor = {0.3, 0.8, 0.6, 1.0};

	int rawset_len = trico;

	for (int i = 0; i < rawset_len; i++)
	{

		int seeker = i * 3;

		// note: this promotes a uint16 to int32
		int p1 = indecies[seeker];
		int p2 = indecies[seeker + 1];
		int p3 = indecies[seeker + 2];

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

		pt1.v[2] = apply_zbufcap(pt1.v[2]);
		pt2.v[2] = apply_zbufcap(pt2.v[2]);
		pt3.v[2] = apply_zbufcap(pt3.v[2]);

		if (rd.meta)
		{
			int entry     = rd.meta->colors_elements[i];
			ARGB_t pcolor = palindex_to_argb(entry);
			dcolor	      = argb_to_glcolor(pcolor);
		}

		glBegin(GL_TRIANGLES);

		if (!DEPTH_DRAW)
		{
			glColor3f(dcolor.r, dcolor.g, dcolor.b);
			glVertex3f(pt1.v[0], -pt1.v[1], pt1.v[2]);
			glVertex3f(pt2.v[0], -pt2.v[1], pt2.v[2]);
			glVertex3f(pt3.v[0], -pt3.v[1], pt3.v[2]);
		}
		else
		{
			glColor3f(pt1.v[2], pt1.v[2], pt1.v[2]);
			glVertex3f(pt1.v[0], -pt1.v[1], pt1.v[2]);
			glColor3f(pt2.v[2], pt2.v[2], pt2.v[2]);
			glVertex3f(pt2.v[0], -pt2.v[1], pt2.v[2]);
			glColor3f(pt2.v[2], pt2.v[2], pt2.v[2]);
			glVertex3f(pt3.v[0], -pt3.v[1], pt3.v[2]);
			glColor3f(pt2.v[2], pt2.v[2], pt2.v[2]);
		}

		glEnd();
	}
}

void gltest_renderwm(int x, int y, struct gltest_mesh_s *mesh,
    struct gltest_meshmeta_s *meta)
{
	struct renderdata rd;
	rd.meta = meta;
	gltest_render_internal(x, y, mesh, rd);
}

void gltest_render(int x, int y, struct gltest_mesh_s *mesh)
{
	struct renderdata rd;
	rd.meta = 0;
	gltest_render_internal(x, y, mesh, rd);
}

void *current_bg;

typedef struct __attribute__((packed)) /* scary! */
{
	uint8_t r;
	uint8_t g;
	uint8_t b;
} RGB_t;

RGB_t *current_bg_converted;
unsigned bgtex;
void gltest_render_background()
{
	int w, h;
	int pitch;
	uint8_t *img;
	int ret = gltest_getHoodBackground(&w, &h, &img, &pitch);
	if (ret)
		return; // cannot render at this time

	if (current_bg != img)
	{
		current_bg = img;
		if (current_bg_converted)
			free(current_bg_converted);
		current_bg_converted = malloc(w * h * sizeof(RGB_t));
		if (!current_bg_converted)
		{
			//oh well
			fprintf(stderr,"malloc failed!");
			abort();
		}
		memset(current_bg_converted, 0, w * h * sizeof(RGB_t));
		int ccap = w * h;
#if 1
		//BMP8 to RGB888
		for (int r = 0; r < h; r++)
		{
			for (int c = 0; c < w; c++)
			{
				uint8_t index	    = img[r * pitch + c];
				ARGB_t argb	    = palindex_to_argb(index);
				union ARGB_u argb_u = *(union ARGB_u *)&argb;
				current_bg_converted[r * w + c].r = argb_u.col.r;
				current_bg_converted[r * w + c].g = argb_u.col.g;
				current_bg_converted[r * w + c].b = argb_u.col.b;
			}
		}
#else
		for (int i = 0; i < ccap; i++)
		{
			ARGB_t argb		   = 0;
			union ARGB_u argb_u	   = *(union ARGB_u *)&argb;
			argb_u.col.a		   = 255;
			argb_u.col.r		   = i % 4;
			argb_u.col.g		   = i;
			argb_u.col.b		   = (i + 159) * 20;
			int no			   = i;
			current_bg_converted[no].r = argb_u.col.r;
			current_bg_converted[no].g = argb_u.col.g;
			current_bg_converted[no].b = argb_u.col.b;
		}
#endif
		if (bgtex)
			glDeleteTextures(1, &bgtex);
		glGenTextures(1, &bgtex);
		glBindTexture(GL_TEXTURE_2D, bgtex);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
		glTexImage2D(GL_TEXTURE_2D,
		    0,
		    GL_RGB,
		    w,
		    h,
		    0,
		    GL_RGB,
		    GL_UNSIGNED_BYTE,
		    current_bg_converted);
	}
	glEnable(GL_TEXTURE_2D);
	glDepthMask(GL_FALSE);
	glBindTexture(GL_TEXTURE_2D, bgtex);

	glBegin(GL_TRIANGLE_FAN);
	glColor3f(1.0, 1.0, 1.0);

	glTexCoord2f(0, 0);
	glVertex2f(-1, -1);

	glTexCoord2f(1, 0);
	glVertex2f(1, -1);

	glTexCoord2f(1, -1);
	glVertex2f(1, 1);

	glTexCoord2f(0, -1);
	glVertex2f(-1, 1);

	glEnd();

	glDepthMask(GL_TRUE);
	glDisable(GL_TEXTURE_2D);
}


void gltest_unload_scene()
{
	current_bg = 0;
	free(current_bg_converted);
	current_bg_converted=0;
	glDeleteTextures(1,&bgtex);
	bgtex=0;
}