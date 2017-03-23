#include "stdafx.h"

mEnemyBullet::mEnemyBullet()
{
	Layer = Layer_EnemyBullet;
}

void mEnemyBullet::MyUpdate()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}
}

void mEnemyBullet::MyPeculiarAction(BaseObject * PlayerObj) {
	// �v���C���[�I�u�W�F�N�g���󂯎��A�����蔻��̏������s��
	double PlayerObjectCenterX = PlayerObj->CenterX;
	double PlayerObjectCenterY = PlayerObj->CenterY;

	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;

		if (ColEllipsPoint(PlayerObjectCenterX, PlayerObjectCenterY, (BaseObject2D*)(*itr))) {
			// �Փ�
			(*itr)->ObjectDelete();
			// DrawFormatString(5, 5, GetColor(0, 255, 255), _T("HIT!")); // ������`�悷��

			// ���������A�u�W�F�N�g�S�Ăɑ΂���Hit���Ăяo��(�����ɑΏۃC�e���^)��
			// �l������( Unity�Ƃ��̎d�g�� )
			// ����̓v���C���ƓG�e�ɍi���ď�����g��
		}
	}
}

void mEnemyBullet::MyDraw()
{
	for (auto itr = ObjectList.begin(); itr != ObjectList.end();  ) {
		if ((*itr)->ObjectDeleteFlag) {
			delete((*itr));
			itr = ObjectList.erase( itr ); // �v�f���폜�A���v�f���󂯎��
			continue;
		}
		(*itr)->MyDraw();
		itr++;
	}

	DrawFormatString(45, 45, GetColor(0, 255, 255), _T("�e�� %d"), ObjectList.size()); // ������`�悷��
}

void mEnemyBullet::MakeBullet( BulletPattern *BulletPatternObj ) 
{
	double Angle = BulletPatternObj->Angle - (BulletPatternObj->N - 1) * BulletPatternObj->Span;
	for (int i = 0; i < BulletPatternObj->N; i++) {
		Bullet2 *tmp = new Bullet2(
			BulletPatternObj->FileName,
			BulletPatternObj->X,
			BulletPatternObj->Y,
			Angle,
			BulletPatternObj->Speed,
			BulletPatternObj->CompositeModeParameter,
			(int)BulletPatternObj->Transparency);
		tmp->vAngle = BulletPatternObj->vAngle;
		tmp->vAngleRate = BulletPatternObj->vAngleRate;
		AddObject(tmp);

		Angle += BulletPatternObj->Span;
	}
}

mEnemyBullet::~mEnemyBullet()
{
}

bool mEnemyBullet::ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp)
{
	double ElpSizeX = Elp->WidthX * 0.4;
	double ElpSizeY = Elp->HeightY * 0.4;

	// �_�ɑȉ~���^�~�ϊ��s���K�p
	double Ofs_x = PlayerX - Elp->CenterX;
	double Ofs_y = PlayerY - Elp->CenterY;
	double After_x = Ofs_x*cos(Elp->Angle) + Ofs_y*sin(Elp->Angle);
	double After_y = ElpSizeX / ElpSizeY * (-Ofs_x*sin(Elp->Angle) + Ofs_y*cos(Elp->Angle));


	DrawFormatString(5, 35, GetColor(0, 255, 255), _T("dist %f"), After_x*After_x + After_y*After_y); // ������`�悷��
	DrawFormatString(305, 35, GetColor(0, 255, 255), _T("elp(x,y) %f,%f"), Elp->CenterX , Elp->CenterY ); // ������`�悷��


	// ���_����ړ���_�܂ł̋������Z�o
	if (After_x*After_x + After_y*After_y <= ElpSizeX*ElpSizeX)
		return true;   // �Փ�
	return false;
}