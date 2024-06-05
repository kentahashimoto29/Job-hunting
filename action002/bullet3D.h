//========================================================
//
//ウインドウの生成等 (bullet.h)
//Author 橋本賢太
//
//========================================================
#ifndef _BULLET3D_H_
#define _BULLET3D_H_
#include "main.h"
#include "objectX.h"

//===================================
//弾のクラス
//===================================
class CBullet3D : public CObjectX
{
public:
	CBullet3D(int nPriority = 6);																//コンストラクタ
	CBullet3D(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Mag, int nPriority = 6);						//オーバーライドされたコンストラクタ
	~CBullet3D();																//デストラクタ

	static CBullet3D *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, float Mag);		//弾の生成

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

	bool CollisionEnemy(D3DXVECTOR3 pos);		//敵と弾との当たり判定

private:

	D3DXVECTOR3 m_move;							//弾の移動量
	int m_nLife;								//弾の体力

	float m_MoveMag;							//移動量の倍率
};

#endif