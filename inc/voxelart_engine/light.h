#ifndef VOXELART_LIGHT_H
#define VOXELART_LIGHT_H

#include <iostream>
#include <GL/gl.h>

struct Light{
	float position[4];
	float ambient[4];
	float diffuse[4];
	float spot_directon[3];
	float spot_cutoff;
};

void glActivateLight(int p_light);
void glDisableLight(int p_light);
void glUpdateLight(int p_light);
void glSetLightPosition(int p_light, float p_x,float p_y,float p_z);
void glSetLightDirection(int p_light, float p_x,float p_y,float p_z);
void glSetLightAmbient(int p_light,float p_r,float p_g,float p_b,float p_a);
void glSetLightDiffuse(int p_light,float p_r,float p_g,float p_b,float p_a);

// sollte immer aufgerufen werden, wenn die Modelmatrix reloaded wird
// (nach camera->lookThrough())
void glUpdateLights();



#endif
