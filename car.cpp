#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	// ‘Ò‚¿ŽžŠÔ
	constexpr int kWaitFrameMin = 30;
	constexpr int kWaitFrameMax = 300;
	// ŽÔ‚Ì‘¬“x
	constexpr float kSpeed = -17.0f;
}

Car::Car()
{
	m_handle = -1;
	m_fieldY = 0.0f;
	m_waitFrame = 0;
}

void Car::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle, &m_size.x, &m_size.y);
}

void Car::setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = Game::kScreenWidth + 16.0f;
	m_pos.y = m_fieldY - m_size.y;

	m_vec.x = kSpeed;
	m_vec.y = 0.0f;

	// “®‚«Žn‚ß‚é‚Ü‚Å‚ÌŽžŠÔ‚ðÝ’è 1~3•b‘Ò‚Â 60~180f
	m_waitFrame = GetRand(kWaitFrameMin) + kWaitFrameMin;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}
	m_pos += m_vec;
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}