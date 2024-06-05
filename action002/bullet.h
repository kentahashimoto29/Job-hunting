//========================================================
//
//ウインドウの生成等 (bullet.h)
//Author 橋本賢太
//
//========================================================
#ifndef _BULLET_H_
#define _BULLET_H_
#include "main.h"
#include "object2D.h"

//===================================
//弾のクラス
//===================================
class CBullet : public CObject2D
{
public:
	CBullet();									//コンストラクタ
	CBullet(D3DXVECTOR3 pos, D3DXVECTOR3 move);	//オーバーライドされたコンストラクタ
	~CBullet();									//デストラクタ

	static CBullet *Create(D3DXVECTOR3 pos);	//弾の生成

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

private:
	bool CollisionEnemy(D3DXVECTOR3 pos);		//敵と弾との当たり判定

	static int m_nIdxTexture;
	D3DXVECTOR3 m_move;							//弾の移動量
	int m_nLife;								//弾の体力
};

#endif