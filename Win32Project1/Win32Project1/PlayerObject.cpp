#include "stdafx.h"

PlayerObject::PlayerObject(const TCHAR *FileName)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾
}

PlayerObject::PlayerObject(const TCHAR *FileName, int _CenterX, int _CenterY, BaseObject* EnemyBulletObject)
{
	// ����������
	InitCommon(FileName); // �t�@�C��������O���t�B�b�N�n���h���E�T�C�Y���擾(�����摜�Ǎ��p)
	CenterX = _CenterX;
	CenterY = _CenterY;

	// �G�e�Ǘ��I�u�W�F�N�g�ւ̃A�h���X�B(�{�����̒e���ɗ��p)
	EnemyBullet = EnemyBulletObject;
	//�e�����p�̉摜
	GrazeHandle = _gl_mGraphicObject->MyLoadGraphic(_T("Image/graze.png"));
	//�X�R�A�\���p�t�H���g(�{����)
	ScoreFont = CreateFontToHandle(NULL, 24, 3);

	// �{�����������Đ���Ԃ�
	BomPrepareSound = false;
}

PlayerObject::~PlayerObject()
{
	// �q�I�u�W�F�N�g����
	MyDestructor();
}

void PlayerObject::InitCommon(const TCHAR *FileName) {
	// �摜�����ǂݍ���
	int splitX = 3; // ������
	int splitY = 4; // �c����
	_gl_mGraphicObject->MyLoadDivGraphic(FileName, splitX, splitY, GraphicHandle); // �摜�����Ǎ�
	GraphicPattern = 10; // �摜�\���p�^�[���ݒ�
	GetGraphSize(GraphicHandle[0], &WidthX, &HeightY); // �O���t�B�b�N�T�C�Y�̐ݒ�

	// �v���C�����̏�����
	Life = 3; // �c�@
	InvincibleTime = 0; // ���G�^�C��
	BomSize = 0.0; // �{���̑傫��
	GrazeScore = 0.0; // �O���C�Y�ɂ��҂����X�R�A
	EraseScore = 0.0; // �{���ɂ��҂����X�R�A

	// ���C���ݒ�
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

	//�{���̔���
	if (_gl_KeyControlObject->Key[KEY_INPUT_Z] == -1 && BomSize > 100) {
		ActivateBom();
	}

	// �{���T�C�Y�̉��Z
	BomSize += 100.0 / 60 / 30;
	if (BomSize > MaxBomSize)
		BomSize = MaxBomSize;

	// �g���Ɏ��߂鏈��
	if (CenterX <= 35)  CenterX = 35;
	if (CenterY <= 35)  CenterY = 35;
	if (CenterX >= 540)  CenterX = 540;
	if (CenterY >= WindowSizeY - 35)  CenterY = WindowSizeY - 35;

	// �A�j���[�V����( �A�j���[�V�������Ȃ��摜�𗘗p���Ă���̂œ��ɈӖ��͂Ȃ� )
	if (++AnimationCounter == AnimationInterval) {
		if (++AnimationCounter == 12) {
			AnimationCounter = 10;
		}
		AnimationCounter = 0;
	}

	// �{���Œe����������
	if (UsingBom == TRUE) {
		for (auto itr = EnemyBullet->ObjectList.begin(); itr != EnemyBullet->ObjectList.end(); ++itr) {
			if ((*itr)->ObjectDeleteFlag) continue;
			int Hit = ColEllipsPoint(BomX, BomY, (BaseObject2D*)(*itr));
			if (Hit == 1) {
				((BaseObject2D*)(*itr))->Fadeout = 60; // 60�t���[�������Ēe���t�F�[�h�A�E�g����
				((BaseObject2D*)(*itr))->NoHitFlag = true; // �����蔻��̏���
				tmp += ((BaseObject2D*)(*itr))->EraseScore; //�|�C���g���Z
			}
		}
		BomCounter--;	//�t���[���i�߂�
		//60�t���[���o������{�����I��
		if (BomCounter == 0) {
			CloseBom();
		}
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
	
	// �{�����g���ĂȂ��ꍇ
	// (Size��100�����̎��͔����\������)
	if (UsingBom == FALSE) {
		if (BomSize < 100) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
			DrawRotaGraph(CenterX, CenterY, 2.0 * BomSize / 450, 0.0, GrazeHandle, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		//Size��100�ȏ�̎��͔Z���\������
		else if (BomSize >= 100) {
			if (!BomPrepareSound) {
				_gl_mSoundObject->MyPlaySoundMem(_T("Sound/pi48.wav"), DX_PLAYTYPE_BACK); // �{���������̍Đ�
				BomPrepareSound = true;
			}

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawRotaGraph(CenterX, CenterY, 2.0 * BomSize / 450, 0.0, GrazeHandle, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}
	// �{���������͂��̏�ɉ摜��u���Ă���
	else if (UsingBom == TRUE) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawRotaGraph(BomX, BomY, 2.0 * BomSize / 450, 0.0, GrazeHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	// �{���ł̃X�R�A���Z�l��\��
	if (ShowScore == TRUE) {
		DrawFormatStringToHandle(BomX, BomY - 40, GetColor(75 + (120 - ScoreCounter) * 3 / 2, 135 + (120 - ScoreCounter), 195 + (120 - ScoreCounter) / 2), ScoreFont, _T("+%d"), (int)tmp);
		if (ScoreCounter == 0) {
			ShowScore = FALSE;
		}
		ScoreCounter--;
	}
}

void PlayerObject::MyPeculiarAction(BaseObject * obj) {
	// ���ɂ�邱�Ƃ͂Ȃ�
}

void PlayerObject::ActivateBom() {
	// �͈͓��̒e��������
	UsingBom = TRUE;
	tmp = 0.0;
	BomCounter = 60;
	BomX = CenterX;
	BomY = CenterY;
	InvincibleTime = 90;

	// �{�����������Đ���Ԃ�
	BomPrepareSound = false;

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
	//�{���̏I������
	UsingBom = FALSE;
	BomSize = 0.0;
	EraseScore += tmp;

	//�{���œ����X�R�A��\��
	ShowScore = TRUE;
	ScoreCounter = 120;
}

int PlayerObject::ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp) {
	// X�̃T�C�Y�𔻒�Ƃ��ė��p����
	double ElpSizeX = BomSize; // �傫��
	double ElpSizeY = BomSize; // �傫��

	// �_�ɑȉ~���^�~�ϊ��s���K�p(Y�����֊g�傷��)
	double Ofs_x = PlayerX - Elp->CenterX;
	double Ofs_y = PlayerY - Elp->CenterY;
	double After_x = Ofs_x*cos(Elp->Angle) + Ofs_y*sin(Elp->Angle);
	double After_y = ElpSizeX / ElpSizeY * (-Ofs_x*sin(Elp->Angle) + Ofs_y*cos(Elp->Angle));

	// ���_����ړ���_�܂ł̋������Z�o
	if (After_x*After_x + After_y*After_y <= ElpSizeX*ElpSizeX)	return 1;
	return 0;
}