#include "../../inc/voxelart_engine/light.h"

// --- bsb_light.cpp ---
// Hier gibt es ein paar Hilfsfunktionen zum Licht
//
// Änderungen:
// - 21.02.12: Datei erstellt (bit)
int glLights[8]={GL_LIGHT0,GL_LIGHT1,GL_LIGHT2,GL_LIGHT3,GL_LIGHT4,GL_LIGHT5,GL_LIGHT6,GL_LIGHT7};

Light* lights[8];

void glActivateLight(int p_light){
	lights[p_light]=new Light();
	glEnable(glLights[p_light]);
}
void glDisableLight(int p_light){
	lights[p_light]=NULL;
	glDisable(glLights[p_light]);
}

void glSetLightPosition(int p_light, float p_x,float p_y,float p_z){
	lights[p_light]->position[0]=p_x;
	lights[p_light]->position[1]=p_y;
	lights[p_light]->position[2]=p_z;
	lights[p_light]->position[3]=1.0f;
}
void glSetLightDirection(int p_light, float p_x,float p_y,float p_z){
	lights[p_light]->position[0]=p_x;
	lights[p_light]->position[1]=p_y;
	lights[p_light]->position[2]=p_z;
	lights[p_light]->position[3]=0.0f;	
}

void glSetLightAmbient(int p_light,float p_r,float p_g,float p_b,float p_a){
	lights[p_light]->ambient[0]=p_r;
	lights[p_light]->ambient[1]=p_g;
	lights[p_light]->ambient[2]=p_b;
	lights[p_light]->ambient[3]=p_a;
}
void glSetLightDiffuse(int p_light,float p_r,float p_g,float p_b,float p_a){
	lights[p_light]->diffuse[0]=p_r;
	lights[p_light]->diffuse[1]=p_g;
	lights[p_light]->diffuse[2]=p_b;
	lights[p_light]->diffuse[3]=p_a;	
}
void glUpdateLight(int p_light){
	if(lights[p_light]->ambient!=NULL){
		glLightfv(GL_LIGHT0, GL_AMBIENT,lights[p_light]->ambient);
	}
	if(lights[p_light]->diffuse!=NULL){
		glLightfv(GL_LIGHT0, GL_DIFFUSE,lights[p_light]->diffuse);
	}
}
void glUpdateLights(){
	glEnable(GL_LIGHTING); //Licht an
	for(int i=0;i<8;i++){
		if(lights[i]!=NULL){
			glLightfv(glLights[i], GL_POSITION, lights[i]->position); //Lichtposition wird gesetzt
		}
	}
}
