#pragma once

class SceneTitle
{
public:
	SceneTitle();
	virtual ~SceneTitle();

	// �����������A�I������
	void init();
	void end();

	// �Q�[������
	bool update();

	// �`��
	void draw();

private:
	// �t�F�[�h����
	int m_fadeBright;
	// �t�F�[�h���x
	int m_fadeSpeed;
};