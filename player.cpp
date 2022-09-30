#include "DxLib.h"
#include "game.h"
#include "player.h"

namespace
{
	// �L�����N�^�[�̃T�C�Y
	constexpr float kSizeX = 128.0f;
	constexpr float kSizeY = 128.0f;
	// �W�����v��
	constexpr float kJumpAcc = -16.5f;
	// �d��
	constexpr float kGravity = 1.0f;
}

Player::Player()
{
	m_handle = -1;
	m_fieldY = 0.0f;

	m_isDead = false;
}

void Player::setGraphic(int handle)
{
	m_handle = handle;
	GetGraphSizeF(m_handle ,&m_graphSize.x, &m_graphSize.y);
	m_colSize = m_graphSize;
}

void Player:: setup(float fieldY)
{
	m_fieldY = fieldY;
	m_pos.x = 64.0f;
	m_pos.y = m_fieldY - m_graphSize.y;

	m_vec.x = 0.0f;
	m_vec.y = 0.0f;
}

void Player::update()
{
	if (m_isDead) return;

	m_pos += m_vec;
	// �n�ʂƂ̓����蔻��
	bool isField = false;
	if (m_pos.y > m_fieldY - m_graphSize.y)
	{
		m_pos.y = m_fieldY - m_graphSize.y;
		isField = true;
	}

	// �L�[���͏���
	int padState = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	if (padState & PAD_INPUT_1)
	{
		if (isField)
		{
			m_vec.y = kJumpAcc;	// �W�����v�J�n
		}
	}
	m_vec.y += kGravity;
}

void Player::draw()
{
	if (m_isDead)
	{
		DrawRectGraph(m_pos.x, m_pos.y, 128, 0, 128, 128, m_handle, false, false);
	}
	else
	{
		DrawRectGraph(m_pos.x, m_pos.y, 0, 0, 128, 128, m_handle, false, false);
	}

}

bool Player::isCol(Car& car)
{
	float playerLeft = getPos().x;
	float playerRight = getPos().x + kSizeX;
	float playerTop = getPos().y;
	float playerBottom = getPos().y + kSizeY;

	float carLeft = car.getPos().x;
	float carRight = car.getPos().x + car.getSize().x;
	float carTop = car.getPos().y;
	float carBottom = car.getPos().y + car.getSize().y;

	if (playerLeft > carRight)	return false;
	if (playerRight < carLeft)	return false;
	if (playerTop > carBottom)	return false;
	if (playerBottom < carTop)	return false;

	return true;
}
