//========================================================
//
//ウインドウの生成等 (enemy.h)
//Author 橋本賢太
//
//========================================================
#ifndef _ENEMY_H_
#define _ENEMY_H_
#include "main.h"
#include "object2D.h"

//===================================
//敵のクラス
//===================================
class CEnemy : public CObject2D
{
public:
	CEnemy();									//コンストラクタ
	CEnemy(D3DXVECTOR3 pos);					//オーバーライドされたコンストラクタ
	~CEnemy();									//デストラクタ

	static CEnemy *Create(D3DXVECTOR3 pos);		//敵の生成

	HRESULT Init(void);							//初期化処理
	void Uninit(void);							//終了処理
	void Update(void);							//更新処理
	void Draw(void);							//描画処理

private:
	static int m_nIdxTexture;					//テクスチャの番号
};

#endif