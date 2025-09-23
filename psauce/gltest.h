
#include <inttypes.h>

#define PSAUCE_GLTEST_ACTIVE 1

#if PSAUCE_GLTEST_ACTIVE == 0
#undef PSAUCE_GLTEST_ACTIVE
#endif

void gltest_init();

/* 
	C version of class RMesh 
*/
struct gltest_mesh_s
{
	int16_t m_sNum;												// Number of triangles in array (3 elements per triangle!)
	uint16_t* m_pArray;	
};

struct gltest_point_s
{
	float v[4];
};


void gltest_render(int x, int y,struct gltest_mesh_s* mesh);
#define gltest_render_rmesh(x,y,MESH) gltest_render(x,y,reinterpret_cast<struct gltest_mesh_s*>(MESH))

void gltest_preparerender();
void gltest_postrender();