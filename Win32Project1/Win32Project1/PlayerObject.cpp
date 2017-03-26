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
	//�����ꂽ�����
	if (_gl_KeyControlObject->Key[KEY_INPUT_Z] == -1 && BomSize > 100) ActivateBom();
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
	if (UsingBom == TRUE) {
		for (auto itr = EnemyBullet->ObjectList.begin(); itr != EnemyBullet->ObjectList.end(); ++itr) {
			if ((*itr)->ObjectDeleteFlag) continue;
			int Hit = ColEllipsPoint(CenterX, CenterY, (BaseObject2D*)(*itr));
			if (Hit == 1) {
				(*itr)->ObjectDelete(); // �Փˑ���̒e������
			}
		}
		Counter--;
		if (Counter == 0) {
			CloseBom();
		}
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
	if (UsingBom == FALSE) {
		if (BomSize < 100) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
			DrawRotaGraph(CenterX, CenterY, 2.0 * BomSize / 450, 0.0, GrazeHandle, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		else if (BomSize >= 100) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawRotaGraph(CenterX, CenterY, 2.0 * BomSize / 450, 0.0, GrazeHandle, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}
	else if (UsingBom == TRUE) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawRotaGraph(BomX, BomY, 2.0 * BomSize / 450, 0.0, GrazeHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	if(BomSize < 100) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
		DrawRotaGraph(CenterX, CenterY, ( 2 / 3 ) * BomSize / 150, 0.0, GrazeHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	else if (BomSize >= 100) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawRotaGraph(CenterX, CenterY, ( 2 / 3 ) * BomSize / 150, 0.0, GrazeHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
}

void PlayerObject::MyPeculiarAction(BaseObject * obj) {
	// ���ɂ�邱�Ƃ͂Ȃ�
}

void PlayerObject::ActivateBom() {
	// �͈͓��̒e��������
	UsingBom = TRUE;
	Counter = 60;
	BomX = CenterX;
	BomY = CenterY;

	// �{���G�t�F�N�g�̕\��
	AnimationObject *AnimationObjectTmp;
	AnimationObjectTmp = new AnimationObject(
		_T("Image/Animation2.png"),
		10,
		1,
		CenterX,
		CenterY);
	AnimationObjectTmp->SetParameter(5, 0, 9); // �A�j���[�V�����p�x�E�J�n�E�I�����Z�b�g
	AnimationObjectTmp->Transparency = 200;
	AnimationObjectTmp->Mode = ADD;
	AnimationObjectTmp->Enlargement = 1.5;
	AddObject(AnimationObjectTmp);

	_gl_mSoundObject->MyPlaySoundMem(_T("Sound/power03.wav"), DX_PLAYTYPE_BACK); // �{�����̍Đ�
}

void PlayerObject::CloseBom() {

	UsingBom = FALSE;
	BomSize = 0.0;
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