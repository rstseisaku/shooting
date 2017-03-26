#include "stdafx.h"

PlayerObject::PlayerObject( const TCHAR *FileName )
{
	InitCommon(FileName);
}

PlayerObject::PlayerObject(const TCHAR *FileName, int _CenterX,int _CenterY)
{
	InitCommon(FileName);
	CenterX = _CenterX;
	CenterY = _CenterY;
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

	Layer = Layer_PlayerObject;
}

void PlayerObject::MyUpdate() 
{
	// �v���C���[�̓��͂ɉ����Ď��@���ړ�������
	int Speed = 5;
	if (_gl_KeyControlObject->Key[KEY_INPUT_LSHIFT] >= 1) Speed /= 3;
	if (_gl_KeyControlObject->Key[KEY_INPUT_RIGHT] >= 1) CenterX += Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_LEFT] >= 1) CenterX -= Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_DOWN] >= 1) CenterY+= Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_UP] >= 1) CenterY -= Speed;

	if (CenterX <= MoveableAreaLeft)  CenterX = MoveableAreaLeft;
	if (CenterY <= MoveableAreaUpper)  CenterY = MoveableAreaUpper;
	if (CenterX >= MoveableAreaRight)  CenterX = MoveableAreaRight;
	if (CenterY >= MoveableAreaButtom)  CenterY = MoveableAreaButtom;

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
		if (InvincibleTime > 60) {	SetDrawBlendMode(NORMAL, 127); } // ���G���Ԓ��͔������ɕ\��
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

	if (DEBUG) {
		DrawFormatString(200, 450, GetColor(0, 255, 255), _T("(Screen)Life %d"), Life); // ������`�悷��
		DrawFormatString(100, 50, GetColor(0, 255, 255), _T("x,y %f %f"), CenterX,CenterY); // ������`�悷��
	}
}

void PlayerObject::MyPeculiarAction(BaseObject * obj) {
	// ���ɂ�邱�Ƃ͂Ȃ�
}