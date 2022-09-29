#include "DxLib.h"
#include "game.h"
#include "car.h"

namespace
{
	// 待ち時間
	constexpr int kWaitFrameMin = 30;
	constexpr int kWaitFrameMax = 300;
	// 車の速度
	constexpr float kSpeed = -17.0f;
	// 車の行動場所
	constexpr float kActArea = Game::kScreenWidth - 200.0f;
	// 車のジャンプ力
	constexpr float kJumpAcc = -21.0f;
	// 車の重力
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

	// 動きのバリエーションを選択
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

	// 動き始めるまでの時間を設定
	m_waitFrame = GetRand(kWaitFrameMin) + kWaitFrameMin;
	// 再度動き始めるまでの時間を設定
	m_againWaitFrame = GetRand(kWaitFrameMin) + kWaitFrameMin;;
}

void Car::update()
{
	if (m_waitFrame > 0)
	{
		m_waitFrame--;
		return;
	}

// デバッグ
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

// まっすぐ進む
void Car::updateNormal()
{
	m_pos += m_vec;
}
// 一時停止フェイント
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
// ジャンプする
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
// 途中で引き返す
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