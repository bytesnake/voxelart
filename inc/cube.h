#ifndef CUBE_H
#define CUBE_H

#include <boost/shared_ptr.hpp>
#include "voxelart_engine/mesh.h"

//#include "world.h"

// Location/Normals
#define X_POS 0
#define Y_POS 1
#define Z_POS 2

// Texture Coordinates
#define U_POS 0
#define V_POS 1

// Colours
#define R_POS 0
#define G_POS 1
#define B_POS 2
#define A_POS 3

#ifndef VOXELART_MESH_H
#define VOXELART_MESH_H
// Vertex structure
struct Vertex
{
	GLfloat location[3];
	GLfloat tex[2];
	GLfloat normal[3];
	GLfloat color[4];
	GLubyte padding[16];
};
#endif
using namespace std;

struct Cube
{
	typedef boost::shared_ptr<Cube> pointer_t;

	/**
	 * 0: front
	 * 1: back
	 * 2: right
	 * 3: left
	 * 4: top
	 * 5: bottom
	 */
	bool visible[6];
	float color[4];
	float a; // Seitenlänge
	void show(int id);
	void hide(int id);
	void setColor(float r, float g, float b, float a);	
	GLfloat* multVert(float b, GLfloat* a);
	
	void renderToMesh(float p_x,float p_y,float p_z,vector<Vertex>* p_vertices,vector<GLuint>* p_indices);
	void renderSideTM(int p_side,float p_x,float p_y,float p_z,vector<Vertex>* p_vertices,vector<GLuint>* p_indices);
	Cube(float a);
	//~Cube();
};
#endif
