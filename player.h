#pragma once

#include "Vec2.h"
#include "car.h"

class Player
{
public:
	Player();
	virtual ~Player() {}

	// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
	void setGraphic(int handle);

	// �����ݒ�	�n�ʂ̍�����^����
	void setup( float fieldY );

	// �X�V
	void update();
	// �`��
	void draw();

	// �ԂƂ̏Փ˔���
	bool isCol(Car& car);

	// �ʒu�̎擾
	Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	Vec2 getGraphSize() const { return m_graphSize; }
	Vec2 getColSize() const { return m_colSize; }

	// ���S�ݒ�
	void setDead(bool isDead) { m_isDead = isDead; }

private:
	// �O���t�B�b�N�n���h��
	int m_handle;
	// �O���t�B�b�N�̕��ƍ���
	Vec2 m_graphSize;
	// �����蔻��̕��ƍ���
	Vec2 m_colSize;

	// �ʒu
	Vec2 m_pos;
	// �x�N�g��
	Vec2 m_vec;
	// �n�ʂ̍���
	float m_fieldY;

	bool m_isDead;
};