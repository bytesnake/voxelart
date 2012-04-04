#include "../../inc/bsb_engine/bsb_camera.h"
#include <GL/glut.h>
#include <iostream>

using namespace std;

Bsb_Camera::Bsb_Camera(){
	position=new Bsb_Vector(0,0,0);
	lookAt=new Bsb_Vector(0,0,-1);
	upVector=new Bsb_Vector(0,1,0);
}
void Bsb_Camera::lookThrough(){
	cout << "Bsb_Camera::lookThrough()" <<endl;
    gluLookAt(position->x, position->y, position->z, // hier stehe ich 
              lookAt->x,  lookAt->y, lookAt->z,  // hier schaue ich hin 
              upVector->x,  upVector->y,  upVector->z);  // dieser Vektor zeigt senkrecht nach oben 
}
