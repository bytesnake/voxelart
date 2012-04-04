#include "../inc/cube.h"

// --- cube.cpp ---
// Ein optimierter Würfel/Voxel, der immer nur die Seiten malt, die auch wirklich dargestellt werden müssen.
//
// Änderungen:
// - 21.02.12: Code aufgeräumt (bit)
// - 22.02.12: Code auf Geschwindigkeit optimiert und Würfel auf größe 1 gesetzt (byt)
// - 25.02.12: Würfel werden nun von allen Seiten gerendert (bit)


//    v6----- v5
//   /|      /|
//  v1------v0|
//  | |     | |
//  | |v7---|-|v4
//  |/      |/
//  v2------v3

GLfloat vertices_front[]  = { 0.5, 0.5, 0.5,  -0.5, 0.5, 0.5,  -0.5,-0.5, 0.5,   0.5,-0.5, 0.5};	// v0-v0.5-v2-v3	front
GLfloat vertices_right[]  = { 0.5, 0.5, 0.5,   0.5,-0.5, 0.5,   0.5,-0.5,-0.5,   0.5, 0.5,-0.5};	// v0-v3-v4-v5	right
GLfloat vertices_top[]    = { 0.5, 0.5, 0.5,   0.5, 0.5,-0.5,  -0.5, 0.5,-0.5,  -0.5, 0.5, 0.5};	// v0-v5-v6-v0.5	top
GLfloat vertices_left[]   = {-0.5, 0.5, 0.5,  -0.5, 0.5,-0.5,  -0.5,-0.5,-0.5,  -0.5,-0.5, 0.5};	// v0.5-v6-v7-v2	left
GLfloat vertices_bottom[] = {-0.5,-0.5,-0.5,   0.5,-0.5,-0.5,   0.5,-0.5, 0.5,  -0.5,-0.5, 0.5};	// v7-v4-v3-v2	bottom
GLfloat vertices_back[]   = { 0.5,-0.5,-0.5,  -0.5,-0.5,-0.5,  -0.5, 0.5,-0.5,   0.5, 0.5,-0.5};	// v4-v7-v6-v5	back
                     
GLubyte indices_alw[] = {0,1,2, 0,2,3}; // Die Indizes sind für jede Seite gleich

Cube::Cube(){	
	for(int i=0;i<6;i++){//erstmal alle Seiten unsichtbar machen
		visible[i]=false;
	}
}

void Cube::show(int id) {
	visible[id] = true;
}

void Cube::setColor(float r, float g, float b, float a) {
	color[0] = r; color[1] = g; color[2] = b; color[3] =a;
}

/**
 * schreibt die Vertices und indizes direkt in diesen puffer
 */

void Cube::renderToMesh(float p_x,float p_y,float p_z,vector<Vertex>* p_vertices,vector<GLuint>* p_indices){
	if(visible[0]){renderSideTM(0,p_x,p_y,p_z,p_vertices,p_indices);}
	if(visible[1]){renderSideTM(1,p_x,p_y,p_z,p_vertices,p_indices);}
	if(visible[2]){renderSideTM(2,p_x,p_y,p_z,p_vertices,p_indices);}
	if(visible[3]){renderSideTM(3,p_x,p_y,p_z,p_vertices,p_indices);}
	if(visible[4]){renderSideTM(4,p_x,p_y,p_z,p_vertices,p_indices);}
	if(visible[5]){renderSideTM(5,p_x,p_y,p_z,p_vertices,p_indices);}
}
Vertex tmpvert;
void Cube::renderSideTM(int p_side,float p_x,float p_y,float p_z,vector<Vertex>* p_vertices,vector<GLuint>* p_indices){
	int oldsize=p_vertices->size();

	float normals[3];
	GLfloat* vertices;
	switch(p_side){
		case 0:
			normals[0]=0;
			normals[1]=0;
			normals[2]=1;
			vertices=vertices_front;
			break;
		case 1:
			normals[0]=0;
			normals[1]=0;
			normals[2]=-1;
			vertices=vertices_back;
			break;
		case 2:
			normals[0]=1;
			normals[1]=0;
			normals[2]=0;
			vertices=vertices_right;
			break;
		case 3:
			normals[0]=-1;
			normals[1]=0;
			normals[2]=0;
			vertices=vertices_left;
			break;
		case 4:
			normals[0]=0;
			normals[1]=1;
			normals[2]=0;
			vertices=vertices_top;
			break;
		case 5:
			normals[0]=0;
			normals[1]=-1;
			normals[2]=0;
			vertices=vertices_bottom;
			break;
	}
	
	tmpvert.normal[X_POS]=normals[0];
	tmpvert.normal[Y_POS]=normals[1];
	tmpvert.normal[Z_POS]=normals[2];
	
	tmpvert.color[R_POS]=color[0];
	tmpvert.color[G_POS]=color[1];
	tmpvert.color[B_POS]=color[2];
	tmpvert.color[A_POS]=color[3];

	//all vertices
	for(int i=0; i < 11; i=i+3) {
		tmpvert.location[X_POS]	= p_x+vertices[i];
		tmpvert.location[Y_POS]	= p_y+vertices[i+1];
		tmpvert.location[Z_POS]	= p_z+vertices[i+2];
		p_vertices->push_back(tmpvert);
	}
	
	
	
	p_indices->push_back(oldsize+0);
	p_indices->push_back(oldsize+1);
	p_indices->push_back(oldsize+2);
	p_indices->push_back(oldsize+2);
	p_indices->push_back(oldsize+3);
	p_indices->push_back(oldsize+0);
	

}

