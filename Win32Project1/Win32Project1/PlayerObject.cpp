#include "stdafx.h"

PlayerObject::PlayerObject(const TCHAR *FileName)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
}

PlayerObject::PlayerObject(const TCHAR *FileName, int _CenterX, int _CenterY, BaseObject* EnemyBulletObject)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得(分割画像読込用)
	CenterX = _CenterX;
	CenterY = _CenterY;

	// 敵弾管理オブジェクトへのアドレス。(ボム時の弾消に利用)
	EnemyBullet = EnemyBulletObject;
	//弾消し用の画像
	GrazeHandle = _gl_mGraphicObject->MyLoadGraphic(_T("Image/graze.png"));
	//スコア表示用フォント(ボム時)
	ScoreFont = CreateFontToHandle(NULL, 24, 3);

	// ボム準備音未再生状態に
	BomPrepareSound = false;
}

PlayerObject::~PlayerObject()
{
	// 子オブジェクト消去
	MyDestructor();
}

void PlayerObject::InitCommon(const TCHAR *FileName) {
	// 画像分割読み込み
	int splitX = 3; // 横分割
	int splitY = 4; // 縦分割
	_gl_mGraphicObject->MyLoadDivGraphic(FileName, splitX, splitY, GraphicHandle); // 画像分割読込
	GraphicPattern = 10; // 画像表示パターン設定
	GetGraphSize(GraphicHandle[0], &WidthX, &HeightY); // グラフィックサイズの設定

	// プレイヤ情報の初期化
	Life = 3; // 残機
	InvincibleTime = 0; // 無敵タイム
	BomSize = 0.0; // ボムの大きさ
	GrazeScore = 0.0; // グレイズにより稼いだスコア
	EraseScore = 0.0; // ボムにより稼いだスコア

	// レイヤ設定
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

	//ボムの発動
	if (_gl_KeyControlObject->Key[KEY_INPUT_Z] == -1 && BomSize > 100) {
		ActivateBom();
	}

	// ボムサイズの加算
	BomSize += 100.0 / 60 / 30;
	if (BomSize > MaxBomSize)
		BomSize = MaxBomSize;

	// 枠内に収める処理
	if (CenterX <= 35)  CenterX = 35;
	if (CenterY <= 35)  CenterY = 35;
	if (CenterX >= 540)  CenterX = 540;
	if (CenterY >= WindowSizeY - 35)  CenterY = WindowSizeY - 35;

	// アニメーション( アニメーションしない画像を利用しているので特に意味はなし )
	if (++AnimationCounter == AnimationInterval) {
		if (++AnimationCounter == 12) {
			AnimationCounter = 10;
		}
		AnimationCounter = 0;
	}

	// ボムで弾を消す処理
	if (UsingBom == TRUE) {
		for (auto itr = EnemyBullet->ObjectList.begin(); itr != EnemyBullet->ObjectList.end(); ++itr) {
			if ((*itr)->ObjectDeleteFlag) continue;
			int Hit = ColEllipsPoint(BomX, BomY, (BaseObject2D*)(*itr));
			if (Hit == 1) {
				((BaseObject2D*)(*itr))->Fadeout = 60; // 60フレームかけて弾をフェードアウト消去
				((BaseObject2D*)(*itr))->NoHitFlag = true; // 当たり判定の除去
				tmp += ((BaseObject2D*)(*itr))->EraseScore; //ポイント加算
			}
		}
		BomCounter--;	//フレーム進める
		//60フレーム経ったらボムを終了
		if (BomCounter == 0) {
			CloseBom();
		}
	}

	// 子オブジェクトのMyUpdateを呼び出す
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
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
	
	// ボムを使ってない場合
	// (Sizeが100未満の時は薄く表示する)
	if (UsingBom == FALSE) {
		if (BomSize < 100) {
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 50);
			DrawRotaGraph(CenterX, CenterY, 2.0 * BomSize / 450, 0.0, GrazeHandle, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
		//Sizeが100以上の時は濃く表示する
		else if (BomSize >= 100) {
			if (!BomPrepareSound) {
				_gl_mSoundObject->MyPlaySoundMem(_T("Sound/pi48.wav"), DX_PLAYTYPE_BACK); // ボム準備音の再生
				BomPrepareSound = true;
			}

			SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
			DrawRotaGraph(CenterX, CenterY, 2.0 * BomSize / 450, 0.0, GrazeHandle, true);
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
		}
	}
	// ボムった時はその場に画像を置いていく
	else if (UsingBom == TRUE) {
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, 150);
		DrawRotaGraph(BomX, BomY, 2.0 * BomSize / 450, 0.0, GrazeHandle, true);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
	}
	// ボムでのスコア加算値を表示
	if (ShowScore == TRUE) {
		DrawFormatStringToHandle(BomX, BomY - 40, GetColor(75 + (120 - ScoreCounter) * 3 / 2, 135 + (120 - ScoreCounter), 195 + (120 - ScoreCounter) / 2), ScoreFont, _T("+%d"), (int)tmp);
		if (ScoreCounter == 0) {
			ShowScore = FALSE;
		}
		ScoreCounter--;
	}
}

void PlayerObject::MyPeculiarAction(BaseObject * obj) {
	// 特にやることはない
}

void PlayerObject::ActivateBom() {
	// 範囲内の弾幕を消す
	UsingBom = TRUE;
	tmp = 0.0;
	BomCounter = 60;
	BomX = CenterX;
	BomY = CenterY;
	InvincibleTime = 90;

	// ボム準備音未再生状態に
	BomPrepareSound = false;

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
	//ボムの終了処理
	UsingBom = FALSE;
	BomSize = 0.0;
	EraseScore += tmp;

	//ボムで得たスコアを表示
	ShowScore = TRUE;
	ScoreCounter = 120;
}

int PlayerObject::ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp) {
	// Xのサイズを判定として利用する
	double ElpSizeX = BomSize; // 大きさ
	double ElpSizeY = BomSize; // 大きさ

	// 点に楕円→真円変換行列を適用(Y方向へ拡大する)
	double Ofs_x = PlayerX - Elp->CenterX;
	double Ofs_y = PlayerY - Elp->CenterY;
	double After_x = Ofs_x*cos(Elp->Angle) + Ofs_y*sin(Elp->Angle);
	double After_y = ElpSizeX / ElpSizeY * (-Ofs_x*sin(Elp->Angle) + Ofs_y*cos(Elp->Angle));

	// 原点から移動後点までの距離を算出
	if (After_x*After_x + After_y*After_y <= ElpSizeX*ElpSizeX)	return 1;
	return 0;
}