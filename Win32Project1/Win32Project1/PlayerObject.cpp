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
	// プレイヤーの入力に応じて自機を移動させる
	int Speed = 5;
	if (_gl_KeyControlObject->Key[KEY_INPUT_LSHIFT] >= 1) Speed /= 3;
	if (_gl_KeyControlObject->Key[KEY_INPUT_RIGHT] >= 1) CenterX += Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_LEFT] >= 1) CenterX -= Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_DOWN] >= 1) CenterY += Speed;
	if (_gl_KeyControlObject->Key[KEY_INPUT_UP] >= 1) CenterY -= Speed;

	//ボムる
	//離された時解放
	if (_gl_KeyControlObject->Key[KEY_INPUT_Z] == -1 && BomSize > 100) ActivateBom();
	BomSize += 100.0 / 60 / 30;
	if (BomSize > MaxBomSize)
		BomSize = MaxBomSize;

	if (CenterX <= 35)  CenterX = 35;
	if (CenterY <= 35)  CenterY = 35;
	if (CenterX >= 540)  CenterX = 540;
	if (CenterY >= WindowSizeY - 35)  CenterY = WindowSizeY - 35;

	// 自機をアニメーションさせる
	if (++AnimationCounter == AnimationInterval) {
		if (++AnimationCounter == 12) {
			AnimationCounter = 10;
		}
		AnimationCounter = 0;
	}

	// 子オブジェクトのMyUpdateを呼び出す
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}
	if (UsingBom == TRUE) {
		for (auto itr = EnemyBullet->ObjectList.begin(); itr != EnemyBullet->ObjectList.end(); ++itr) {
			if ((*itr)->ObjectDeleteFlag) continue;
			int Hit = ColEllipsPoint(CenterX, CenterY, (BaseObject2D*)(*itr));
			if (Hit == 1) {
				(*itr)->ObjectDelete(); // 衝突相手の弾を消す
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
	// オブジェクトの表示
	SetDrawBlendMode(NORMAL, 255);
	if (InvincibleTime > 0) {
		InvincibleTime--; // 無敵時間を減らす
		if (InvincibleTime > 60) { SetDrawBlendMode(NORMAL, 127); } // 無敵時間中は半透明に表示
	}
	DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle[GraphicPattern], true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);

	// 子オブジェクトのMyDrawを呼び出す
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ) {
		if ((*itr)->ObjectDeleteFlag) {
			delete((*itr));
			itr = ObjectList.erase(itr); // 要素を削除、次要素を受け取る
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
	// 特にやることはない
}

void PlayerObject::ActivateBom() {
	// 範囲内の弾幕を消す
	UsingBom = TRUE;
	Counter = 60;
	BomX = CenterX;
	BomY = CenterY;

	// ボムエフェクトの表示
	AnimationObject *AnimationObjectTmp;
	AnimationObjectTmp = new AnimationObject(
		_T("Image/Animation2.png"),
		10,
		1,
		CenterX,
		CenterY);
	AnimationObjectTmp->SetParameter(5, 0, 9); // アニメーション頻度・開始・終了をセット
	AnimationObjectTmp->Transparency = 200;
	AnimationObjectTmp->Mode = ADD;
	AnimationObjectTmp->Enlargement = 1.5;
	AddObject(AnimationObjectTmp);

	_gl_mSoundObject->MyPlaySoundMem(_T("Sound/power03.wav"), DX_PLAYTYPE_BACK); // ボム音の再生
}

void PlayerObject::CloseBom() {

	UsingBom = FALSE;
	BomSize = 0.0;
}

int PlayerObject::ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp) {
	// Xのサイズを判定として利用する
	double ElpSizeX = BomSize; // 大きさ
	double ElpSizeY = BomSize; // 
												   // 点に楕円→真円変換行列を適用(Y方向へ拡大する)
	double Ofs_x = PlayerX - Elp->CenterX;
	double Ofs_y = PlayerY - Elp->CenterY;
	double After_x = Ofs_x*cos(Elp->Angle) + Ofs_y*sin(Elp->Angle);
	double After_y = ElpSizeX / ElpSizeY * (-Ofs_x*sin(Elp->Angle) + Ofs_y*cos(Elp->Angle));

	// 原点から移動後点までの距離を算出
	if (After_x*After_x + After_y*After_y <= ElpSizeX*ElpSizeX)	return 1;
	return 0;
}