// stdafx.h : 標準のシステム インクルード ファイルのインクルード ファイル、または
// 参照回数が多く、かつあまり変更されない、プロジェクト専用のインクルード ファイル
// を記述します。
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows ヘッダーから使用されていない部分を除外します。
// Windows ヘッダー ファイル:
#include <windows.h>

// C ランタイム ヘッダー ファイル
#include "DxLib.h"
#include <cstdio>
#include <cstdlib>
#include <cmath>

#include <vector>
#include <list>
#include <map>  
#include <iostream>
#include <algorithm>

#include "BaseObject.h"
#include "BaseObject2D.h"
#include "PlayerObject.h"
#include "PlayerDecorationObject.h"
#include "mGameObject.h"
#include "KeyControl.h"
#include "mGraphic.h"
#include "BackGround.h"
#include "mEnemyBullet.h"
#include "Bullet.h"
#include "Bullet2.h"
#include "Screen.h"
#include "BulletPattern.h"
#include "mEnemy.h"
#include "Enemy.h"

#define WindowSizeX 1024
#define WindowSizeY 576
#define WindowCenterX 512
#define WindowCenterY 288
#define FieldCenterX 288
#define FieldCenterY 288
#define M_PI 3.1415926535

/*
* 背景管理オブジェクト ⇒ 背景			 Layer = (0)
* PlayerObject(ショット)				 Layer = (1)
* 敵弾管理オブジェクト ⇒ 敵弾などなど	 Layer = (10)
* 敵機管理オブジェクト ⇒ 敵			 Layer = (11)
* PlayerObject(本体)					 Layer = (5)
* PlayerDecorationObject(当たり判定明示)			 Layer = (20)
*/
#define Layer_EnemyObject 10
#define Layer_EnemyBullet 11
#define Layer_PlayerObject 5
#define Layer_PlayerDecorationObject 20
#define Layer_PlayerShot 1
#define Layer_BackGround 0
#define Layer_Screen 21

enum CompositeMode { NORMAL = DX_BLENDMODE_PMA_ALPHA, ADD = DX_BLENDMODE_PMA_ADD, SUB = DX_BLENDMODE_PMA_SUB };

// グローバル変数として，画像管理オブジェクトを 1 つだけ保持
extern mGraphic* _gl_mGraphicObject;
extern KeyControl* _gl_KeyControlObject;