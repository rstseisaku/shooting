#pragma once

// �e���p�^�[���̃e���v���[�g��ݒ肷��N���X�B
class BulletPattern
{
public:
	BulletPattern();
	~BulletPattern();

	int N; // Nway�e�̐ݒ�
	double Angle; // �N�_�ƂȂ�p�x
	double Span; // Nway�e�̊Ԋu
	double Speed; // �e�̃X�s�[�h
	double X; // �ˏo�ʒu
	double Y; // �ˏo�ʒu
	int Transparency; // ���ߓx
	int CompositeModeParameter; // �������[�h�̐ݒ�
	TCHAR * FileName; // �摜�t�@�C�����̐ݒ�
};