// stdafx.h : �W���̃V�X�e�� �C���N���[�h �t�@�C���̃C���N���[�h �t�@�C���A�܂���
// �Q�Ɖ񐔂������A�����܂�ύX����Ȃ��A�v���W�F�N�g��p�̃C���N���[�h �t�@�C��
// ���L�q���܂��B
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Windows �w�b�_�[����g�p����Ă��Ȃ����������O���܂��B
// Windows �w�b�_�[ �t�@�C��:
#include <windows.h>

// C �����^�C�� �w�b�_�[ �t�@�C��
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
* �w�i�Ǘ��I�u�W�F�N�g �� �w�i			 Layer = (0)
* PlayerObject(�V���b�g)				 Layer = (1)
* �G�e�Ǘ��I�u�W�F�N�g �� �G�e�ȂǂȂ�	 Layer = (10)
* �G�@�Ǘ��I�u�W�F�N�g �� �G			 Layer = (11)
* PlayerObject(�{��)					 Layer = (5)
* PlayerDecorationObject(�����蔻�薾��)			 Layer = (20)
*/
#define Layer_EnemyObject 10
#define Layer_EnemyBullet 11
#define Layer_PlayerObject 5
#define Layer_PlayerDecorationObject 20
#define Layer_PlayerShot 1
#define Layer_BackGround 0
#define Layer_Screen 21

enum CompositeMode { NORMAL = DX_BLENDMODE_PMA_ALPHA, ADD = DX_BLENDMODE_PMA_ADD, SUB = DX_BLENDMODE_PMA_SUB };

// �O���[�o���ϐ��Ƃ��āC�摜�Ǘ��I�u�W�F�N�g�� 1 �����ێ�
extern mGraphic* _gl_mGraphicObject;
extern KeyControl* _gl_KeyControlObject;