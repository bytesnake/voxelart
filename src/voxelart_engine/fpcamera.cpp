#include "../../inc/voxelart_engine/fpcamera.h"

//Constructor that takes the starting x, y, z location of the camera
vaEngine::FPCamera::FPCamera(float x, float y, float z) 
: m_speed(0,0,0), position(x,y,z) {
	//instantiate position Vector3f to the x y z params.
	m_yaw=0;
	m_pitch=0;
	jump = false;
}
    
float toRadians(float num) {
	return num * (M_PI/180);
}
    
//increment the camera's current yaw rotation
void vaEngine::FPCamera::yaw(float amount) {
	m_yaw += amount;
}
     
//increment the camera's current yaw rotation
void vaEngine::FPCamera::pitch(float amount) {
	//increment the pitch by the amount param
	m_pitch += amount;
	if(m_pitch>90){
		m_pitch=90;
	}
	if(m_pitch<-90){
		m_pitch=-90;
	}        
}

void vaEngine::FPCamera::setSpeedY(float y)  {
	m_speed.y = y;
}

void vaEngine::FPCamera::addSpeedY(float y)  {
	m_speed.y += y;
}

//moves the camera forward relative to its current rotation (yaw)
void vaEngine::FPCamera::walkForward(float distance) {
	m_speed.x -= distance * (float)sin(toRadians(m_yaw));
	m_speed.z += distance * (float)cos(toRadians(m_yaw));
}
     
//moves the camera backward relative to its current rotation (yaw)
void vaEngine::FPCamera::walkBackwards(float distance) {
	m_speed.x += distance * (float)sin(toRadians(m_yaw));
	m_speed.z -= distance * (float)cos(toRadians(m_yaw));
}
     
//strafes the camera left relitive to its current rotation (yaw)
void vaEngine::FPCamera::strafeLeft(float distance) {
	m_speed.x -= distance * (float)sin(toRadians(m_yaw-90));
	m_speed.z += distance * (float)cos(toRadians(m_yaw-90));
}
     
//strafes the camera right relitive to its current rotation (yaw)
void vaEngine::FPCamera::strafeRight(float distance) {
	m_speed.x -= distance * (float)sin(toRadians(m_yaw+90));
	m_speed.z += distance * (float)cos(toRadians(m_yaw+90));
}

void vaEngine::FPCamera::move(float time) {
	//position.z+=m_speed->z*time;
	//position.x+=m_speed->x*time;
	//position.y+=m_speed->y*time;
	position += m_speed * time;
	//TODO: Dämpfung verbessern
	m_speed.z /= 1.2;
	m_speed.x /= 1.2;
}

void vaEngine::FPCamera::lookThrough() {
	//roatate the pitch around the X axis
	glRotatef(m_pitch, 1.0f, 0.0f, 0.0f);
	//roatate the yaw around the Y axis
	glRotatef(m_yaw, 0.0f, 1.0f, 0.0f);
	//translate to the position vector's location
	glTranslatef(position.x, position.y, position.z);
}
    
