#pragma once
class BaseObject
{
public:
	BaseObject();
	BaseObject(const TCHAR * FileName);
	~BaseObject();

	// ���ۃN���X�B(�h����Ŏ������Ȃ���΂Ȃ�Ȃ����)
	virtual void MyUpdate() = 0;
	virtual void MyDraw() = 0;
	virtual void MyPeculiarAction( BaseObject * obj ) = 0; // ���̃I�u�W�F�N�g����L�̏���
	void AddObject(BaseObject * obj);

	void ObjectDelete();

	double GetCenterX();
	double GetCenterY();
	double GetDrawX();
	double GetDrawY();

	// ���ʂ��ĕK�v�ƂȂ�p�����[�^
	double CenterX = 0; // �������WX�B��Ɉ������W�B
	double CenterY = 0; // �������WY�B��Ɉ������W�B
	int WidthX = 0; // �T�C�Y�B�R���X�g���N�^�Œ�`
	int HeightY = 0; // �T�C�Y�B�R���X�g���N�^�Œ�` 

	int Layer;
	// �w�i�Ǘ��I�u�W�F�N�g �� �w�i			 Layer = (0)
	// PlayerObject(�V���b�g)				 Layer = (1)
	// �G�e�Ǘ��I�u�W�F�N�g �� �G�e�ȂǂȂ�  Layer = (10)
	// �G�@�Ǘ��I�u�W�F�N�g �� �G			 Layer = (11)
	// PlayerObject(�{��)					 Layer = (20)

	bool ObjectDeleteFlag = false;

	// �q�I�u�W�F�N�g���X�g
	std::list<BaseObject*> ObjectList;


private:
	double LeftX = 0; // �����W�B�\�����ɗ��p�B
	double UpperY = 0; // ����W�B�\�����ɗ��p�B
};