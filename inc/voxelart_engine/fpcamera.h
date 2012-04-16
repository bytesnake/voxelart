#ifndef VOXELART_FPCAMERA_H
#define VOXELART_FPCAMERA_H
#include "vector.h"
#include <GL/gl.h>

using namespace vaEngine;
namespace vaEngine {
	class FPCamera/*: public Camera*/{
		private:
	    	//the rotation around the Y axis of the camera
			float       m_yaw;  		//the rotation around the X axis of the camera
			float       m_pitch;
			float       m_slant;
			Vector m_speed;

		public:
			Vector position;
			FPCamera(float x, float y, float z);
			void yaw(float amount);
			void pitch(float amount);
			void walkForward(float distance);
			void walkBackwards(float distance);
			void strafeLeft(float distance);
			void strafeRight(float distance);
			void setSpeedY(float y);
			void addSpeedY(float y);
			void move(float time);
			void lookThrough();
			//TODO: In Spieler auslagern
			bool jump;
	};
}

#endif
