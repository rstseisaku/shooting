#include "stdafx.h"


/*
* �G�e���Ǘ����邽�߂̃N���X
* �v���C���Ƃ̂����蔻�菈���������ōs��
*/
mEnemyBullet::mEnemyBullet()
{
	// ���C����ݒ肷�邾��
	Layer = Layer_EnemyBullet;
}

void mEnemyBullet::MyUpdate()
{
	// �����t���O�𗧂Ă�
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}
}

// �v���C���[�I�u�W�F�N�g���󂯎��A�����蔻��̏������s��
void mEnemyBullet::MyPeculiarAction(BaseObject * PlayerObj) {
	// �󂯎��I�u�W�F�N�g���v���C���I�u�W�F�N�g���m�F
	if (PlayerObj->Layer != Layer_PlayerObject) return;

	// �󂯎�����v���C���I�u�W�F�N�g����l���擾
	double PlayerObjectCenterX = PlayerObj->CenterX;
	double PlayerObjectCenterY = PlayerObj->CenterY;

	// �Ǘ����Ă���e�I�u�W�F�N�g�Ɠ����蔻����s��
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;

		// �ȉ~�Ɠ_�Ƃ̂����蔻��
		int Hit = ColEllipsPoint(PlayerObjectCenterX, PlayerObjectCenterY, (BaseObject2D*)(*itr));

		// Hit = 1 �Ȃ�A��e����
		if ( Hit == 1 && (((PlayerObject *)PlayerObj)->InvincibleTime == 0) ) {
			(*itr)->ObjectDelete(); // �Փˑ���̒e������
			((PlayerObject *)PlayerObj)->Life--; // �c�@�����炷
			((PlayerObject *)PlayerObj)->InvincibleTime = 120; // ���G���Ԃ��Z�b�g

			// ��e�G�t�F�N�g�̕\��
			AnimationObject *AnimationObjectTmp;
			AnimationObjectTmp = new AnimationObject(
				_T("Image/Animation1.png"), 
				7, 
				1, 
				((PlayerObject *)PlayerObj)->CenterX,
				((PlayerObject *)PlayerObj)->CenterY);
			AnimationObjectTmp->SetParameter( 3, 0, 7); // �A�j���[�V�����p�x�E�J�n�E�I�����Z�b�g
			((PlayerObject *)PlayerObj)->AddObject( AnimationObjectTmp );

			_gl_mSoundObject->MyPlaySoundMem( _T("Sound/bom18.wav"), DX_PLAYTYPE_BACK ); // ��e���Đ�
			break; // ���t���[���ŕ����̒e�ɓ�����Ȃ�
		} else if (Hit >= 2) { 	   // Hit = 2 �Ȃ�A�O���C�Y����
			((BaseObject2D *)(*itr))->GrazeFlag = true;
			_gl_mSoundObject->MyPlaySoundMem(_T("Sound/hit27.wav"), DX_PLAYTYPE_BACK); // �O���C�Y���Đ�
			((PlayerObject *)PlayerObj)->BomSize += 5.0; // �{���������傫������
			((PlayerObject *)PlayerObj)->GrazeScore += ((BaseObject2D *)(*itr))->GrazeScore; // �X�R�A���Z
		}
	}
}

void mEnemyBullet::MyDraw()
{
	// �����Ă���e����\��
	for (auto itr = ObjectList.begin(); itr != ObjectList.end();  ) {
		if ((*itr)->ObjectDeleteFlag) {
			delete((*itr));
			itr = ObjectList.erase( itr ); // �v�f���폜�A���v�f���󂯎��
			continue;
		}
		(*itr)->MyDraw();
		itr++;
	}

	if (DEBUG) {
		DrawFormatString(45, 45, GetColor(0, 255, 255), _T("�e�� %d"), ObjectList.size()); // ������`�悷��
		DrawFormatString(45, 65, GetColor(0, 255, 255), _T("�O���C�Y/�{�� %d,%lf"), SetGrazeScore, SetEraseScore); // ������`�悷��
	}
}

// BulletPattern�ɏ]���Ēe���𐶐�
void mEnemyBullet::MakeBullet( BulletPattern *BulletPatternObj ) 
{
	double Angle = BulletPatternObj->Angle - (BulletPatternObj->N - 1) * ( BulletPatternObj->Span / 2 );
	for (int i = 0; i < BulletPatternObj->N; i++) {
		Bullet2 *tmp = new Bullet2(
			BulletPatternObj->FileName,
			BulletPatternObj->X,
			BulletPatternObj->Y,
			Angle,
			BulletPatternObj->Speed,
			BulletPatternObj->CompositeModeParameter,
			BulletPatternObj->Transparency);
		tmp->vAngle = BulletPatternObj->vAngle;
		tmp->vAngleRate = BulletPatternObj->vAngleRate;
		AddBullet(tmp);

		Angle += BulletPatternObj->Span;
	}
}

void mEnemyBullet::AddBullet(BaseObject * obj)
{
	// �X�R�A����t�������āA�e�������ۂɐ���
	((BaseObject2D*)obj)->GrazeScore = SetGrazeScore;
	((BaseObject2D*)obj)->EraseScore = SetEraseScore/60;
	ObjectList.push_back(obj);
}


mEnemyBullet::~mEnemyBullet()
{
	MyDestructor();
}

// �ȉ~�Ɠ_�Ƃ̂����蔻�菈��
// 0 = NO HIT
// 1 = HIT
// 2 = GRAZE
int mEnemyBullet::ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp)
{
	// X�̃T�C�Y�𔻒�Ƃ��ė��p����
	double ElpSizeX = Elp->WidthX * 0.4; // �����蔻��X
	double ElpSizeY = Elp->HeightY * 0.4; // �����蔻��Y
	double ElpGrazeSizeX = Elp->WidthX * 1.1; // �O���C�Y�p�̔���
	if (Elp->GrazeFlag == true) ElpGrazeSizeX = 0; // ���ɃO���C�Y���Ă����画�������

	// �_�ɑȉ~���^�~�ϊ��s���K�p(Y�����֊g�傷��)
	double Ofs_x = PlayerX - Elp->CenterX;
	double Ofs_y = PlayerY - Elp->CenterY;
	double After_x = Ofs_x*cos(Elp->Angle) + Ofs_y*sin(Elp->Angle);
	double After_y = ElpSizeX / ElpSizeY * (-Ofs_x*sin(Elp->Angle) + Ofs_y*cos(Elp->Angle));

	if (DEBUG) {
		DrawFormatString(5, 35, GetColor(0, 255, 255), _T("dist %f"), After_x*After_x + After_y*After_y); // ������`�悷��
		DrawFormatString(305, 35, GetColor(0, 255, 255), _T("elp(x,y) %f,%f"), Elp->CenterX, Elp->CenterY); // ������`�悷��
	}

	// ���_����ړ���_�܂ł̋������Z�o
	if (After_x*After_x + After_y*After_y <= ElpSizeX*ElpSizeX) {
		if (Elp->NoHitFlag == true) return 0;
		return 1;
	}
	if (After_x*After_x + After_y*After_y <= ElpGrazeSizeX*ElpGrazeSizeX) {
		if (Elp->NoHitFlag == true) return 0;
		return 2;
	}
	return 0;
}