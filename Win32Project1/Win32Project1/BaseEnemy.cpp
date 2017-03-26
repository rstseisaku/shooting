#include "stdafx.h"
#include "BaseEnemy.h"


BaseEnemy::BaseEnemy(const TCHAR * FileName, mEnemyBullet * obj, PlayerObject * _PlayerObjectInstance)
{
	InitCommon(FileName);
	mEnemyBulletObject = obj;
	PlayerObjectInstance = _PlayerObjectInstance;
	Pattern = NOSELECTED;
}

BaseEnemy::BaseEnemy(const TCHAR * FileName, mEnemyBullet * obj, PlayerObject * _PlayerObjectInstance, double _X, double _Y)
{
	InitCommon(FileName);
	mEnemyBulletObject = obj;
	PlayerObjectInstance = _PlayerObjectInstance;
	CenterX = _X;
	CenterY = _Y;
	Pattern = NOSELECTED;
}

BaseEnemy::~BaseEnemy()
{
}

double BaseEnemy::GetAngleToPlayer() {
	// ���@�ւ̊p�x�����߂�
	double Ans =
		atan2(PlayerObjectInstance->CenterY - CenterY,
			PlayerObjectInstance->CenterX - CenterX);
	Ans = Ans * 180.0 / M_PI; // �x = ���W�A�� �~ 180 �� �~����
	return Ans;
}