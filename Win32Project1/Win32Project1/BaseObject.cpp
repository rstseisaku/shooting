#include "stdafx.h"
#include "BaseObject.h"


/*
* �I�u�W�F�N�g��ݒ肷�邽�߂̃N���X
* AddObject() �c �q�I�u�W�F�N�g�̒ǉ�
* ObjectDelete() �c �����t���O�𗧂Ă�BUpdate()�EDraw()���Ă΂�Ȃ��Ȃ�B
*�@�� �����t���O���o���Ă�����Adelete( *p ) ���ĂԁA�Ƃ����������ʓr�K�v�B
*/
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
	// �q�I�u�W�F�N�g�̒ǉ�
	ObjectList.push_back(obj);
}

void BaseObject::ObjectDelete()
{
	// �����t���O�𗧂Ă�B
	// Update() Draw()���Ă΂Ȃ����邾��
	ObjectDeleteFlag = true;
}

void BaseObject::MyDestructor()
{
	// �ێ����Ă���I�u�W�F�N�g�����ׂĔj��
	// // �q�I�u�W�F�N�g���A���I�ɔj������
	for (auto itr = ObjectList.begin(); itr != ObjectList.end(); ) {
		delete((*itr));
		itr = ObjectList.erase(itr); // �v�f���폜�A���v�f���󂯎��
	}
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
	return CenterX - WidthX / 2;
}

double BaseObject::GetDrawY()
{
	return CenterY - HeightY / 2;
}