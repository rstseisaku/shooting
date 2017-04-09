#include "stdafx.h"
#include "ItemObject.h"


ItemObject::ItemObject(const TCHAR * FileName, int _CenterX, int _CenterY, int _Layer)
{
	// 初期化処理
	InitCommon(FileName); // ファイル名からグラフィックハンドル・サイズを取得
	CenterX = _CenterX;
	CenterY = _CenterY;
	Layer = _Layer; // アイテムオブジェクトは、レイヤーを利用してアイテム種類を判断
}

ItemObject::~ItemObject()
{
	// 子オブジェクトの消去
	MyDestructor();
}

void ItemObject::MyUpdate()
{
	// アイテムオブジェクトはとられるのを待つだけ( 何もしない )
}

void ItemObject::MyDraw()
{
	// オブジェクトの画像を表示
	SetDrawBlendMode(Mode, Transparency);
	DrawRotaGraph((int)CenterX, (int)CenterY, 1.0, Angle / 180 * M_PI,
		GraphicHandle, true);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 255);
}

void ItemObject::MyPeculiarAction(BaseObject * obj)
{
	// 受け取るオブジェクトがプレイヤオブジェクトか確認
	if (obj->Layer != Layer_PlayerObject) return;

	// 受け取ったプレイヤオブジェクトから値を取得
	double PlayerX = obj->CenterX;
	double PlayerY = obj->CenterY;

	// プレイヤとアイテムの距離を算出
	double DistX = abs(PlayerX - CenterX);
	double DistY = abs(PlayerY - CenterY);

	// 矩形判定
	if (DistX <= (WidthX / 2) && DistY <= (HeightY / 2)) {
		// レイヤに応じて、アイテム獲得処理
		if (Layer == Layer_Item) ((PlayerObject*)obj)->GetItemNum++;
		if (Layer == Layer_RareItem) ((PlayerObject*)obj)->GetRareItemNum++;
		if (Layer == Layer_BomItem) ((PlayerObject*)obj)->BomSize += 50;

		// アイテム取得エフェクト表示
		AnimationObject *AnimationObjectTmp;
		AnimationObjectTmp = new AnimationObject(
			_T("Image/Animation3.png"),
			10,
			1,
			((PlayerObject*)obj)->CenterX,
			((PlayerObject*)obj)->CenterY);
		AnimationObjectTmp->Mode = ADD; // アルファブレンドを加算表示に設定
		AnimationObjectTmp->SetParameter(2, 0, 9); // アニメーション頻度・開始・終了をセット

	    // プレイヤオブジェクトの子オブジェクトとして、アニメーションオブジェクトを登録
		((PlayerObject*)obj)->AddObject(AnimationObjectTmp); 

		// 取得音再生
		_gl_mSoundObject->MyPlaySoundMem(_T("Sound/on11.wav"), DX_PLAYTYPE_BACK);

		// 消去フラグを立てる
		ObjectDelete();
	}
}
