#pragma once
class BaseObject
{
public:
	BaseObject();
	BaseObject(const TCHAR * FileName);
	~BaseObject();

	// 抽象クラス。(派生先で実装しなければならないやつ)
	virtual void MyUpdate() = 0;
	virtual void MyDraw() = 0;
	virtual void MyPeculiarAction( BaseObject * obj ) = 0; // そのオブジェクト種特有の処理
	void AddObject(BaseObject * obj);

	void ObjectDelete();

	double GetCenterX();
	double GetCenterY();
	double GetDrawX();
	double GetDrawY();

	// 共通して必要となるパラメータ
	double CenterX = 0; // 中央座標X。主に扱う座標。
	double CenterY = 0; // 中央座標Y。主に扱う座標。
	int WidthX = 0; // サイズ。コンストラクタで定義
	int HeightY = 0; // サイズ。コンストラクタで定義 

	int Layer;
	// 背景管理オブジェクト ⇒ 背景			 Layer = (0)
	// PlayerObject(ショット)				 Layer = (1)
	// 敵弾管理オブジェクト ⇒ 敵弾などなど  Layer = (10)
	// 敵機管理オブジェクト ⇒ 敵			 Layer = (11)
	// PlayerObject(本体)					 Layer = (20)

	bool ObjectDeleteFlag = false;

	// 子オブジェクトリスト
	std::list<BaseObject*> ObjectList;


private:
	double LeftX = 0; // 左座標。表示時に利用。
	double UpperY = 0; // 上座標。表示時に利用。
};