#include "../inc/Player.h"

Player::Player()
: m_camera(0,40,0), m_speed(0, 0, 0), m_acc(0, 0, 0) {}

void Player::move(float time) {
	m_camera.walkForward(m_speed.z*time);
	m_camera.strafeLeft(m_speed.z*time);
	m_camera.setSpeedY(m_speed.y*time);	

	m_speed = m_speed + (m_acc * time);
}
