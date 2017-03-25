#include "stdafx.h"
#include "AnimationObject.h"


AnimationObject::AnimationObject(const TCHAR * FileName, int _SplitX, int _SplitY, int _CenterX, int _CenterY)
{
	SplitX = _SplitX;
	SplitY = _SplitY;
	CenterX = _CenterX;
	CenterY = _CenterY;
	_gl_mGraphicObject->MyLoadDivGraphic(FileName, SplitX, SplitY, GraphicHandle);
	GetGraphSize(GraphicHandle[0], &WidthX, &HeightY);
}

AnimationObject::~AnimationObject()
{
}

void AnimationObject::MyUpdate()
{
	// アニメーションを進める
	AnimationCounter = (++AnimationCounter) % AnimationInterval;
	if (AnimationCounter == 0) {
		GraphicPattern++;
		if (GraphicPattern == (AnimationEnd + 1))  ObjectDelete();
	}
}

void AnimationObject::MyDraw()
{
	 DrawGraph((int)GetDrawX(), (int)GetDrawY(), GraphicHandle[GraphicPattern], true);
}

void AnimationObject::MyPeculiarAction(BaseObject * obj)
{
	// 特に必要ない
}

void AnimationObject::SetParameter(int _AnimationInterval, int _AnimationStart, int _AnimationEND)
{
	AnimationInterval = _AnimationInterval;
	AnimationStart = _AnimationStart;
	AnimationEnd = _AnimationEND;

	GraphicPattern = AnimationStart;
}
