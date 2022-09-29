#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	// �҂�����
	constexpr int kWaitFrameMin = 30;
	constexpr int kWaitFrameMax = 300;
	// �Ԃ̑��x
	constexpr float kSpeed = -17.0f;
	// �Ԃ̍s���ꏊ
	constexpr float kActArea = Game::kScreenWidth - 200.0f;
	// �Ԃ̃W�����v��
	constexpr float kJumpAcc = -21.0f;
	// �Ԃ̏d��
	constexpr float kGravity = 1.0f;
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

	// �����̃o���G�[�V������I��
	int randNum = GetRand(99);
	if (randNum < 38)
	{
		m_moveType = kMoveTypeNormal;
	}
	else if (randNum < 68)
	{
		m_moveType = kMoveTypeStop;
	}
	else if (randNum < 98)
	{
		m_moveType = kMoveTypeJump;
	}
	else
	{
		m_moveType = kMoveTypeReturn;
	}

	// �����n�߂�܂ł̎��Ԃ�ݒ�
	m_waitFrame = GetRand(kWaitFrameMin) + kWaitFrameMin;
	// �ēx�����n�߂�܂ł̎��Ԃ�ݒ�
	m_againWaitFrame = GetRand(kWaitFrameMin) + kWaitFrameMin;;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

// �f�o�b�O
	m_moveType = kMoveTypeReturn;

	switch (m_moveType)
	{
	case kMoveTypeNormal:
		updateNormal();
		break;
	case kMoveTypeStop:
		updateStop();
		break;
	case kMoveTypeJump:
		updateJump();
		break;
	case kMoveTypeReturn:
		updateReturn();
		break;
	default:
		updateNormal();
		break;
	}
}

void Car::draw()
{
	DrawGraphF(m_pos.x, m_pos.y, m_handle, true);
}
/*private*/

// �܂������i��
void Car::updateNormal()
{
	m_pos += m_vec;
}
// �ꎞ��~�t�F�C���g
void Car::updateStop()
{
	if (m_pos.x < kActArea)
	{
		if (m_againWaitFrame > 0)
		{
			m_againWaitFrame--;
			m_vec.x = 0.0f;
		}
		else
		{
			m_vec.x = kSpeed;
		}
	}
	m_pos += m_vec;
}
// �W�����v����
void Car::updateJump()
{
	m_pos += m_vec;
	bool isField = false;
	if (m_pos.y > m_fieldY - m_size.y)
	{
		m_pos.y = m_fieldY - m_size.y;
		isField = true;
	}

	if (m_pos.x < kActArea)
	{
		if (isField)
		{
			m_vec.y = kJumpAcc;
		}
	}
	m_vec.y += kGravity;
}
// �r���ň����Ԃ�
void Car::updateReturn()
{
	if (m_pos.x < kActArea)
	{
		if (m_againWaitFrame > 0)
		{
			m_againWaitFrame--;
			m_vec.x = 0.0f;
		}
		else
		{
			if (m_pos.x > kActArea)
			{
				m_vec.x = kSpeed;
			}
			else
			{
				m_vec.x = -kSpeed;
			}
		}
	}
	m_pos += m_vec;
}