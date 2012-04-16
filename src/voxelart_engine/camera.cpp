#include "../../inc/voxelart_engine/camera.h"
#include <GL/glut.h>
#include <iostream>

using namespace std;

vaEngine::Camera::Camera()
:position(0,0,0), lookAt(0,0,-1), upVector(0,1,0) {
}

void vaEngine::Camera::lookThrough(){
	cout << "Camera::lookThrough()" <<endl;
	gluLookAt(
		position.x, position.y, position.z, // hier stehe ich 
		lookAt.x,  lookAt.y, lookAt.z,  // hier schaue ich hin 
		upVector.x,  upVector.y,  upVector.z // dieser Vektor zeigt senkrecht nach oben 
	);  
}
