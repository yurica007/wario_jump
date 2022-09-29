#pragma once

#include "Vec2.h"

class Car
{
public:
	Car();
	virtual ~Car() {}

	// �O���t�B�b�N�f�[�^�̐ݒ�	�����ŃT�C�Y���擾����
	void setGraphic(int handle);

	// �����ݒ�	�n�ʂ̍�����^����
	void setup(float fieldY);

	// �X�V
	void update();
	// �`��
	void draw();

	// �ʒu�̎擾
	Vec2 getPos() const { return m_pos; }
	// �T�C�Y�̎擾
	Vec2 getSize() const { return m_size; }

private:
	// �Ԃ̋����̃o���G�[�V����
	typedef enum MoveType
	{
		kMoveTypeNormal,
		kMoveTypeStop,
		kMoveTypeJump,
		kMoveTypeReturn,

		kMoveTypeNum
	};

private:
	void updateNormal();		// �܂������i��
	void updateStop();		// �ꎞ��~�t�F�C���g
	void updateJump();		// �W�����v����
	void updateReturn();		// �r���ň����Ԃ�

private:
	// �O���t�B�b�N�n���h��
	int m_handle;
	// �O���t�B�b�N�̕��ƍ���	�����蔻��ɂ��g�p����
	Vec2 m_size;

	// �Ԃ̋���
	MoveType m_moveType;

	// �ړ��J�n�܂ł̑҂�����
	int m_waitFrame;
	// �ēx�ړ��J�n�܂ł̑҂�����
	int m_againWaitFrame;

	// �ʒu
	Vec2 m_pos;
	// �x�N�g��
	Vec2 m_vec;
	// �n�ʂ̍���
	float m_fieldY;
};