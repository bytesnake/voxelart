#include "../../inc/bsb_engine/bsb_tpcamera.h"
   //Constructor that takes the starting x, y, z location of the camera
    
	extern float toRadians(float num);
    
    Bsb_TPCamera::Bsb_TPCamera(float x, float y, float z)
    {
        //instantiate position Vector3f to the x y z params.
        position = new Bsb_Vector(x, y, z);
        m_yaw=0;
        m_pitch=0;
		m_slant = 0; 
	//	wackel = true;
    }
    //increment the camera's current yaw rotation
    void Bsb_TPCamera::yaw(float amount)
    {
        //increment the yaw by the amount param
        m_yaw += amount;
    }
     
    //increment the camera's current yaw rotation
    void Bsb_TPCamera::pitch(float amount)
    {
        //increment the pitch by the amount param
        m_pitch += amount;
        if(m_pitch>89){
        	m_pitch=89;
        }
        if(m_pitch<-89){
        	m_pitch=-89;
        }        
    }

    //moves the camera forward relative to its current rotation (yaw)
    void Bsb_TPCamera::walkForward(float distance)
    {
        position->x += distance * (float)sin(toRadians(m_yaw));
        position->z += distance * (float)cos(toRadians(m_yaw));
    }
     
    //moves the camera backward relative to its current rotation (yaw)
    void Bsb_TPCamera::walkBackwards(float distance)
    {
        position->x -= distance * (float)sin(toRadians(m_yaw));
        position->z -= distance * (float)cos(toRadians(m_yaw));
    }
     
    //strafes the camera left relitive to its current rotation (yaw)
    void Bsb_TPCamera::strafeLeft(float distance)
    {
        position->x -= distance * (float)sin(toRadians(m_yaw-90));
        position->z -= distance * (float)cos(toRadians(m_yaw-90));
    }
     
    //strafes the camera right relitive to its current rotation (yaw)
    void Bsb_TPCamera::strafeRight(float distance)
    {
        position->x -= distance * (float)sin(toRadians(m_yaw+90));
        position->z -= distance * (float)cos(toRadians(m_yaw+90));
    }
    
    void Bsb_TPCamera::jump(){
    	position->y+=1;
    }
    
    //translates and rotate the matrix so that it looks through the camera
    //this dose basic what gluLookAt() does
  //  using Bsb_Camera:lookThrough;
	void Bsb_TPCamera::lookThrough()
	{
		cout << "Bsb_TPCamera::lookThrough()" <<endl;
		lookAt->x=position->x+5*(sin(toRadians(m_yaw))*cos(toRadians(m_pitch)));
		lookAt->y=position->y+5*sin(toRadians(m_pitch));
		lookAt->z=position->z+5*(cos(toRadians(m_yaw))*cos(toRadians(m_pitch)));
		cout<<(position->x-lookAt->x)<<","<<(position->y-lookAt->y)<<","<<(position->z-lookAt->z)<<endl;
		//Bsb_Camera::lookThrough();
		
    gluLookAt(lookAt->x,  lookAt->y, lookAt->z, // hier stehe ich 
              position->x, position->y, position->z,  // hier schaue ich hin 
              upVector->x,  upVector->y,  upVector->z);  // dieser Vektor zeigt senkrecht nach oben 
	}
/*
		if(wackel){
			m_slant+=5;
		} else {
			m_slant-=5;	
		}
		if(m_slant <-50 | m_slant >50){wackel = !wackel;}
		
        //roatate the pitch around the X axis
        glRotatef(m_pitch, 1.0f, 0.0f, 0.0f);
        //roatate the yaw around the Y axis
        glRotatef(m_yaw, 0.0f, 1.0f, 0.0f);
        glRotatef(m_slant,0.0f,0.0f,1.0f);
        //translate to the position vector's location
        glTranslatef(position->x, position->y, position->z);
    }*/
    
