#include "Space.h"

extern GLint screenWidth;
extern GLint screenHeight;

void Space::AddForce(float force) {
	m_Force = force;
}
void Space::Update(float deltaTime) {
	float pos_y = Get2DPosition().y;
	float total_force = m_Force - m_Gravity;
	pos_y -= total_force * deltaTime;
	pos_y = pos_y > screenHeight ? screenHeight : pos_y;

	Set2DPosition(Get2DPosition().x, pos_y);

	m_Force -= m_Gravity * deltaTime;
	m_Force = m_Force > 0 ? m_Force : 0;

	ApplyAnimation(total_force);
}
void Space::SetDie() {
	m_Force = 0;
}
void Space::ApplyAnimation(float param)
{
}

void Space::SetTextureState(std::shared_ptr<Texture> up, std::shared_ptr<Texture> down, std::shared_ptr<Texture> idle)
{
	this->up_Texture = up;
	this->down_Texture = down;
	this->idle_Texture = idle;
}