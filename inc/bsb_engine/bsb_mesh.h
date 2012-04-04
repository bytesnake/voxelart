#ifndef BSB_MESH_H
#define BSB_MESH_H

#include "bsb_texture.h"
//#include "../main.h"
#include "bsb_game.h"

using namespace std;

 // Vertex structure
struct Vertex
{
	GLfloat location[3];
	GLfloat tex[2];
	GLfloat normal[3];
	GLfloat color[4];
	GLubyte padding[16];
};
 
class Bsb_Mesh:Bsb_Object{
	private:
		/*float* colors;
		unsigned char* indices;
		float* texCoords;
		float* normals;
	
		Bsb_Texture* texture;

    	int indices_count;*/
		GLuint vboID; // Vertex Buffer Object ID
		GLuint indexVBOID; // Index Buffer Object ID
		vector<Vertex> vertices;
		vector<GLuint> indices;
    public:
	    Bsb_Mesh();
    	Bsb_Vector* position;
    	virtual void render();
    	void createMesh();
    	void updateMesh();
    	void deleteMesh();
    	void setVertices(vector<Vertex> p_vertices);
    	void setIndices(vector<GLuint> p_indices);
    	
/*    	void setVertices(float[],int);
    	void setColors(float p_colors[]);
    	void setIndices(unsigned char p_indices[],int p_count);
    	void setTextureCoords(float p_texcoords[]);
    	void setNormals(float p_normals[]);
    	void setTexture(Bsb_Texture* p_texture);
    	float* vertices;*/
};

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
