#include "stdafx.h"
#include "BaseObject.h"


BaseObject::BaseObject()
{
}

BaseObject::BaseObject(const TCHAR *FileName) 
{
}


BaseObject::~BaseObject()
{
}

void BaseObject::AddObject(BaseObject * obj)
{
	ObjectList.push_back(obj);
}

void BaseObject::ObjectDelete()
{
	ObjectDeleteFlag = true;
}


double BaseObject::GetCenterX()
{
	return CenterX;
}

double BaseObject::GetCenterY()
{
	return CenterY;
}

double BaseObject::GetDrawX()
{
	return CenterX - WidthX/2;
}

double BaseObject::GetDrawY()
{
	return CenterY - HeightY / 2;
}