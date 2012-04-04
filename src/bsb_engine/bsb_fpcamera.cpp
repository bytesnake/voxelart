	#include "../../inc/bsb_engine/bsb_FPCamera.h"
   //Constructor that takes the starting x, y, z location of the camera
    
    float toRadians(float num){
    	return num * (M_PI/180);
    }
    
    Bsb_FPCamera::Bsb_FPCamera(float x, float y, float z)
    {
        //instantiate position Vector3f to the x y z params.
        position = new Bsb_Vector(x, y, z);
	m_speed = new Bsb_Vector(0,0,0);
        m_yaw=0;
        m_pitch=0;
    }
    //increment the camera's current yaw rotation
    void Bsb_FPCamera::yaw(float amount)
    {
        //increment the yaw by the amount param
        m_yaw += amount;
    }
     
    //increment the camera's current yaw rotation
    void Bsb_FPCamera::pitch(float amount)
    {
        //increment the pitch by the amount param
        m_pitch += amount;
        if(m_pitch>90){
        	m_pitch=90;
        }
        if(m_pitch<-90){
        	m_pitch=-90;
        }        
    }

    void Bsb_FPCamera::stopFall()  {	
	m_speed->y=0;
    }

    //moves the camera forward relative to its current rotation (yaw)
    void Bsb_FPCamera::walkForward(float distance)
    {
        m_speed->x -= distance * (float)sin(toRadians(m_yaw));
        m_speed->z += distance * (float)cos(toRadians(m_yaw));
    }
     
    //moves the camera backward relative to its current rotation (yaw)
    void Bsb_FPCamera::walkBackwards(float distance)
    {
        m_speed->x += distance * (float)sin(toRadians(m_yaw));
        m_speed->z -= distance * (float)cos(toRadians(m_yaw));
    }
     
    //strafes the camera left relitive to its current rotation (yaw)
    void Bsb_FPCamera::strafeLeft(float distance)
    {
        m_speed->x -= distance * (float)sin(toRadians(m_yaw-90));
        m_speed->z += distance * (float)cos(toRadians(m_yaw-90));
    }
     
    //strafes the camera right relitive to its current rotation (yaw)
    void Bsb_FPCamera::strafeRight(float distance)
    {
        m_speed->x -= distance * (float)sin(toRadians(m_yaw+90));
        m_speed->z += distance * (float)cos(toRadians(m_yaw+90));
    }
   
    void Bsb_FPCamera::top(float distance) {
	position->y+=distance;
    }

    void Bsb_FPCamera::jump(){
    	position->y-=1;
    }
    void Bsb_FPCamera::down(){
    	position->y+=1;
    }    

    void Bsb_FPCamera::move(float time) {
	position->z+=m_speed->z*time;
	position->x+=m_speed->x*time;
	position->y+=m_speed->y*time;
	m_speed->div(1.08);
	//m_speed->y += 9.81*time;	
    }
    void Bsb_FPCamera::lookThrough()
    {
        //roatate the pitch around the X axis
        glRotatef(m_pitch, 1.0f, 0.0f, 0.0f);
        //roatate the yaw around the Y axis
        glRotatef(m_yaw, 0.0f, 1.0f, 0.0f);
        //translate to the position vector's location
        glTranslatef(position->x, position->y, position->z);
    }
    
