#pragma once

#include "player.h"
#include "car.h"

class SceneMain
{
public:
	SceneMain();
	virtual ~SceneMain();

	// �����������A�I������
	void init();
	void end();

	// �Q�[������
	bool update();

	// �`��
	void draw();

private:
	// �O���t�B�b�N�n���h��
	int m_hPlayer;
	int m_hCar;

	// �v���C���[
	Player m_player;
	// �G
	Car m_car;
};