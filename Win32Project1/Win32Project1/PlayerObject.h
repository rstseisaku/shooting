#include "BaseObject.h"


#pragma once
class PlayerObject : public BaseObject
{
public:
	PlayerObject(const TCHAR * FileName);
	PlayerObject(const TCHAR * FileName, int _LeftX, int _UpperY, BaseObject* mEnemyBulletObject);
	~PlayerObject();

	void InitCommon(const TCHAR * FileName); // constructor����

											 // ��������
	void MyUpdate();
	void MyDraw();
	void MyPeculiarAction(BaseObject * obj);

	int ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp);

	// �摜��12�ɕ����Ǎ�
	int GraphicHandle[100]; // �R���X�g���N�^�Œ�`
	int GraphicPattern;
	int AnimationInterval = 10;
	int AnimationCounter = 0;
	int Life;
	int InvincibleTime;
	int Graze;
	double BomSize;
	int GrazeHandle;
	int EnemyLevel;
	bool UsingBom = FALSE;
	int Counter;
	int BomX;
	int BomY;

	BaseObject* EnemyBullet;
};

