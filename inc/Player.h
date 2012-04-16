#ifndef Player_H
#define Player_H

#include <iostream>
#include "voxelart_engine/fpcamera.h"
#include "voxelart_engine/vector.h"

class Player
{
	private:
		vaEngine::Vector m_speed;
		vaEngine::Vector m_acc;
		float m_atten;
		float m_yaw, m_pitch;
		vaEngine::FPCamera m_camera;
	public:
		Player();
		vaEngine::Vector getSpeed() { return m_speed; }
		vaEngine::Vector getAcc() { return m_acc; }
		void addSpeed(vaEngine::Vector speed) { m_speed = m_speed + speed; }
		void addAcc(vaEngine::Vector acc) { m_acc = m_acc + acc; }
		void setAtt(float atten) { m_atten = atten; }

		void move(float time);
		

		
		
	
			
};
#endif
