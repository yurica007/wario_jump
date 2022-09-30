#include "DxLib.h"
#include "game.h"

#include "SceneTitle.h"
#include "SceneMain.h"

// �v���O������ WinMain ����n�܂�܂�
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	// window���[�h�ݒ�
	ChangeWindowMode(Game::kWindowMode);
	// �E�C���h�E���ݒ�
	SetMainWindowText(Game::kTitleText);
	// ��ʃT�C�Y�̐ݒ�
	SetGraphMode(Game::kScreenWidth, Game::kScreenHeight, Game::kColorDepth);

	if (DxLib_Init() == -1)		// �c�w���C�u��������������
	{
		return -1;			// �G���[���N�����璼���ɏI��
	}

	// �_�u���o�b�t�@���[�h
	SetDrawScreen(DX_SCREEN_BACK);

	// ���݂̃V�[���ԍ�		0:Title 1:Main
	int sceneNo = 0;

	SceneTitle sceneTitle;
	SceneMain sceneMain;

	switch (sceneNo)
	{
	case 0:
		sceneTitle.init();
		break;
	case 1:
		sceneMain.init();
		break;
	}

	while (ProcessMessage() == 0)
	{
		LONGLONG  time = GetNowHiPerformanceCount();
		// ��ʂ̃N���A
		ClearDrawScreen();

		// �V�[���ύX�t���O
		bool isChange = false;
		switch (sceneNo)
		{
		case 0:
			isChange = sceneTitle.update();
			sceneTitle.draw();
			if (isChange)
			{
				sceneTitle.end();

				sceneMain.init();
				sceneNo = 1;
			}
			break;
		case 1:
			sceneMain.update();
			sceneMain.draw();
			break;
		}

		//����ʂ�\��ʂ����ւ���
		ScreenFlip();

		// esc�L�[����������I������
		if (CheckHitKey(KEY_INPUT_ESCAPE))	break;

		// fps��60�ɌŒ�
		while (GetNowHiPerformanceCount() - time < 16667)
		{
		}
	}
	switch (sceneNo)
	{
	case 0:
		sceneTitle.end();
		break;
	case 1:
		sceneMain.end();
		break;
	}
	DxLib_End();				// �c�w���C�u�����g�p�̏I������

	return 0;				// �\�t�g�̏I�� 
}