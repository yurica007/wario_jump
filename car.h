#pragma once

#include "Vec2.h"

class Car
{
public:
	Car();
	virtual ~Car() {}

	// グラフィックデータの設定	内部でサイズも取得する
	void setGraphic(int handle);

	// 初期設定	地面の高さを与える
	void setup(float fieldY);

	// 更新
	void update();
	// 描画
	void draw();

	// 位置の取得
	Vec2 getPos() const { return m_pos; }
	// サイズの取得
	Vec2 getSize() const { return m_size; }

private:
	void updateNomal();		// まっすぐ進む
	void updateStop();		// 一時停止フェイント
	void updateJump();		// ジャンプする
	void updateReturn();		// 途中で引き返す

private:
	// グラフィックハンドル
	int m_handle;
	// グラフィックの幅と高さ	当たり判定にも使用する
	Vec2 m_size;

	// 移動開始までの待ち時間
	int m_waitFrame;

	// 位置
	Vec2 m_pos;
	// ベクトル
	Vec2 m_vec;
	// 地面の高さ
	float m_fieldY;
};