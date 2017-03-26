#include "stdafx.h"

PlayerObject::PlayerObject(const TCHAR *FileName)
{
	InitCommon(FileName);
}

PlayerObject::PlayerObject(const TCHAR *FileName, int _CenterX, int _CenterY, BaseObject* EnemyBulletObject)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;

	EnemyBullet = EnemyBulletObject;

	GrazeHandle = _gl_mGraphicObject->MyLoadGraphic(_T("Image/graze.png"));
	GetGraphSize(GrazeHandle, &GrazeWidth, &GrazeHeight);
}

PlayerObject::~PlayerObject()
{
}


void PlayerObject::InitCommon(const TCHAR *FileName) {
	int splitX = 3;
	int splitY = 4;
	_gl_mGraphicObject->MyLoadDivGraphic(FileName, splitX, splitY, GraphicHandle);
	GraphicPattern = 10;

	GetGraphSize(GraphicHandle[0], &WidthX, &HeightY);
	Life = 3;
	InvincibleTime = 0;
	BomSize = 0.0;

	Layer = Layer_PlayerObject;
}

void PlayerObject::MyUpdate()
{
	// �v���C���[�̓��͂ɉ����Ď��@���ړ�������
	int Speed = 5;
	if (_gl_KeyControlObject->Key[KEY_INPUT_LSHIFT] >= 1) Speed /= 3;
	if (_gl_KeyControlObject->Key[KEY_INPUT_RIGHT] >= 1) CenterX += Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_LEFT] >= 1) CenterX -= Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_DOWN] >= 1) CenterY += Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_UP] >= 1) CenterY -= Speed;

	//�{����
	//������Ă���Ԕ͈͊g��
	if (_gl_KeyControlObject->Key[KEY_INPUT_Z] >= 1) PrepareBom(EnemyBullet);
	//�����ꂽ�����
	if (_gl_KeyControlObject->Key[KEY_INPUT_Z] == -1 && BomSize > 100) ActivateBom(EnemyBullet);
	BomSize += 100.0 / 60 / 30;
	if (BomSize > MaxBomSize)
		BomSize = MaxBomSize;

	if (CenterX <= 35)  CenterX = 35;
	if (CenterY <= 35)  CenterY = 35;
	if (CenterX >= 540)  CenterX = 540;
	if (CenterY >= WindowSizeY - 35)  CenterY = WindowSizeY - 35;

	// ���@���A�j���[�V����������
	if (++AnimationCounter == AnimationInterval) {
		if (++AnimationCounter == 12) {
			AnimationCounter = 10;
		}
		AnimationCounter = 0;
	}

	// �q�I�u�W�F�N�g��MyUpdate���Ăяo��
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}
}

void PlayerObject::MyDraw()
{
	// �I�u�W�F�N�g�̕\��
	SetDrawBlendMode(NORMAL, 255);
	if (InvincibleTime > 0) {
		InvincibleTime--; // ���G���Ԃ����炷
		if (InvincibleTime > 60) { SetDrawBlendMode(NORMAL, 127); } // ���G���Ԓ��͔������ɕ\��
	}
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle[GraphicPattern], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// �q�I�u�W�F�N�g��MyDraw���Ăяo��
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ) {
		if ((*itr)->ObjectDeleteFlag) {
			delete((*itr));
			itr = ObjectList.erase(itr); // �v�f���폜�A���v�f���󂯎��
			continue;
		}
		(*itr)->MyDraw();
		itr++;
	}
	if(BomSize < 100) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		DrawRotaGraph(CenterX, CenterY, 2 * BomSize / 150, 0.0, GrazeHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	else if (BomSize >= 100) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawRotaGraph(CenterX, CenterY, 2 * BomSize / 150, 0.0, GrazeHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void PlayerObject::MyPeculiarAction(BaseObject * obj) {
	// ���ɂ�邱�Ƃ͂Ȃ�
}

void PlayerObject::PrepareBom(BaseObject* Bullet) {
	//BomSize /*= 75; /*/ += 100.0 / 3 / 60;

	if (DEBUG) {
		DrawFormatString(200, 400, GetColor(0, 255, 255), _T("BomSize %lf"), BomSize); // ������`�悷��
	}
}

void PlayerObject::ActivateBom(BaseObject* Bullet) {
	// �͈͓��̒e��������
	for (auto itr = Bullet->ObjectList.begin(); itr != Bullet->ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		int Hit = ColEllipsPoint(CenterX, CenterY, (BaseObject2D*)(*itr));
		if ( Hit == 1) {
			(*itr)->ObjectDelete(); // �Փˑ���̒e������
		}
	}
	BomSize = 0.0;

	// ��e�G�t�F�N�g�̕\��
	AnimationObject *AnimationObjectTmp;
	AnimationObjectTmp = new AnimationObject(
		_T("Image/Animation2.png"),
		10,
		1,
		CenterX,
		CenterY);
	AnimationObjectTmp->SetParameter(3, 0, 9); // �A�j���[�V�����p�x�E�J�n�E�I�����Z�b�g
	AnimationObjectTmp->Transparency = 200;
	AnimationObjectTmp->Mode = ADD;
	AddObject(AnimationObjectTmp);
}

int PlayerObject::ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp) {
	// X�̃T�C�Y�𔻒�Ƃ��ė��p����
	double ElpSizeX = BomSize; // �傫��
	double ElpSizeY = BomSize; // 
												   // �_�ɑȉ~���^�~�ϊ��s���K�p(Y�����֊g�傷��)
	double Ofs_x = PlayerX - Elp->CenterX;
	double Ofs_y = PlayerY - Elp->CenterY;
	double After_x = Ofs_x*cos(Elp->Angle) + Ofs_y*sin(Elp->Angle);
	double After_y = ElpSizeX / ElpSizeY * (-Ofs_x*sin(Elp->Angle) + Ofs_y*cos(Elp->Angle));

	// ���_����ړ���_�܂ł̋������Z�o
	if (After_x*After_x + After_y*After_y <= ElpSizeX*ElpSizeX)	return 1;
	return 0;
}