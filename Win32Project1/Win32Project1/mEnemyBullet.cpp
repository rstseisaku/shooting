#include "stdafx.h"


/*
* 敵弾を管理するためのクラス
* プレイヤとのあたり判定処理もここで行う
*/
mEnemyBullet::mEnemyBullet()
{
	// レイヤを設定するだけ
	Layer = Layer_EnemyBullet;
}

void mEnemyBullet::MyUpdate()
{
	// 消去フラグを立てる
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;
		(*itr)->MyUpdate();
	}
}

// プレイヤーオブジェクトを受け取り、当たり判定の処理を行う
void mEnemyBullet::MyPeculiarAction(BaseObject * PlayerObj) {
	// 受け取るオブジェクトがプレイヤオブジェクトか確認
	if (PlayerObj->Layer != Layer_PlayerObject) return;

	// 受け取ったプレイヤオブジェクトから値を取得
	double PlayerObjectCenterX = PlayerObj->CenterX;
	double PlayerObjectCenterY = PlayerObj->CenterY;

	// 管理している弾オブジェクトと当たり判定を行う
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ++itr) {
		if ((*itr)->ObjectDeleteFlag) continue;

		// 楕円と点とのあたり判定
		int Hit = ColEllipsPoint(PlayerObjectCenterX, PlayerObjectCenterY, (BaseObject2D*)(*itr));

		// Hit = 1 なら、被弾処理
		if ( Hit == 1 && (((PlayerObject *)PlayerObj)->InvincibleTime == 0) ) {
			(*itr)->ObjectDelete(); // 衝突相手の弾を消す
			((PlayerObject *)PlayerObj)->Life--; // 残機を減らす
			((PlayerObject *)PlayerObj)->InvincibleTime = 120; // 無敵時間をセット

			// 被弾エフェクトの表示
			AnimationObject *AnimationObjectTmp;
			AnimationObjectTmp = new AnimationObject(
				_T("Image/Animation1.png"), 
				7, 
				1, 
				((PlayerObject *)PlayerObj)->CenterX,
				((PlayerObject *)PlayerObj)->CenterY);
			AnimationObjectTmp->SetParameter( 3, 0, 7); // アニメーション頻度・開始・終了をセット
			((PlayerObject *)PlayerObj)->AddObject( AnimationObjectTmp );

			_gl_mSoundObject->MyPlaySoundMem( _T("Sound/bom18.wav"), DX_PLAYTYPE_BACK ); // 被弾音再生
			break; // 同フレームで複数の弾に当たらない
		} else if (Hit >= 2) { 	   // Hit = 2 なら、グレイズ処理
			((BaseObject2D *)(*itr))->GrazeFlag = true;
			_gl_mSoundObject->MyPlaySoundMem(_T("Sound/hit27.wav"), DX_PLAYTYPE_BACK); // グレイズ音再生
			((PlayerObject *)PlayerObj)->BomSize += 5.0; // ボムを少し大きくする
			((PlayerObject *)PlayerObj)->GrazeScore += ((BaseObject2D *)(*itr))->GrazeScore; // スコア加算
		}
	}
}

void mEnemyBullet::MyDraw()
{
	// 持っている弾幕を表示
	for (auto itr = ObjectList.begin(); itr != ObjectList.end();  ) {
		if ((*itr)->ObjectDeleteFlag) {
			delete((*itr));
			itr = ObjectList.erase( itr ); // 要素を削除、次要素を受け取る
			continue;
		}
		(*itr)->MyDraw();
		itr++;
	}

	/*
	if (DEBUG) {
		DrawFormatString(45, 45, GetColor(0, 255, 255), _T("弾数 %d"), ObjectList.size()); // 文字を描画する
		DrawFormatString(45, 65, GetColor(0, 255, 255), _T("グレイズ/ボム %d,%lf"), SetGrazeScore, SetEraseScore); // 文字を描画する
	}*/
}

// BulletPatternに従って弾幕を生成
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
	// スコア情報を付け足して、弾幕を実際に生成
	((BaseObject2D*)obj)->GrazeScore = SetGrazeScore;
	((BaseObject2D*)obj)->EraseScore = SetEraseScore/60;
	ObjectList.push_back(obj);
}


mEnemyBullet::~mEnemyBullet()
{
	MyDestructor();
}

// 楕円と点とのあたり判定処理
// 0 = NO HIT
// 1 = HIT
// 2 = GRAZE
int mEnemyBullet::ColEllipsPoint(double PlayerX, double PlayerY, BaseObject2D* Elp)
{
	// Xのサイズを判定として利用する
	double ElpSizeX = Elp->WidthX * 0.4; // 当たり判定X
	double ElpSizeY = Elp->HeightY * 0.4; // 当たり判定Y
	double ElpGrazeSizeX = Elp->WidthX * 1.1; // グレイズ用の判定
	if (Elp->GrazeFlag == true) ElpGrazeSizeX = 0; // 既にグレイズしていたら判定を消す

	// 点に楕円→真円変換行列を適用(Y方向へ拡大する)
	double Ofs_x = PlayerX - Elp->CenterX;
	double Ofs_y = PlayerY - Elp->CenterY;
	double After_x = Ofs_x*cos(Elp->Angle) + Ofs_y*sin(Elp->Angle);
	double After_y = ElpSizeX / ElpSizeY * (-Ofs_x*sin(Elp->Angle) + Ofs_y*cos(Elp->Angle));

	/*
	if (DEBUG) {
		DrawFormatString(5, 35, GetColor(0, 255, 255), _T("dist %f"), After_x*After_x + After_y*After_y); // 文字を描画する
		DrawFormatString(305, 35, GetColor(0, 255, 255), _T("elp(x,y) %f,%f"), Elp->CenterX, Elp->CenterY); // 文字を描画する
	}
	*/

	// 原点から移動後点までの距離を算出
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