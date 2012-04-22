#ifndef VOXELART_MESH_H
#define VOXELART_MESH_H

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

#include "texture.h"
#include "vector.h"

using namespace std;
using namespace vaEngine;

 // Vertex structure
struct Vertex
{
	GLfloat location[3];
	GLfloat tex[2];
	GLfloat normal[3];
	GLfloat color[4];
	GLubyte padding[16];
};

namespace vaEngine {
	class Mesh {
	    private:
		GLuint vboID; // Vertex Buffer Object ID
		GLuint indexVBOID; // Index Buffer Object ID
		vector<Vertex> vertices;
		vector<GLuint> indices;
		bool isRender, existData;
		GLuint multiTex;

	    public:
		Mesh();
		Mesh(GLuint num);
	    	Vector* position;
	    	virtual void render();
	    	void createMesh();
	    	void updateMesh();
	    	void deleteMesh();

	    	void setVertices(vector<Vertex> p_vertices);
	    	void setIndices(vector<GLuint> p_indices);
		bool isrender() { return isRender; }
		bool existdata() { return existData; }
		vector<Vertex>* getVertices() { return &vertices; }
		vector<GLuint>* getIndices() { return &indices; }
	};
}

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

// A helper macro to get a position
#define BUFFER_OFFSET(i) ((char *)NULL + (i))



#endif
